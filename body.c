#include <stdio.h>
#include <stdlib.h>
#include "header.h"

static struct Produk listProduk[28] = {
    {
        1,                  // id
        "beras putih 5 kg", // nama
        "sembako",          // kategori
        80000,              // harga
    },
    {
        2,                  // id
        "beras merah 2 kg", // nama
        "sembako",          // kategori
        50000,              // harga
    },
    {
        3,                 // id
        "gula pasir 1 kg", // nama
        "sembako",         // kategori
        20000,             // harga
    },
    {
        4,                 // id
        "gula merah 1 kg", // nama
        "sembako",         // kategori
        30000,             // harga
    },
    {
        5,                       // id
        "minyak goreng 2 liter", // nama
        "sembako",               // kategori
        40000,                   // harga
    },
    {
        6,                       // id
        "minyak goreng 1 liter", // nama
        "sembako",               // kategori
        20000,                   // harga
    },
    {
        7,                        // id
        "telur ayam negeri 1 kg", // nama
        "sembako",                // kategori
        20000,                    // harga
    },
    {
        8,                         // id
        "telur ayam kampung 1 kg", // nama
        "sembako",                 // kategori
        60000,                     // harga
    },
    {
        9,                // id
        "indomie goreng", // nama
        "sembako",        // kategori
        2500,             // harga
    },
    {
        10,                    // id
        "indomie ayam bawang", // nama
        "sembako",             // kategori
        2500,                  // harga
    },
    {
        11,            // id
        "kecap manis", // nama
        "sembako",     // kategori
        10000,         // harga
    },
    {
        12,           // id
        "kecap asin", // nama
        "sembako",    // kategori
        12000,        // harga
    },
    {
        13,                             // id
        "sabun lifebouy botol 100 ml",  // nama
        "perlengkapan mandi & mencuci", // kategori
        20000,                          // harga
    },
    {
        14,                             // id
        "shampoo clear botol 100 ml",   // nama
        "perlengkapan mandi & mencuci", // kategori
        20000,                          // harga
    },
    {
        15,                  // id
        "kayu putih 210 ml", // nama
        "obat-obatan",       // kategori
        75000,               // harga
    },
    {
        16,            // id
        "komix",       // nama
        "obat-obatan", // kategori
        1500,          // harga
    },
    {
        17,                      // id
        "panadol tablet isi 10", // nama
        "obat-obatan",           // kategori
        10000,                   // harga
    },
    {
        18,                // id
        "moring original", // nama
        "makanan ringan",  // kategori
        1000,              // harga
    },
    {
        19,               // id
        "moring pedas",   // nama
        "makanan ringan", // kategori
        1000,             // harga
    },
    {
        20,               // id
        "chuba",          // nama
        "makanan ringan", // kategori
        1000,             // harga
    },
    {
        21,        // id
        "panther", // nama
        "minuman", // kategori
        1000,      // harga
    },
    {
        22,        // id
        "power f", // nama
        "minuman", // kategori
        1000,      // harga
    },
    {
        23,        // id
        "kopikap", // nama
        "minuman", // kategori
        1000,      // harga
    },
    {
        24,                           // id
        "sampoerna filter 16 batang", // nama
        "rokok",                      // kategori
        27000,                        // harga
    },
    {
        25,                              // id
        "djarum super filter 12 batang", // nama
        "rokok",                         // kategori
        25000,                           // harga
    },
    {
        26,                  // id
        "bumbu nasi goreng", // nama
        "bumbu dapur",       // kategori
        2500,                // harga
    },
    {
        27,                  // id
        "bumbu ayam goreng", // nama
        "bumbu dapur",       // kategori
        5000,                // harga
    },
    {
        28,                  // id
        "bumbu ikan goreng", // nama
        "bumbu dapur",       // kategori
        4000,                // harga
    },
};

static struct User currentUser;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// auth

