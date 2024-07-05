#pragma once

#include "../Repository/repository.h"

//Input: a repository list and a product.
//The function add the product x in the array.
void add_product(DynamicArray *repo, Product x);

//Input: a repository list and a product.
//The function remove the product x from the list if x exists in array.
int Remove_product(DynamicArray *repo, char *name, char *category);

//Input: a repository list and a product.
//The function update the product x from the list if x exists in array.
int update_product(DynamicArray *repo, char *name, char *category, int new_quantity, char *new_date);

//Input: a repository list and a substring.
//Output: The function return an array with all the products that contains the input substring.
DynamicArray *search_string(DynamicArray *product_list, char *sub_string);

//Input: a repository list a category, a date and a variable to say if we need to sort the result or not.
//Output: The function return an array with all the products that are from the given category and expires
//        before the x date.
DynamicArray *filter_products(DynamicArray *product_list, char *category, char *x, int sort);

//Input: a repository list and a quantity.
//Output: The function return an array with all the products that has quantity at least min_quantity.
DynamicArray *filter_quantity(DynamicArray *product_list, int min_quantity);

//Copy the actual repository in a dynamic array that stores dynamic arrays.
//Input: undo_list is a dynamic array that stores dynamic arrays.
void add_undo(UndoRedoDynamicArray *undo_list, DynamicArray *Repository);

//Perform an undo operation,saves in redo list the actual repository and return this repository.
DynamicArray *make_undo(UndoRedoDynamicArray *undo_list, UndoRedoDynamicArray *redo_list);

//Copy the actual repository in a dynamic array that stores dynamic arrays.
//Input: redo is a dynamic array that stores dynamic arrays.
void add_redo(UndoRedoDynamicArray *redo_list, DynamicArray *Repository);

//Perform an redo operation,saves in undo list the actual repository and return this repository.
DynamicArray *make_redo(UndoRedoDynamicArray *redo_list, UndoRedoDynamicArray *undo_list);