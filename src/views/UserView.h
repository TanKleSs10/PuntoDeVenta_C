#ifndef USERVIEW_H
#define USERVIEW_H

#include "../models/UserModel.h"

// Declaraciones para UserView (view)
void inputSuperUserData(User *user);

void inputUserData(User *user);

void inputUserDataForUpdate(User *user);

void showUserData(const User *user, int size);

int inputSearchUserDataByid();

char *inputSearchUserDataByName();

int inputSelectSearchUserData();

void showNoUserMessage();

void showMenuUser();

void showMenuSearchUser();

#endif
