#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


// obtener fecha
char* get_date_formato_iso() {
    time_t timer;
    char* buffer = (char*)malloc(11 * sizeof(char)); // YYYY-MM-DD\0

    if (buffer == NULL) {
        LOG_ERROR("Error al asignar memoria");
        return NULL;
    }

    timer = time(NULL);
    struct tm *tm_info = localtime(&timer);

    if (tm_info == NULL) {
        LOG_ERROR("Error al obtener la fecha");
        free(buffer);
        return NULL;
    }

    strftime(buffer, 11, "%Y-%m-%d", tm_info);
    return buffer;
}

static LogLevel current_log_level = LOG_INFO;

void set_log_level(LogLevel level) {
    current_log_level = level;
}

const char* level_to_string(LogLevel level) {
    switch (level) {
        case LOG_DEBUG: return "DEBUG";
        case LOG_INFO: return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR: return "ERROR";
        case LOG_CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

void log_msg(LogLevel level, const char* formato, ...) {
    if (level < current_log_level) return;

    char* date_str = get_date_formato_iso();
    char* filename = NULL;
    const char* log_dir = "logs/";
    const char* log_ext = ".log";

    if (date_str != NULL) {
        size_t filename_len = strlen(log_dir) + strlen(date_str) + strlen(log_ext) + 1;
        filename = (char*)malloc(filename_len * sizeof(char));
        if (filename == NULL) {
            LOG_ERROR("Error al asignar memoria para el nombre del archivo de log");
            free(date_str);
            return;
        }
        snprintf(filename, filename_len, "%s%s%s", log_dir, date_str, log_ext);
        free(date_str);
    } else {
        // Si falla la obtención de la fecha, usa un nombre de archivo genérico
        filename = strdup("logs/sistema.log");
        if (filename == NULL) {
            LOG_ERROR("Error al asignar memoria para el nombre de archivo de log genérico");
            return;
        }
    }
    
    FILE* f = fopen(filename, "a");
    if (!f) return;

    // Obtener timestamp
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char tiempo[26];
    strftime(tiempo, sizeof(tiempo), "%Y-%m-%d %H:%M:%S", tm_info);

    // Escribir en archivo
    fprintf(f, "[%s] [%s] ", tiempo, level_to_string(level));
    va_list args;
    va_start(args, formato);
    vfprintf(f, formato, args);
    va_end(args);
    fprintf(f, "\n");
    fclose(f);

    // Solo imprimir en consola si es DEBUG
    if (level == LOG_DEBUG) {
        printf("[DEBUG] ");
        va_start(args, formato);
        vprintf(formato, args);
        va_end(args);
        printf("\n");
    }
}
