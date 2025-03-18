#include "helpers.h"

void logError(const char *msj)
{
    FILE *file = fopen(ERROR_LOG, "a");
    if (!file)
    {
        return; // Evitar mostrar errores a usuarios malintencionados
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d] ERROR: %s: %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, // Fecha
            t->tm_hour, t->tm_min, t->tm_sec,             // Hora
            msj, strerror(errno));                        // Mensaje personalizado + error del sistema

    fclose(file);
}

// Función genérica para abrir archivos
FILE *openFile(const char *filename, const char *mode, const char *errorMsg)
{
    FILE *file = fopen(filename, mode);
    if (!file)
    {
        logError(errorMsg);
    }
    return file;
}

int replaceFile(const char *original, const char *temp)
{
    if (remove(original) != 0)
        return 0;
    if (rename(temp, original) != 0)
        return 0;
    return 1;
}

void ShowMessageCleanScreen(const char *msj, int seconds)
{
    printf("%s\n", msj);

#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(segundos);
#endif

    system(CLEAN_SCREEN);
}