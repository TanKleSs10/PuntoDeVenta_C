#ifndef USER_MODEL_H
#define USER_MODEL_H

typedef enum {
    ADMIN = 1,
    CASHIER = 2,
    SUPERADMIN = 3
} UserRole;


typedef struct {
    int id;
    char username[20];
    char password[20];
    UserRole role;
} User;

#endif
