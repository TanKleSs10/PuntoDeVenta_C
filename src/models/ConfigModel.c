#include "ConfigModel.h"
#include <stdio.h>

// Implementaciones para ConfigModel (model)
static const char *CONFIG_FILE = "../data/config.dat";

int saveConfig(const ConfigPOS *config)
{
    FILE *file = openFile(CONFIG_FILE, "wb", "Error al abrir el archivo de configuracion");
    if (!file)
        return 0;
    int result = fwrite(config, sizeof(ConfigPOS), 1, file) == 1;
    fclose(file);

    return result;
}

int readConfig(ConfigPOS *config)
{
    FILE *file = openFile(CONFIG_FILE, "rb", "Error al abrir el archivo de configuración");
    if (!file)
        return 0; // El archivo no existe.

    int read = fread(config, sizeof(ConfigPOS), 1, file);
    fclose(file);

    // Validar si la lectura fue exitosa y si los datos son válidos
    if (read != 1 || strlen(config->admin) == 0)
    {
        return 0; // Configuración inválida.
    }

    return 1; // Configuración válida.
}

ConfigPOS *getConfig()
{
    FILE *file = openFile(CONFIG_FILE, "rb", "Error al abrir el archivo de configuración");
    if (!file)
        return NULL;

    ConfigPOS *config = (ConfigPOS *)malloc(sizeof(ConfigPOS));
    if (!config)
    {
        fclose(file);
        logError("Error al asignar memoria para la configuracion.");
        return NULL;
    }

    if (fread(config, sizeof(ConfigPOS), 1, file) != 1)
    {
        free(config);
        fclose(file);
        logError("Error al leer la configuracion del archivo.");
        return NULL;
    }

    fclose(file);
    return config;
}

int removeFileConfig()
{

    if (!openFile(CONFIG_FILE, "rb", "Error al abrir el archivo de configuración"))
        return 0;

    remove(CONFIG_FILE);
    return 1;
}