void auth()
{

    clearScreen();
    puts("**************************GUDANG GARAM JAYA********************************\n");
    puts("Input '1' untuk Register");
    puts("Input '2' untuk Login\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        registerUser();
        break;
    case 2:
        loginUser();
        break;
    default:
        auth();
        break;
    }
}

void registerUser()
{
    clearScreen();

    FILE *file = fopen(USER_DATABASE, "ab");
    
    struct User user;

    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char namaLengkap[50];
    char alamat[100];
    char nomorTelepon[20];

    puts("**************************REGISTER********************************\n");
    printf("Masukkan email (tidak boleh ada spasi): ");
    scanf("%s", email);
    printf("Masukkan password (tidak boleh ada spasi): ");
    scanf("%s", password);
    getchar();
    printf("Masukkan nama lengkap: ");
    fgets(namaLengkap, 50, stdin);
    printf("Masukkan alamat: ");
    fgets(alamat, 100, stdin);
    printf("Masukkan nomor telepon: ");
    fgets(nomorTelepon, 20, stdin);
    
    char hashedPassword[33];
    hashPassword(password, hashedPassword);
    
    strcpy(user.email, email);
	strcpy(user.password, hashedPassword);
	strcpy(user.namaLengkap, namaLengkap);
	strcpy(user.alamat, alamat);
	strcpy(user.nomorTelepon, nomorTelepon);

	fwrite(&user, sizeof(struct User), 1, file);
    fclose(file);

    loginUser();
}

void loginUser()
{
    clearScreen();

    FILE *file = fopen(USER_DATABASE, "rb");
    
    struct User user;
    
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loginSuccess = 0;

    puts("**************************LOGIN********************************\n");
    printf("Masukkan email (tidak boleh ada spasi): ");
    scanf("%s", email);
    printf("Masukkan password (tidak boleh ada spasi): ");
    scanf("%s", password);
    getchar();
    
    char hashedPassword[33];
    hashPassword(password, hashedPassword);

	while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(email, user.email) == 0 && strcmp(hashedPassword, user.password) == 0) {
        	currentUser = user;
            loginSuccess = 1;
            break;
        }
    }

    fclose(file);

    if (loginSuccess)
    {
        dashboard();
    }
    else
    {
        puts("\nEmail atau Password salah.");
        puts("Input '1' untuk coba lagi");
        puts("Input '2' untuk kembali\n");
        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            loginUser();
            break;
        case 2:
            auth();
            break;
        default:
            break;
        }
    }
}

void hashPassword(const char *password, char *hashedPassword) {
	int length = strlen(password);
    int i;
    for (i = 0; i < 32; i++) {
        hashedPassword[i] = (password[i % length] ^ (i + 1)) % 94 + 33;
    }
    hashedPassword[32] = '\0';
}

void logout()
{
	strcpy(currentUser.email, "");
	strcpy(currentUser.password, "");
	strcpy(currentUser.namaLengkap, "");
	strcpy(currentUser.alamat, "");
	strcpy(currentUser.nomorTelepon, "");
	
    auth();
}

// dashboard

void dashboard()
{
    clearScreen();
    puts("**************************DASHBOARD********************************\n");
    puts("Input '1' untuk List Produk");
    puts("Input '2' untuk Cari Produk");
    puts("Input '3' untuk Keranjang");
    puts("Input '4' untuk Akun");
    puts("Input '5' untuk Keluar\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        list();
        break;
    case 2:
        search();
        break;
    case 3:
        cartFunction();
        break;
    case 4:
        akun();
        break;
    case 5:
        exitProgram();
        break;
    default:
        break;
    }
}

void list()
{
    kategori();
}

void search()
{
    getSearchKeyword();
}

