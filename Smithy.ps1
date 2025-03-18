[CmdletBinding()]
Param(
  [Parameter(Mandatory = $true, Position = 0)]
  [string]$Name,

  [Parameter(Mandatory = $true, Position = 1, ValueFromRemainingArguments = $true)]
  [string[]]$Types
)

# Convertir el nombre a PascalCase para mantener consistencia
$NamePascal = ($Name.Substring(0, 1).ToUpper() + $Name.Substring(1).ToLower())

# Mapeo de los tipos a sus respectivas carpetas
$TypeMapping = @{
  "model"      = "models"
  "controller" = "controllers"
  "view"       = "views"
}

foreach ($Type in $Types) {
  if (-not $TypeMapping.ContainsKey($Type)) {
    Write-Host "Error: Tipo desconocido '$Type'. Usa 'model', 'controller' o 'view'." -ForegroundColor Red
    continue
  }

  # Generar el nombre del archivo en formato PascalCase
  $FullName = "$NamePascal$($Type.Substring(0,1).ToUpper())$($Type.Substring(1))"
  $NAME_UPPER = $FullName.ToUpper()

  # Definir las rutas de los archivos
  $FolderPath = "src\$($TypeMapping[$Type])"
  $headerPath = "$FolderPath\$FullName.h"
  $sourcePath = "$FolderPath\$FullName.c"

  # Crear la carpeta si no existe
  if (!(Test-Path $FolderPath)) {
    New-Item -ItemType Directory -Path $FolderPath -Force | Out-Null
  }

  # Contenido del archivo .h
  $headerContent = @"
#ifndef ${NAME_UPPER}_H
#define ${NAME_UPPER}_H

// Declaraciones para ${FullName} (${Type})

void example${FullName}Function();

#endif
"@

  # Contenido del archivo .c
  $sourceContent = @"
#include "${FullName}.h"
#include <stdio.h>

// Implementaciones para ${FullName} (${Type})

void example${FullName}Function() {
    printf("Funcion de ejemplo para ${FullName} (${Type})\n");
}
"@

  # Crear los archivos y escribir contenido
  New-Item -ItemType File -Path $headerPath -Force | Out-Null
  New-Item -ItemType File -Path $sourcePath -Force | Out-Null

  Set-Content -Path $headerPath -Value $headerContent
  Set-Content -Path $sourcePath -Value $sourceContent

  Write-Host "Archivos generados:"
  Write-Host "  $headerPath"
  Write-Host "  $sourcePath"
}

Write-Host "Generación completada con éxito." -ForegroundColor Green
