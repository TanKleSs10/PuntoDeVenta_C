#include "AuthModel.h"

// Guarda la sesión en un archivo
int saveSession(Session *session)

{
    FILE *file = openFile(SESSIONS_FILE, "ab", "Error al abrir el archivo de sesiones");
    if (!file)
        return 0;

    int result = fwrite(session, sizeof(Session), 1, file) == 1;
    fclose(file);
    return result;
}

// Lee la sesión almacenada y devuelve un puntero a Session
Session *getSession()
{
    FILE *file = openFile(SESSIONS_FILE, "rb", "Error al abrir el archivo de sesiones");
    if (!file)
        return NULL;

    Session *session = (Session *)malloc(sizeof(Session));
    if (!session)
    {
        fclose(file);
        logError("Error al asignar memoria para la sesión.");
        return NULL;
    }

    if (fread(session, sizeof(Session), 1, file) != 1)
    {
        free(session);
        fclose(file);
        logError("Error al leer la sesión del archivo.");
        return NULL;
    }

    fclose(file);
    return session;
}

// Elimina la sesión almacenada
int removeSession()
{
    if (remove(SESSIONS_FILE) == 0)
    {
        return 1; // Sesión eliminada exitosamente
    }
    logError("Error al eliminar la el archivo de sesiones.");
    return 0; // No se pudo eliminar la sesión
}