void cartFunction()
{
    clearScreen();
    puts("**************************KERANJANG********************************\n");

    struct Produk cart[28];
    struct CartDatabase cartDatabase[28];
    getCart(cart, cartDatabase);

    if (cart[0].id == 0)
    {
        puts("Keranjang kosong.\n");
        puts("Input '1' untuk List Produk");
        puts("Input '2' untuk Cari Produk");
        puts("Input '0' untuk kembali ke dashboard\n");

        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 0:
            dashboard();
            break;
        case 1:
            list();
            break;
        case 2:
            search();
            break;
        default:
            break;
        }
    }
    else
    {
        int totalHarga = 0;
        for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
        {
            if (cart[i].nama[0] != '\0')
            {
                totalHarga += cart[i].harga;
                printf("%d. %s\nRp%d\n\n", i + 1, cart[i].nama, cart[i].harga);
            }
        }

        printf("Total harga: Rp%d\n", totalHarga);

        puts("\nInput '1' untuk checkout");
        puts("Input '2' untuk hapus produk dari keranjang");
        puts("Input '0' untuk kembali ke dashboard\n");

        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 0:
            dashboard();
            break;
        case 1:
            checkout(totalHarga);
            break;
        case 2:
            deleteProductFromCart();
            break;
        default:
            break;
        }
    }
}

void akun()
{
    clearScreen();
    puts("**************************AKUN********************************\n");
    puts("Input '1' untuk Info Akun");
    puts("Input '2' untuk Edit Info Akun");
    puts("Input '3' untuk Ganti Password");
    puts("Input '4' untuk Info Aplikasi");
    puts("Input '5' untuk Pusat Bantuan");
    puts("Input '6' untuk Log Out");
    puts("Input '0' untuk kembali ke dashboard\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        infoAkun();
        break;
    case 2:
        editAkun();
        break;
    case 3:
        gantiPassword();
        break;
    case 4:
        infoAplikasi();
        break;
    case 5:
        pusatBantuan();
        break;
    case 6:
        logout();
        break;
    case 0:
        dashboard();
        break;
    default:
        break;
    }
}

void exitProgram()
{
    clearScreen();
    puts("Keluar dari program.");
    exit(0);
}

void detail(
    int id,
    char nama[],
    char kategori[],
    int harga)
{
    clearScreen();
    puts("**************************DETAIL PRODUK********************************\n");
    printf("Nama produk: %s\n", nama);
    printf("Kategori produk: %s\n", kategori);
    printf("Harga produk: Rp%d\n", harga);

    puts("\nInput '1' untuk tambah ke keranjang");
    puts("Input '0' untuk kembali ke dashboard");

    printf("\n");
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        dashboard();
        break;
    case 1:
        addToCart(id, nama);
        break;
    default:
        break;
    }
}

// list produk

void kategori()
{
    clearScreen();
    puts("**************************LIST PRODUK********************************\n");

    char *kategori[] = {"sembako", "perlengkapan mandi & mencuci", "obat-obatan", "makanan ringan", "minuman", "rokok", "bumbu dapur"};
    puts("Kategori:");
    for (int i = 0; i < 7; i++)
    {
        printf("%d. %s\n", i + 1, kategori[i]);
    }
    printf("\n");

    for (int i = 0; i < 7; i++)
    {
        printf("Input '%d' untuk melihat list produk %s\n", i + 1, kategori[i]);
    }
    puts("Input '0' untuk kembali");
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    if (input == 0)
    {
        dashboard();
    }
    else
    {
        char selectedCategory[50];
        strcpy(selectedCategory, kategori[input - 1]);
        listByKategori(selectedCategory);
    }
}

