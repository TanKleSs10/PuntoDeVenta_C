#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h> // Para system(), etc.
#define ERROR_LOG "../data/error.log"

#ifdef _WIN32
#define CLEAN_SCREEN "cls"
#else
#define CLEAN_SCREEN "clear"
#endif

#ifdef _WIN32
#include <windows.h> // Para Sleep()
#else
#include <unistd.h> // Para sleep()
#endif

FILE *openFile(const char *filename, const char *mode, const char *errorMsg);
int replaceFile(const char *original, const char *temp);
void logError(const char *msj);
void ShowMessageCleanScreen(const char *msj, int seconds);

#endif