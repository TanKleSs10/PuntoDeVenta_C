#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructuras ----

typedef struct {
	int id;
	char name[50];
	char desc[100];
	char bar_code[13];
	float price;
} Product;  // Estructura de un producto

typedef struct {
	int id;
	char name[50];
	int role; // 1: Administrador, 2: Cajero, etc.
	char pass[20]; // En un sistema real, se debería cifrar
} User; // Estructura de usuario

typedef struct {
	char bussinesName[50];
	float taxes;  // Porcentaje de impuesto (ej. 16.0 para 16%)
	char currency[10];  // "MXN", "USD", etc.
	char admin[50];
} ConfigPOS; // Estructura de la configuración


// Funciones para la configuracion de sistema ---

// Funcion para configurar el sistema
void configSystem() {
	FILE *file = fopen("config.dat", "wb"); // Sobreescribimos la configuracion
	if (!file) {
		printf("Error al abrir el archivo \n");
		return;
	}

	ConfigPOS c;
	User superUser;

	// Solicitar nombre de la empresa
	do {
		printf("Nombre de la empresa: ");
		scanf(" %49[^\n]", c.bussinesName);
		if (strlen(c.bussinesName) == 0) {
			printf("❌ El nombre no puede estar vacio. \n");
		}
	} while (strlen(c.bussinesName) == 0);

	// Solicitar porcentaje de impuestos
	do {
		printf("Porcentaje de Impuestos (IVA): ");
		scanf("%f", &c.taxes);
		if (c.taxes <= 0) {
			printf("❌ El Impuesto debe ser un numero positivo mayor a 0.\n");
		}
	} while (c.taxes <= 0);

	// Solicitar tipo de moneda
	do {
		printf("Ingresa el tipo de moneda (MXN o USD): ");
		scanf(" %9s", c.currency);
		if (strcmp(c.currency, "MXN") != 0 && strcmp(c.currency, "USD") != 0) {
			printf("❌ La moneda debe ser MXN o USD.\n");
		}
	} while (strcmp(c.currency, "MXN") != 0 && strcmp(c.currency, "USD") != 0);

	// Crear superusuario
	printf("\n--- Creacion del Superusuario ---\n");
	superUser.id = 1;
	superUser.role = 1; // Administrador

	printf("Nombre del Superusuario: ");
	scanf(" %49[^\n]", superUser.name);

	printf("Contraseña del Superusuario: ");
	scanf(" %19s", superUser.pass);

	// Guardar nombre del administrador en ConfigPOS
	strcpy(c.admin, superUser.name);

	// Guardar la configuracion en el archivo
	fwrite(&c, sizeof(ConfigPOS), 1, file);
	fclose(file);

	// Guardar superusuario en otro archivo
	file = fopen("users.dat", "wb");
	if (!file) {
		printf("Error al abrir el archivo de usuarios\n");
		return;
	}
	fwrite(&superUser, sizeof(User), 1, file);
	fclose(file);

	printf("\n✅ Configuracion guardada exitosamente.\n");
}

// Funcion para verificar si el sistema ya está configuradoc ---

int isConfigured() {
	FILE *file = fopen("config.dat", "rb");
	if (!file) {
		return 0; // No existe el archivo, no está configurado
	}

	fseek(file, 0, SEEK_END); // Mueve el puntero al final
	long size = ftell(file);  // Obtiene la posición actual (tamaño del archivo)
	fclose(file);

	return (size > 0); // Retorna 1 si tiene datos, 0 si está vacío
}

// Leer la configuracion del sistema
void showConfig() {
	FILE *file = fopen("config.dat", "rb"); // Abrimos en modo lectura binaria
	if (!file) {
		printf("No hay configuracion.\n");
		return;
	}

	ConfigPOS c;
	printf("\n--- Configuracion del sistema ---\n");

	// Leer el archivo hasta el final
	while (fread(&c, sizeof(ConfigPOS), 1, file)) {
		printf("Nombre de la empresa: %s | Impuestos(IVA): %2.f | Tipo de Moneda: %s | Administrador: %s \n",
		       c.bussinesName, c.taxes, c.currency, c.admin );
	}

	fclose(file);
}