void listByKategori(char selectedCategory[])
{
    clearScreen();
    puts("**************************LIST PRODUK********************************\n");

    // collect list produk by kategori
    struct Produk listProdukByKategori[28];

    // remove weird characters within strings in listProdukByKategori
    for (int i = 0; i < (sizeof(listProdukByKategori) / sizeof(listProdukByKategori[0])); i++)
    {
        strcpy(listProdukByKategori[i].nama, "");
    }

    // the main filter algorithm
    int listProdukByKategoriIndex = 0;
    for (int i = 0; i < (sizeof(listProduk) / sizeof(listProduk[0])); i++)
    {
        if (strstr(listProduk[i].kategori, selectedCategory) != NULL)
        {
            listProdukByKategori[listProdukByKategoriIndex] = listProduk[i];
            listProdukByKategoriIndex++;
        }
    }

    printf("List %s:\n", selectedCategory);
    for (int i = 0; i < (sizeof(listProdukByKategori) / sizeof(listProdukByKategori[0])); i++)
    {
        if (listProdukByKategori[i].nama[0] != '\0')
        {
            printf("%d) %s\n", i + 1, listProdukByKategori[i].nama);
        }
    }
    printf("\n");

    for (int i = 0; i < (sizeof(listProdukByKategori) / sizeof(listProdukByKategori[0])); i++)
    {
        if (listProdukByKategori[i].nama[0] != '\0')
        {
            printf("Input '%d' untuk melihat detail %s\n", i + 1, listProdukByKategori[i].nama);
        }
    }
    puts("Input '0' untuk kembali");
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    if (input == 0)
    {
        kategori();
    }
    else
    {
        detail(
            listProdukByKategori[input - 1].id,
            listProdukByKategori[input - 1].nama,
            listProdukByKategori[input - 1].kategori,
            listProdukByKategori[input - 1].harga);
    }
}

// search

void getSearchKeyword()
{
    clearScreen();
    puts("**************************CARI PRODUK********************************\n");

    // get search keyword
    char keyword[50];
    printf("Masukkan keyword pencarian: ");
    gets(keyword);

    listBySearchKeyword(keyword);
}

