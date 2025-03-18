#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <stdio.h>
#include <string.h>
#include "../helpers/helpers.h"

// Declaraciones para ConfigModel (model)

typedef struct
{
    char bussinesName[50];
    float taxes;       // Porcentaje de impuesto (ej. 16.0 para 16%)
    char currency[10]; // "MXN", "USD", etc.
    char admin[50];
} ConfigPOS; // Estructura de la configuración

int saveConfig(const ConfigPOS *config);

int readConfig(ConfigPOS *config);

int removeFileConfig();
ConfigPOS *getConfig();

#endif