// funcion para elminar la configuración
void deleteConfig() {
	FILE *fileConfig = fopen("config.dat", "rb");
	FILE *fileUsers = fopen("users.dat", "rb");

	// Si ambos archivos no existen, no hay nada que eliminar
	if (!fileConfig && !fileUsers) {
		printf("⚠️ No hay configuración ni usuarios registrados.\n");
		return;
	}

	// Cerramos los archivos si fueron abiertos
	if (fileConfig) fclose(fileConfig);
	if (fileUsers) fclose(fileUsers);

	// Preguntar al usuario si desea eliminar los archivos
	char option[10]; // Suficientemente grande para "si" o "no"
	printf("\nSe eliminarán la configuracion y los usuarios del sistema de forma permanente.\n");
	printf("Estas seguro de eliminar la configuracion? (si / no): ");
	scanf(" %9s", option); // Leemos la respuesta

	// Convertir a minúsculas para evitar errores con "Si" o "SI"
	for (int i = 0; option[i]; i++) {
		option[i] = tolower(option[i]);
	}

	if (strcmp(option, "si") == 0) {
		printf("Eliminando configuracion...\n");
		remove("config.dat");
		remove("users.dat");
		printf("Configuracion eliminada correctamente.\n");
		return;
	} else {
		printf("Operacion cancelada. Regresando al menú...\n");
	}
}

/// funciones autenticar usuarios

int validatedUser() {
	FILE *file = fopen("users.dat", "rb");
	if (!file) {
		printf("❌ No hay usuarios registrados.\n");
		return 0; // Retornamos 0 indicando fallo
	}

	char userToFound[50], password[20];
	printf("Ingrese el nombre de usuario: ");
	scanf("%s", userToFound);

	printf("Ingrese la password: ");
	scanf("%s", password);

	User u;
	int found = 0;

	while (fread(&u, sizeof(User), 1, file)) {
		if (strcmp(u.name, userToFound) == 0 && strcmp(u.pass, password) == 0) {
			found = 1;
			printf("✅ Usuario autenticado correctamente.\n");
			break; // Salimos del bucle porque ya encontramos el usuario
		}
	}

	fclose(file);

	if (!found) {
		printf("Usuario o password incorrectos.\n");
	}

	return found; // Retornamos 1 si autenticó correctamente, 0 si falló
}

//CRUD de Productos

// Función para agregar o crear un producto
void addProduct() {
	FILE *file = fopen("products.dat", "ab");
	if(!file) {
		printf("Error al abrir el archivo \n");
		return;
	}

	Product p;

	// Solicitar ID
	do {
		printf("ID: ");
		scanf("%d", &p.id);
		if (p.id <= 0) {
			printf("❌ El ID debe ser un numero positivo.\n");
		}
	} while (p.id <= 0);

	// Solicitar nombre
	do {
		printf("Nombre: ");
		scanf(" %49[^\n]", p.name);  // %49 para evitar desbordamiento
		if (strlen(p.name) == 0) {
			printf("❌ El nombre no puede estar vacio.\n");
		}
	} while (strlen(p.name) == 0);

	// Solicitar descripción
	do {
		printf("Descripcion: ");
		scanf(" %99[^\n]", p.desc);  // %99 para evitar desbordamiento
		if (strlen(p.desc) == 0) {
			printf("❌ La descripcion no puede estar vacia.\n");
		}
	} while (strlen(p.desc) == 0);

	// Solicitar precio
	do {
		printf("Precio: ");
		scanf("%f", &p.price);
		if (p.price < 0) {
			printf("❌ El precio debe ser un numero positivo.\n");
		}
	} while (p.price < 0);

	// Solicitar código de barras
	do {
		printf("Codigo de Barras (12 dígitos): ");
		scanf("%s", p.bar_code);
		if (strlen(p.bar_code) != 12) {
			printf("❌ El codigo de barras debe tener exactamente 12 caracteres.\n");
		}
	} while (strlen(p.bar_code) != 12);

	// Añadir producto al archivo
	fwrite(&p, sizeof(Product), 1, file);
	fclose(file);

	printf("Producto guardado exitosamente.\n");
}

// Función para mostrar o leer la lista de productos
void showProducts() {
	FILE *file = fopen("products.dat", "rb"); // Abrimos en modo lectura binaria
	if (!file) {
		printf("❌ No hay productos registrados.\n");
		return;
	}

	Product p;
	printf("\n--- Lista de Productos ---\n");

	// Leer el archivo hasta el final
	while (fread(&p, sizeof(Product), 1, file)) {
		printf("ID: %d | Nombre: %s | Descripcion: %s | Precio: %.2f | codigo: %s\n",
		       p.id, p.name, p.desc, p.price, p.bar_code);
	}

	fclose(file);
}

