#pragma once
#include "Domain/domain.h"
#include <string.h>

char* getName(Product *x) {
    return x->name;
}

char* getCategory(Product *x) {
    return x->category;
}

int getQuantity(Product *x) {
    return x->quantity;
}

char *getDate(Product *x) {
    return x->date;
}

Product createProduct(char *name, char *category, int quantity, char *date) {
    Product x;
    strcpy(x.name, name);
    strcpy(x.category, category);
    x.quantity = quantity;
    strcpy(x.date, date);

    return x;
}


