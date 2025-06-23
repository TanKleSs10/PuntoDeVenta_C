#include "utils.h"

const char *role_to_string(UserRole role) {
  switch (role) {
  case ADMIN:
    return "ADMIN";
  case CASHIER:
    return "CAJERO";
  case SUPERADMIN:
    return "SUPERADMIN";
  default:
    return "DESCONOCIDO";
  }
}

// Nueva y mejorada get_line_input
void get_line_input(char *buffer, size_t size) {
  // Intentar leer la línea completa
  if (fgets(buffer, size, stdin) == NULL) {
    // Manejo de error si fgets falla (ej. EOF, error de lectura)
    buffer[0] = '\0'; // Asegurar que el buffer esté vacío
    // Opcional: imprimir un mensaje de error o manejar de otra forma
    printf("Error de lectura de entrada.\n");
    // Asegurarse de limpiar stdin si falló
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    return;
  }

  // Buscar el salto de línea
  char *newline_pos = strchr(buffer, '\n');

  if (newline_pos != NULL) {
    // Si se encuentra el salto de línea, reemplazarlo por el terminador nulo
    *newline_pos = '\0';
  } else {
    // Si no se encontró el salto de línea, significa que la línea era más larga
    // que 'size - 1' caracteres. Es necesario limpiar el resto de stdin.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
      // Consumir el resto de la línea
    }
  }
}

void clear_input() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Función auxiliar para convertir el tipo de promoción a cadena
const char *promo_type_to_string(PromoType type) {
  switch (type) {
  case PROMO_NONE:
    return "Ninguna";
  case PROMO_2X1:
    return "2x1";
  case PROMO_3X2:
    return "3x2";
  case PROMO_NO_TAX:
    return "Sin Impuesto";
  case PROMO_FIXED_DISCOUNT:
    return "Descuento Fijo";
  default:
    return "Desconocido";
  }
}

// Implementación de clear_screen
void clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void press_enter_to_continue() {
  printf("\nPresiona ENTER para continuar...");
  fflush(
      stdout); // Asegura que el mensaje se imprima antes de esperar la entrada

  // Limpia el búfer de entrada de cualquier carácter pendiente,
  // hasta que encuentre un salto de línea o el fin del archivo (EOF).
  // Esto es crucial para que la pausa funcione correctamente si una entrada
  // anterior dejó un '\n' en el búfer.
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void art_adminCore() {
  printf("          ______         __                __             ______     "
         "                                  ______  \n");
  printf(" /      \\       /  |              /  |           /      \\          "
         "                           /      \\ \n");
  printf("/$$$$$$  |  ____$$ | _____  ____  $$/  _______  /$$$$$$  |  ______   "
         " ______   ______        /$$$$$$  |\n");
  printf("$$ |__$$ | /    $$ |/     \\/    \\ /  |/       \\ $$ |  $$/  /      "
         "\\  /      \\ /      \\       $$ |  $$/ \n");
  printf("$$    $$ |/$$$$$$$ |$$$$$$ $$$$  |$$ |$$$$$$$  |$$ |      /$$$$$$  "
         "|/$$$$$$  /$$$$$$  |      $$ |      \n");
  printf("$$$$$$$$ |$$ |  $$ |$$ | $$ | $$ |$$ |$$ |  $$ |$$ |   __ $$ |  $$ "
         "|$$ |  $$/$$    $$ |      $$ |   __ \n");
  printf("$$ |  $$ |$$ \\__$$ |$$ | $$ | $$ |$$ |$$ |  $$ |$$ \\__/  |$$ "
         "\\__$$ |$$ |     $$$$$$$$/       $$ \\__/  |\n");
  printf("$$ |  $$ |$$    $$ |$$ | $$ | $$ |$$ |$$ |  $$ |$$    $$/ $$    $$/ "
         "$$ |     $$       |      $$    $$/ \n");
  printf("$$/   $$/  $$$$$$$/ $$/  $$/  $$/ $$/ $$/   $$/  $$$$$$/   $$$$$$/  "
         "$$/       $$$$$$$/        $$$$$$/  \n");
  printf("                                                                     "
         "                                  \n");
}

void delay_ms(int ms) {
#ifdef _WIN32
  Sleep(ms); // Sleep en Windows usa milisegundos
#else
  // En sistemas POSIX (Linux, macOS), sleep() usa segundos.
  // Para milisegundos, podemos usar usleep() (microsegundos) o nanosleep()
  // (nanosegundos) nanosleep es más preciso y recomendado.
  struct timespec ts;
  ts.tv_sec = ms / 1000;              // Segundos
  ts.tv_nsec = (ms % 1000) * 1000000; // Nanosegundos

  // nanosleep puede ser interrumpido por señales,
  // así que se usa un bucle para reintentar si es interrumpido.
  int ret;
  do {
    ret = nanosleep(&ts, &ts);
  } while (ret == -1 && errno == EINTR);
#endif
}
