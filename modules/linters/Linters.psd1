@{
    ModuleVersion = "1.0"

    NestedModules = @(
        "./modules/linters/Linters.psm1"
        "./modules/linters/helpers/Helpers.psm1"
    )

    FunctionsToExport = @(
        "Test-CodeUsingAllLinters",
        "Test-CodeUsingClang",
        "Test-CodeUsingCSpell",
        "Test-CodeUsingPrettier",
        "Test-CodeUsingPSScriptAnalyzer",
        "Test-CSpellConfigurationFile",
        "Test-GitAttributesFile",
        "Test-GitIgnoreFile",
        "Test-PrettierIgnoreFile"
    )
}
