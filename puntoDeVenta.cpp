#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un producto
typedef struct {
	int id;
	char name[50];
	char desc[100];
	char bar_code[13];
	float price;
} Product;

// Función para agregar un producto
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

// Función para mostrar la lista de productos
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

int main() {
	int option;

	do {
		printf("\n--- Menu ---\n");
		printf("1. Agregar Producto\n");
		printf("2. Mostrar Productos\n");
		printf("3. Salir\n");
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
				printf("Saliendo...\n");
				break;
			default:
				printf("Opcion inválida.\n");
		}
	} while (option != 3);

	return 0;
}
