#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define USER_DATABASE "user_database.dat"
#define CART_DATABASE "cart_database.txt"

struct Produk
{
    int id;
    char nama[50];
    char kategori[50];
    int harga;
};

struct CartDatabase
{
    char email[MAX_EMAIL_LENGTH];
    int id;
};

struct User
{
	char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char namaLengkap[50];
    char alamat[100];
    char nomorTelepon[20];	
};

void clearScreen();
// auth
void auth();
void registerUser();
void loginUser();
void hashPassword(const char *password, char *hashedPassword);
void logout();
// dashboard
void dashboard();
void list();
void search();
void cartFunction();
void akun();
void exitProgram();
void detail(
    int id,
    char nama[],
    char kategori[],
    int harga);
// list produk
void kategori();
void listByKategori(char selectedCategory[]);
// search
void getSearchKeyword();
void listBySearchKeyword(char keyword[]);
// cart
void addToCart(int id, char nama[]);
void getCart(struct Produk outputCart[], struct CartDatabase cartDatabase[]);
void checkout(int totalHarga);
void deleteProductFromCart();
// akun
void infoAkun();
void editAkun();
void gantiPassword();
void infoAplikasi();
void pusatBantuan();

#endif
