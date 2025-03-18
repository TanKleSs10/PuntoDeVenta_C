[CmdletBinding()]
Param(
    [Parameter(Mandatory = $true)]
    [string]$Name
)

# Convertir el nombre a PascalCase
$NamePascal = ($Name.Substring(0, 1).ToUpper() + $Name.Substring(1).ToLower())

# Mapeo de carpetas por tipo (en plural)
$TypeMapping = @{
    "models"      = "Model"
    "controllers" = "Controller"
    "views"       = "View"
}

# Función para extraer declaraciones de funciones de un archivo .c
function Get-FunctionDeclarations {
    param (
        [string]$SourcePath
    )

    # Patrón para detectar definiciones de funciones en C (incluyendo parámetros)
    $functionPattern = '^\w+\s+\w+\([^)]*\)\s*\{'
    $functions = Get-Content -Path $SourcePath | Where-Object { $_ -match $functionPattern }

    # Convertir definiciones de funciones en declaraciones
    $declarations = @()
    foreach ($function in $functions) {
        # Eliminar el { y cualquier cosa después, y agregar un ;
        $declaration = $function -replace '\s*\{.*$', ';'
        $declarations += $declaration
    }

    return $declarations
}

# Función para actualizar un archivo .h si es necesario
function Update-HeaderFile {
    param (
        [string]$Folder,
        [string]$FilePrefix,
        [string]$FileSuffix
    )

    $FullName = "$FilePrefix$FileSuffix"
    $headerPath = "src\$Folder\$FullName.h"
    $sourcePath = "src\$Folder\$FullName.c"

    # Verificar si los archivos existen
    if (!(Test-Path $headerPath) -or !(Test-Path $sourcePath)) {
        Write-Host "Archivo no encontrado: $headerPath o $sourcePath" -ForegroundColor Yellow
        return
    }

    # Obtener fechas de modificación
    $headerTime = (Get-Item $headerPath).LastWriteTime
    $sourceTime = (Get-Item $sourcePath).LastWriteTime

    # Si el .c es más reciente que el .h, se actualiza el header
    if ($sourceTime -gt $headerTime) {
        $NAME_UPPER = $FullName.ToUpper()
        $declarations = Get-FunctionDeclarations -SourcePath $sourcePath

        if ($declarations.Count -eq 0) {
            Write-Host "No se encontraron declaraciones de funciones en $sourcePath" -ForegroundColor Yellow
            return
        }

        $headerContent = @"
#ifndef ${NAME_UPPER}_H
#define ${NAME_UPPER}_H

// Declaraciones para ${FullName}

$($declarations -join "`n")

#endif
"@

        Set-Content -Path $headerPath -Value $headerContent
        Write-Host "Actualizado: $headerPath" -ForegroundColor Green
    }
    else {
        Write-Host "No es necesario actualizar: $headerPath" -ForegroundColor Cyan
    }
}

# Revisar cada tipo (model, controller, view)
foreach ($Folder in $TypeMapping.Keys) {
    $FileSuffix = $TypeMapping[$Folder]
    $FullName = "$NamePascal$FileSuffix"
    Update-HeaderFile -Folder $Folder -FilePrefix $NamePascal -FileSuffix $FileSuffix
}

Write-Host "Verificación completada." -ForegroundColor Cyan