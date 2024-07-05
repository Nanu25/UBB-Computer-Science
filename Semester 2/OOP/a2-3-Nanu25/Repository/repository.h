#pragma once

#include "../Domain/domain.h"
#include "../DynamicArray/Dynamic_array.h"


void Add(DynamicArray *product_list, Product x);
int Remove(DynamicArray *product_list, char *name, char *category);
int Update(DynamicArray *product_list, char *name, char *category, int new_quantity, char *new_date);
