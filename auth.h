// Author: 241524002 / Afriza Choirie Saputra

#ifndef AUTH_H
#define AUTH_H
#include "header.h"

extern struct User currentUser;

void auth();
void registerUser();
void loginUser();
void hashPassword(const char *password, char *hashedPassword);
void logout();

#endif
