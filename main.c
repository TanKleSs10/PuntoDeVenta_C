#include <stdio.h>
#include <locale.h>

#include "src/controllers/ConfigController.h"
#include "src/controllers/UserController.h"
#include "src/controllers/ProductController.h"
#include "src/controllers/AuthController.h"

int main(void)
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    // Validar configuración
    validateConfig();

    // Validar autenticación
    if (!isLoggedIn())
    {
        login();
    }
    // Mostrar menú principal
    welcome();
    return 0;
}