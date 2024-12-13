#ifndef HEADER_H
#define HEADER_H

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
#define PRODUCT_DATABASE "product_database.txt"
#define REKAP_PENJUALAN_DATABASE "rekap_penjualan_database.txt"

struct Produk
{
    int id;
    char nama[50];
    char kategori[50];
    int harga;
    int stock;
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

#endif
