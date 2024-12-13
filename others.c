#include <stdio.h>
#include <stdlib.h>
#include "others.h"

int jumlahProduk;

void getJumlahProduk(int *jumlahProduk) {
	FILE *file = fopen(PRODUCT_DATABASE, "r");
	
	struct Produk produk;

	*jumlahProduk = 0;
	while (fscanf(file, "%d,%49[^,],%49[^,],%d,%d\n",
                  &produk.id,
                  produk.nama,
                  produk.kategori,
                  &produk.harga,
                  &produk.stock) != EOF)
    {
        (*jumlahProduk)++;
    }

    fclose(file);
}

void clearScreen()
{
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

void exitProgram()
{
    clearScreen();
    puts("Keluar dari aplikasi.");
    exit(0);
}