void listBySearchKeyword(char keyword[])
{
    // collect search results
    struct Produk foundProduk[28];

    // remove weird characters within strings in foundProduk
    for (int i = 0; i < (sizeof(foundProduk) / sizeof(foundProduk[0])); i++)
    {
        strcpy(foundProduk[i].nama, "");
    }

    // the main searching algorithm
    int foundProdukIndex = 0;
    for (int i = 0; i < (sizeof(listProduk) / sizeof(listProduk[0])); i++)
    {
        if (strstr(listProduk[i].nama, keyword) != NULL)
        {
            foundProduk[foundProdukIndex] = listProduk[i];
            foundProdukIndex++;
        }
    }

    // print search results to console
    if (foundProduk[0].nama[0] == '\0')
    {
        puts("\nPencarian tidak ditemukan.");
        
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali ke dashboard\n");
        
        int input;
    	printf("Input: ");
    	scanf("%d", &input);
    	getchar();
    	
    	switch(input) {
    		case 1:
    			getSearchKeyword();
    			break;
    		case 0:
    			dashboard();
    			break;
    		default:
    			break;
		}
    }
    else
    {
        puts("\nHasil pencarian:");
        for (int i = 0; i < (sizeof(foundProduk) / sizeof(foundProduk[0])); i++)
        {
            if (foundProduk[i].nama[0] != '\0')
            {
                printf("%d) %s\n", i + 1, foundProduk[i].nama);
            }
        }
    }

    printf("\n");
    for (int i = 0; i < (sizeof(foundProduk) / sizeof(foundProduk[0])); i++)
    {
        if (foundProduk[i].nama[0] != '\0')
        {
            printf("Input '%d' untuk melihat detail %s\n", i + 1, foundProduk[i].nama);
        }
    }
    puts("Input '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    if (input == 0)
    {
        getSearchKeyword();
    }
    else
    {
        detail(
            foundProduk[input - 1].id,
            foundProduk[input - 1].nama,
            foundProduk[input - 1].kategori,
            foundProduk[input - 1].harga);
    }
}

// cart

void addToCart(int id, char nama[])
{
    clearScreen();

    FILE *file = fopen(CART_DATABASE, "a+");

    fprintf(file, "%s %d\n", currentUser.email, id);
    fclose(file);

    printf("\nBerhasil menambahkan %s ke keranjang.\n\n", nama);

    puts("Input '1' untuk lihat keranjang");
    puts("Input '0' untuk kembali ke dashboard\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        dashboard();
        break;
    case 1:
        cartFunction();
        break;
    default:
        break;
    }
}

void getCart(struct Produk outputCart[], struct CartDatabase cartDatabase[])
{
    // remove weird characters within strings in cart
    for (int i = 0; i < (sizeof(listProduk) / sizeof(listProduk[0])); i++)
    {
        strcpy(outputCart[i].nama, "");
    }

    // remove weird characters within strings in cart
    for (int i = 0; i < (sizeof(listProduk) / sizeof(listProduk[0])); i++)
    {
        strcpy(cartDatabase[i].email, "");
    }

    FILE *file = fopen(CART_DATABASE, "r");

    int fileId;
    char fileUserEmail[MAX_EMAIL_LENGTH];
    int outputCartIndex = 0;
    int cartDatabaseIndex = 0;

    while (fscanf(file, "%s %d", fileUserEmail, &fileId) != EOF)
    {
        strcpy(cartDatabase[cartDatabaseIndex].email, fileUserEmail);
        cartDatabase[cartDatabaseIndex].id = fileId;
        cartDatabaseIndex++;
        if (strcmp(fileUserEmail, currentUser.email) == 0)
        {
            for (int i = 0; i < (sizeof(listProduk) / sizeof(listProduk[0])); i++)
            {
                if (listProduk[i].id == fileId)
                {
                    outputCart[outputCartIndex] = listProduk[i];
                    outputCartIndex++;
                }
            }
        }
    }

    fclose(file);
}

void checkout(int totalHarga)
{
    clearScreen();
    puts("**************************CHECKOUT********************************\n");
    printf("Total harga: Rp%d\n\n", totalHarga);

    int uang;
    printf("Masukkan uang: Rp");
    scanf("%d", &uang);

    if (uang == totalHarga)
    {
        puts("\nUang anda pas.\n");
        puts("Terima kasih sudah berbelanja! :)");
    }
    else if (uang > totalHarga)
    {
        printf("\nKembalian Rp%d.\n\n", uang - totalHarga);
        puts("Terima kasih sudah berbelanja! :)");
    }
    else if (uang < totalHarga)
    {
        printf("\nUang anda kurang! Anda berhutang Rp%d ke warung ini!\n\n", totalHarga - uang);
        puts("BAYAR HUTANG AJG! :(");
    }
    else
    {
        puts("\nInvalid input.\n");
    }

    struct Produk cart[28];
    struct CartDatabase cartDatabase[28];
    getCart(cart, cartDatabase);

    struct CartDatabase newCartDatabase[28];

    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        strcpy(newCartDatabase[i].email, "");
    }

    int newCartDatabaseIndex = 0;
    for (int i = 0; i < (sizeof(cartDatabase) / sizeof(cartDatabase[0])); i++)
    {
        if (cartDatabase[i].email[0] != '\0')
        {
            if (strcmp(cartDatabase[i].email, currentUser.email) == 0)
            {
                continue;
            }
            else
            {
                strcpy(newCartDatabase[newCartDatabaseIndex].email, cartDatabase[i].email);
                newCartDatabase[newCartDatabaseIndex].id = cartDatabase[i].id;
                newCartDatabaseIndex++;
            }
        }
    }

    FILE *file = fopen(CART_DATABASE, "w");

    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        if (newCartDatabase[i].email[0] != '\0')
        {
            fprintf(file, "%s %d\n", newCartDatabase[i].email, newCartDatabase[i].id);
        }
    }

    fclose(file);

    puts("\nInput '0' untuk kembali ke dashboard\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        dashboard();
        break;
    default:
        break;
    }
}

