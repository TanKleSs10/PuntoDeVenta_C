#include "includes/auth.ui.h"
#include "../../utils/utils.h"
#include <string.h> // Para strlen

void login_ui(Auth* auth) {
    bool valid_input;
    
    do{
        printf("Ingresa el nombre de usuario: ");
        get_line_input(auth-> user.username, sizeof(auth->user.username));
        valid_input = (strlen(auth->user.username) >= 3 && strlen(auth->user.username) <= 20);
        if (!valid_input) {
            printf("El nombre de usuario debe tener entre 3 y 20 caracteres.\n");
        }
    } while (!valid_input);

    do {
        printf("Ingresa la contraseña: ");
        get_line_input(auth->user.password, sizeof(auth->user.password));
        valid_input = (strlen(auth->user.password) >= 8 && strlen(auth->user.password) <= 20);
        if (!valid_input) {
            printf("La contraseña debe tener entre 8 y 20 caracteres.\n");
        }
    } while (!valid_input);

}

void show_session_ui(Auth* session) {
    printf("Usuario: %s\n", session->user.username);
    printf("Rol: %s\n", role_to_string(session->user.role));
    printf("Fecha de creación: %s\n", ctime(&session->CreatedAt));
}