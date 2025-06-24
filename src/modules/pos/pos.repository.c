#include "includes/pos.repository.h"
#include "../../utils/logger.h"
#include <stdlib.h>

Cart *create_cart_repository() {
  Cart *cart = (Cart *)malloc(sizeof(Cart));
  if (!cart) {
    LOG_ERROR("No se pudo asignar memoria para el carrito");
    return NULL;
  };

  LOG_INFO("Creando un nuevo carrito");
  cart->items = NULL;
  cart->count = 0;
  return cart;
}

int add_product_to_cart_repository(Cart *cart, Product *product, int quantity) {
  if (!cart || !product || quantity <= 0) {
    LOG_ERROR("No se pudo agregar el producto al carrito");
    return -1;
  };

  CartItem *existing = find_product_in_cart_repository(cart, product->id);
  if (existing) {
    existing->quantity += quantity;
    return 0;
  }

  CartItem *newItem = (CartItem *)malloc(sizeof(CartItem));
  if (!newItem) {
    LOG_ERROR("No se pudo asignar memoria para el nuevo item del carrito");
    return -1;
  };

  newItem->product = product;
  newItem->quantity = quantity;

  CartItem **updatedItems =
      (CartItem **)realloc(cart->items, (cart->count + 1) * sizeof(CartItem *));
  if (!updatedItems) {
    LOG_ERROR("No se pudo asignar memoria para los items del carrito");
    free(newItem);
    return -1;
  }

  cart->items = updatedItems;
  cart->items[cart->count] = newItem;
  cart->count++;
  LOG_INFO("El producto ha sido agregado al carrito");
  return 0;
}

int remove_product_from_cart_repository(Cart *cart, int product_id,
                                        int quantity) {
  if (!cart || cart->count == 0 || quantity <= 0) {
    LOG_ERROR("No se puede eliminar el producto del carrito");
    return -1;
  }

  for (int i = 0; i < cart->count; i++) {
    if (cart->items[i]->product->id == product_id) {
      if (cart->items[i]->quantity > quantity) {
        cart->items[i]->quantity -= quantity;
        return 0;
      } else {
        // Eliminar el item completo
        free(cart->items[i]);
        for (int j = i; j < cart->count - 1; j++) {
          cart->items[j] = cart->items[j + 1];
        }
        cart->count--;

        if (cart->count == 0) {
          free(cart->items);
          cart->items = NULL;
        } else {
          CartItem **updatedItems =
              realloc(cart->items, cart->count * sizeof(CartItem *));
          if (updatedItems) {
            cart->items = updatedItems;
          }
        }
        return 0;
      }
    }
  }

  LOG_ERROR("No se pudo eliminar el producto del carrito");
  return -1;
}

void clear_cart_repository(Cart *cart) {
  if (!cart) {
    LOG_ERROR("No se puede limpiar el carrito");
    return;
  };

  for (int i = 0; i < cart->count; i++) {
    free(cart->items[i]);
  }
  free(cart->items);
  cart->items = NULL;
  cart->count = 0;
  LOG_INFO("El carrito ha sido limpiado");
}

CartItem *find_product_in_cart_repository(Cart *cart, int product_id) {
  if (!cart || cart->count == 0) {
    LOG_ERROR("No se puede encontrar el producto en el carrito");
    return NULL;
  };

  for (int i = 0; i < cart->count; i++) {
    if (cart->items[i]->product->id == product_id) {
      return cart->items[i];
    }
  }
  LOG_ERROR("No se pudo encontrar el producto en el carrito");
  return NULL;
}
