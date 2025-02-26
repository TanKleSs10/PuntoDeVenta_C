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



int main() {
	int option;

	do {
		printf("\n--- Menu ---\n");
		printf("1. Agregar Producto\n");
		printf("2. Mostrar Productos\n");
		printf("3. Actualizar Producto\n");
		printf("4. Eliminar Producto\n");
		printf("5. Salir\n");
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
				printf("Saliendo...\n");
				break;
			default:
				printf("Opcion inválida.\n");
		}
	} while (option != 5);

	return 0;
}
