$ErrorActionPreference = "Stop"

Write-Host "##[group]Linting .gitattributes file"

Write-Host "##[debug]Retrieving contents of .gitattributes..."

$gitattributesFileContents = @(Get-Content -Path ./.gitattributes)

Write-Host "##[debug]Finished retrieving the contents .gitattributes:"

$gitattributesFileContentsWithoutComments = @()
$linesNotMatchingCodeStandards = @()
$linesNotMatchingCommentStandards = @()

Write-Host "##[debug]Starting .gitattributes validation..."

foreach ($line in $gitattributesFileContents) {

    if ($line -eq "") {
        Write-Host "##[debug]Current line is blank: '$line'"
        continue
    }

    # Match every before and including '#'
    $lineBeforeAndIncludingComment = $line | Select-String -Pattern ".*#"

    if ($null -eq $lineBeforeAndIncludingComment) {
        Write-Host "##[debug]Current line is code: '$line'"

        if (-not ( # Second repetition of each condition is to account for files without file extensions
                $line -Match "^\* +text=auto$" -or
                $line -Match "^\*\.[a-z]+ +binary$" -or
                $line -Match "^[a-z]+ +binary$" -or
                $line -Match "^\*\.[a-z]+ +text$" -or
                $line -Match "^[a-z]+ +text$" -or
                $line -Match "^\*\.[a-z]+ +text +diff=[a-z]+$" -or
                $line -Match "^[a-z]+ +text +diff=[a-z]+$"
            )) {
            $linesNotMatchingCodeStandards += $line
        }

        else {
            $gitattributesFileContentsWithoutComments += $line
        }

        continue
    }

    if ($lineBeforeAndIncludingComment.matches.value.Length -eq 1) {
        Write-Host "##[debug]Current line is comment: '$line'"
        continue
    }

    Write-Host "##[debug]Current line is a mixture of comment and code: '$line'"
    $linesNotMatchingCommentStandards += $line
}

Write-Host "##[debug]Finished .gitattributes validation."

$errors = @()

if ($linesNotMatchingCodeStandards.Length -gt 0) {
    $errors += "##[error]Standards only allow the following gitattributes: '* text=auto', '[FILE]/[FILE EXTENSION] binary', '[FILE]/[FILE EXTENSION] text', '[FILE]/[FILE EXTENSION] text diff=[TEXT]'"
    $errors += "##[error]The following lines do not conform to the above standards:"
    $errors += $linesNotMatchingCodeStandards | ForEach-Object { "##[error]'$_'" }
}

if ($linesNotMatchingCommentStandards.Length -gt 0) {
    $errors += "##[error]Standards only allow lines to be blank, entirely comment or entirely non-comment."
    $errors += "##[error]The following lines do not conform to the above standards:"
    $errors += $linesNotMatchingCommentStandards | ForEach-Object { "##[error]'$_'" }
}

if ($errors.Length -gt 0) {
    $errors | Out-String | Write-Error
}

Write-Host "##[debug]Retrieving all unique file extensions and unique files without a file extension..."

$gitTrackedFiles = git ls-files -c | Split-Path -Leaf
$uniqueGitTrackedFileExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -gt 1) { ".$($_.Split(".")[-1])" } } | Sort-Object | Select-Object -Unique
$uniqueGitTrackedFilesWithoutExtensions = $gitTrackedFiles | ForEach-Object { if ($_.Split(".").Length -eq 1) { $_ } } | Sort-Object | Select-Object -Unique

Write-Host "##[debug]Retrieved unique file extensions:"
$uniqueGitTrackedFileExtensions | ForEach-Object { "##[debug]$_" } | Write-Host
Write-Host "##[debug]Retrieved unique files without a file extension:"
$uniqueGitTrackedFilesWithoutExtensions | ForEach-Object { "##[debug]$_" } | Write-Host

$fileExtensionsMissingGitattributes = @()
$linesForDuplicateEntries = @()

Write-Host "##[debug]Checking all unique file extensions have a .gitattributes entry:"

foreach ($fileExtension in $uniqueGitTrackedFileExtensions) {

    $foundMatch = $false

    foreach ($line in $gitattributesFileContentsWithoutComments) {

        if ($line -Match "\$fileExtension" ) {
            Write-Host "##[debug]$fileExtension entry found: '$line'"

            if ($foundMatch) {
                $linesForDuplicateEntries += $line
            }

            $foundMatch = $true
        }
    }

    if (-not $foundMatch) {
        $fileExtensionsMissingGitattributes += $fileExtension
    }
}

Write-Host "##[debug]Finished checking that all unique file extensions have a .gitattributes entry."

Write-Host "##[debug]Checking all unique files without a file extension have a .gitattributes entry:"

foreach ($fileName in $uniqueGitTrackedFilesWithoutExtensions) {

    $foundMatch = $false

    foreach ($line in $gitattributesFileContentsWithoutComments) {

        if ($line -Match $fileName ) {
            Write-Host "##[debug]$fileName entry found: '$line'"

            if ($foundMatch) {
                $linesForDuplicateEntries += $line
            }

            $foundMatch = $true
        }
    }

    if (-not $foundMatch) {
        $fileExtensionsMissingGitattributes += $fileName
    }
}


Write-Host "##[debug]Finished checking that all unique files without a file extension have a .gitattributes entry."

$errors = @()

if ($fileExtensionsMissingGitattributes.Length -gt 0) {
    $errors += "##[error]Standards require all file extensions (and files without a file extension) to have an explicit entry in .gitattributes."
    $errors += "##[error]The following file extensions (and files without a file extension) do not conform to the above standards:"
    $errors += $fileExtensionsMissingGitattributes | ForEach-Object { "##[error]'$_'" }
}

if ($linesForDuplicateEntries.Length -gt 0) {
    $errors += "##[error]Standards do not allow multiple entries for file extensions (and files without a file extension) within .gitattributes."
    $errors += "##[error]The following lines do not conform to the above standards:"
    $errors += $linesForDuplicateEntries | ForEach-Object { "##[error]'$_'" }
}

if ($errors.Length -gt 0) {
    $errors | Out-String | Write-Error
}

else {
    Write-Host "##[debug]The .gitattributes file conforms to standards."
}

Write-Host "##[endgroup]"