void deleteProductFromCart()
{
    clearScreen();
    puts("**************************HAPUS PRODUK DARI KERANJANG********************************\n");

    struct Produk cart[28];
    struct CartDatabase cartDatabase[28];
    getCart(cart, cartDatabase);

    puts("\nProduk di keranjang:");
    for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
    {
        if (cart[i].nama[0] != '\0')
        {
            printf("%d. %s\n", i + 1, cart[i].nama);
        }
    }
    printf("\n");

    for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
    {
        if (cart[i].nama[0] != '\0')
        {
            printf("Input '%d' untuk menghapus %s dari keranjang\n", i + 1, cart[i].nama);
        }
    }
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    int removeId = cart[input - 1].id;

    struct CartDatabase newCartDatabase[28];

    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        strcpy(newCartDatabase[i].email, "");
    }

    int newCartDatabaseIndex = 0;
    for (int i = 0; i < (sizeof(cartDatabase) / sizeof(cartDatabase[0])); i++)
    {
        if (cartDatabase[i].email[0] != '\0')
        {
            if (cartDatabase[i].id == removeId && strcmp(cartDatabase[i].email, currentUser.email) == 0)
            {
                continue;
            }
            else
            {
                strcpy(newCartDatabase[newCartDatabaseIndex].email, cartDatabase[i].email);
                newCartDatabase[newCartDatabaseIndex].id = cartDatabase[i].id;
                newCartDatabaseIndex++;
            }
        }
    }

    FILE *file = fopen(CART_DATABASE, "w");

    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        if (newCartDatabase[i].email[0] != '\0')
        {
            fprintf(file, "%s %d\n", newCartDatabase[i].email, newCartDatabase[i].id);
        }
    }

    fclose(file);

    clearScreen();
    printf("\nBerhasil menghapus %s dari keranjang\n", cart[input - 1].nama);

    puts("\nInput '1' untuk melihat keranjang\n");

    int input2;
    printf("Input: ");
    scanf("%d", &input2);
    getchar();

    switch (input2)
    {
    case 1:
        cartFunction();
        break;
    default:
        break;
    }
}

// akun

void infoAkun() {
	clearScreen();
    puts("**************************INFO AKUN********************************\n");
    printf("Email         : %s\n", currentUser.email);
    printf("Nama Lengkap  : %s", currentUser.namaLengkap);
    printf("Alamat        : %s", currentUser.alamat);
    printf("Nomor Telepon : %s", currentUser.nomorTelepon);

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        akun();
        break;
    default:
        break;
    }
}

