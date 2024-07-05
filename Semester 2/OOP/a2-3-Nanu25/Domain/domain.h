#pragma once

typedef struct {
    char name[50];
    char category[50];
    int quantity;
    char date[50];
}Product;

//Getters.
char *getName(Product *x);
char *getCategory(Product *x);
int getQuantity(Product *x);
char *getDate(Product *x);

Product createProduct(char *name, char *category, int quantity, char *date);