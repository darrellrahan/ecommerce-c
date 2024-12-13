// Author: 241524006 / Darrell Rafa Raihan

#ifndef CART_H
#define CART_H
#include "header.h"

void addToCart(int id, char nama[]);
void getCart(struct Produk outputCart[], struct CartDatabase cartDatabase[]);
void checkout(int totalHarga);
void deleteProductFromCart();

#endif
