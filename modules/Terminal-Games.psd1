@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/Dependencies/Dependencies.psm1',
        './modules/Linters/Linters.psm1',
        './modules/Linters/Helpers/Helpers.psm1'
    )
}
