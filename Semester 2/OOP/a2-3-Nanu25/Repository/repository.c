#pragma once
#include <string.h>
#include "repository.h"

void Add(DynamicArray *product_list, Product x) {

    int position = Find(product_list, getName(&x), getCategory(&x));
    if(position == -1)
        add(product_list, x);
    else {
        product_list->product[position].quantity += getQuantity(&x);
        if(strcmp(getName(&product_list->product[position]), getDate(&x)) > 0)
            strcpy(product_list->product[position].date, getDate(&x));
    }
}


int Remove(DynamicArray *product_list, char *name, char *category) {
    int position = Find(product_list, name, category);
    if(position != -1)
        remove_product(product_list, name, category, position);
    else return -1;

    return 1;

}

int Update(DynamicArray *product_list, char *name, char *category, int new_quantity, char *new_date) {
    int position = Find(product_list, name, category);
    if(position != -1)
        Update_product(product_list, name, category, new_quantity, new_date, position);
    else return -1;
    return 1;
}

