#ifndef POS_UI_H
#define POS_UI_H

#include "pos.model.h"   // o donde tengas Cart definido
#include "pos.service.h" // o donde tengas las funciones de servicio

char *pos_get_barcode_input_ui();
int get_quantity_input_ui(int isAdd);
void show_cart_summary_ui(Cart *cart);
void show_message_ui(const char *message);
void show_error_ui(const char *error_message);
float get_payment_amount_ui(float total);
int show_confirm_product(Product *product);
void show_change_ui(float change);
void show_cart_invoice_ui(float subtotal, float tax, float savings,
                          float total);

int show_pos_menu_ui();
void show_cart_detail_ui(Cart *cart);
void generate_ticket_ui(Cart *cart, Breakdown breakdown, float payment,
                        float change, char *nameBusiness);

#endif