// Funcion para eliminar un producto
void deleteProduct() {

	FILE *file = fopen("products.dat", "rb");
	if(!file) {
		printf("No hay productos registrados \n");
		return;
	}

	FILE *tempFile = fopen("temp.dat", "wb");
	if (!tempFile) {
		printf("Error al crear archivo temporal.\n");
		fclose(file);
		return;
	}

	int idToDelete, found;
	printf("Ingrese el ID del producto a eliminar: ");
	scanf("%d", &idToDelete);

	Product p;
	found = 0;

	while (fread(&p, sizeof(Product), 1, file)) {
		if (p.id == idToDelete) {
			found = 1;
			printf("Producto eliminado correctamente.\n");
		} else {
			fwrite(&p, sizeof(Product), 1, tempFile); // Guardamos solo los productos que NO se eliminan
		}
	}

	fclose(file);
	fclose(tempFile);

	if (found) {
		remove("products.dat");  // Eliminamos el archivo original
		rename("temp.dat", "products.dat"); // Renombramos el temporal
	} else {
		printf("Producto con ID %d no encontrado.\n", idToDelete);
		remove("temp.dat"); // Eliminamos el archivo temporal si no hubo cambios
	}
}

// Función para actualizar un producto
void updateProduct() {
	FILE *file = fopen("products.dat", "rb");
	if (!file) {
		printf("No hay productos registrados.\n");
		return;
	}

	FILE *tempFile = fopen("temp.dat", "wb");
	if (!tempFile) {
		printf("Error al crear archivo temporal.\n");
		fclose(file);
		return;
	}

	int idToUpdate;
	printf("Ingrese el ID del producto a actualizar: ");
	scanf("%d", &idToUpdate);

	Product p;
	int found = 0;

	while (fread(&p, sizeof(Product), 1, file)) {
		if (p.id == idToUpdate) {
			found = 1;
			printf("Ingrese el nuevo nombre: ");
			scanf(" %[^\n]", p.name);
			printf("Ingrese la nueva descripcion: ");
			scanf(" %[^\n]", p.desc);
			printf("Ingrese el nuevo precio: ");
			scanf("%f", &p.price);
			printf("Ingrese el nuevo codigo de barras: ");
			scanf("%s", p.bar_code);
			printf("Producto actualizado exitosamente.\n");
		}
		fwrite(&p, sizeof(Product), 1, tempFile);
	}

	fclose(file);
	fclose(tempFile);

	if (found) {
		remove("products.dat");
		rename("temp.dat", "products.dat");
	} else {
		printf("Producto con ID %d no encontrado.\n", idToUpdate);
		remove("temp.dat");
	}
}

// funcion para opciones del programa
void menu() {
	int option;

	do {
		printf("\n--- Menu ---\n");
		printf("1. Agregar Producto\n");
		printf("2. Mostrar Productos\n");
		printf("3. Actualizar Producto\n");
		printf("4. Eliminar Producto\n");
		printf("5. Mostrar configuracion del sistema.\n");
		printf("6. Elminar configuracion\n");
		printf("7. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &option);

		switch (option) {
			case 1:
				addProduct();
				break;
			case 2:
				showProducts();
				break;
			case 3:
				updateProduct();
				break;
			case 4:
				deleteProduct();
				break;
			case 5:
				showConfig();
				break;
			case 6:
				deleteConfig();
				break;
			case 7:
				printf("Saliendo...\n");
				break;
			default:
				printf("Opcion invalida.\n");
		}
	} while (option != 7);
}


int main() {
	int config, validated;
	config = 0;
	validated = 0;
	printf("Bienvenido a tu terminal punto de venta \n");
	// Valida configuración
	if (isConfigured()) {
		printf("Sistema configurado.\n");
	} else {
		printf("El sistema NO esta configurado. Iniciando configuracion...\n");
		configSystem();
		config = 1;
	}
	// Valida Autentificación de usuario
	if(!validatedUser()) {
		validatedUser();
		validated = 1;
	}

	do {
		menu();
	} while(config != 0 && validated != 0);


	return 0;
}