void editAkun() {
	clearScreen();
    puts("**************************EDIT AKUN********************************\n");
    printf("Nama Lengkap  : %s", currentUser.namaLengkap);
    printf("Alamat        : %s", currentUser.alamat);
    printf("Nomor Telepon : %s", currentUser.nomorTelepon);
    
    puts("\nInput '1' untuk Edit Nama Lengkap");
    puts("Input '2' untuk Edit Alamat");
    puts("Input '3' untuk Edit Nomor Telepon");
    puts("Input '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();
    
    struct User tempUser;
    FILE *file;
	// Buka file untuk membaca dan menulis ulang
    file = fopen(USER_DATABASE, "rb+");
    if (file == NULL) {
        file = fopen(USER_DATABASE, "wb+");  // Buat file baru jika tidak ada
        if (file == NULL) {
            printf("\nGagal membuka atau membuat file untuk pembaruan kata sandi.\n");
            return;
        }
    }
    
    char newValue[100];

    switch (input)
    {
    case 1:
    	printf("\nMasukkan nama lengkap baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.namaLengkap, newValue);
        while (fread(&tempUser, sizeof(struct User), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(struct User), SEEK_CUR);  // Kembali ke posisi sebelumnya
	            fwrite(&currentUser, sizeof(struct User), 1, file);  // Tulis data pengguna baru
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 2:
    	printf("\nMasukkan alamat baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.alamat, newValue);
        while (fread(&tempUser, sizeof(struct User), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(struct User), SEEK_CUR);  // Kembali ke posisi sebelumnya
	            fwrite(&currentUser, sizeof(struct User), 1, file);  // Tulis data pengguna baru
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 3:
    	printf("\nMasukkan nomor telepon baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.nomorTelepon, newValue);
        while (fread(&tempUser, sizeof(struct User), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(struct User), SEEK_CUR);  // Kembali ke posisi sebelumnya
	            fwrite(&currentUser, sizeof(struct User), 1, file);  // Tulis data pengguna baru
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 0:
        akun();
        break;
    default:
        break;
    }
}

void gantiPassword() {
	clearScreen();
	puts("**************************GANTI PASSWORD********************************\n");
	
	char currentPassword[100], newPassword[100], confirmPassword[100], hashedPassword[33];
    FILE *file;
    struct User tempUser;
    int found = 0;
    
    printf("Masukkan password saat ini: ");
    scanf("%s", currentPassword);
    
    // Hash kata sandi saat ini dan validasi
    hashPassword(currentPassword, hashedPassword);
    
    if (strcmp(hashedPassword, currentUser.password) != 0) {
        printf("\nKata sandi salah!\n");
        
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali\n");

	    int input;
	    printf("Input: ");
	    scanf("%d", &input);
	    getchar();
	
	    switch (input)
	    {
	    case 1:
	    	gantiPassword();
	    case 0:
	        akun();
	        break;
	    default:
	        break;
	    }
    }

    printf("Masukkan password baru: ");
    scanf("%s", newPassword);
    printf("Konfirmasi password baru: ");
    scanf("%s", confirmPassword);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("\nKata sandi tidak cocok!\n");
        
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali\n");

	    int input;
	    printf("Input: ");
	    scanf("%d", &input);
	    getchar();
	
	    switch (input)
	    {
	    case 1:
	    	gantiPassword();
	    case 0:
	        akun();
	        break;
	    default:
	        break;
	    }
    } else {
        // Hash kata sandi baru
        hashPassword(newPassword, currentUser.password);

        // Buka file untuk membaca dan menulis ulang
        file = fopen(USER_DATABASE, "rb+");
        if (file == NULL) {
            file = fopen(USER_DATABASE, "wb+");  // Buat file baru jika tidak ada
            if (file == NULL) {
                printf("\nGagal membuka atau membuat file untuk pembaruan kata sandi.\n");
                return;
            }
        }

        // Cari pengguna dan perbarui password
        while (fread(&tempUser, sizeof(struct User), 1, file)) {
            if (strcmp(tempUser.email, currentUser.email) == 0) {
                fseek(file, -sizeof(struct User), SEEK_CUR);  // Kembali ke posisi sebelumnya
                fwrite(&currentUser, sizeof(struct User), 1, file);  // Tulis data pengguna dengan password baru
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            printf("\nKata sandi berhasil diubah!\n");
        } else {
            printf("\nPengguna tidak ditemukan!\n");
        }
    }
    
    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        akun();
        break;
    default:
        break;
    }
}

void infoAplikasi()
{
    clearScreen();
    puts("**************************INFO APLIKASI********************************\n");
    puts("Nama Aplikasi         : WARUNG GUDANG GARAM JAYA!");
    puts("Deskripsi Aplikasi    : Platform e-commerce untuk toko kelontong WARUNG GUDANG GARAM JAYA!");
    puts("Versi Aplikasi        : 1.0");

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        akun();
        break;
    default:
        break;
    }
}

void pusatBantuan()
{
    clearScreen();
    puts("**************************PUSAT BANTUAN********************************\n");
    puts("Email         : cs@gudanggaramjaya.com");
    puts("Nomor Telepon : 021-120");
    puts("SMS           : 021120");
    puts("Website       : www.warungmadura.com/help");

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        akun();
        break;
    default:
        break;
    }
}

