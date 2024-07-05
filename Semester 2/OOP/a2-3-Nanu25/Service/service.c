#include <string.h>
#include <stdio.h>
#include "service.h"

void add_product(DynamicArray *repo, Product x) {
    Add(repo, x);
}

int Remove_product(DynamicArray *repo, char *name, char *category) {
    int aux = Remove(repo, name, category);
    return aux;
}

int update_product(DynamicArray *repo, char *name, char *category, int new_quantity, char *new_date) {
    int aux = Update(repo, name, category, new_quantity, new_date);
    return aux;
}

DynamicArray *search_string(DynamicArray *product_list, char *sub_string) {
    DynamicArray *new_list = createDynamicArray(1);

    //Make the letter from the string lower.
    int lg = strlen(sub_string);
    for(int i = 0; i < lg; i++)
        if(&sub_string[i] >= 'A' && &sub_string[i] <= 'Z')
            sub_string[i] += 32;

    //Create a new list with the name i need.
    for(int i = 0; i < product_list->length; i++)
        if(strstr(product_list->product[i].name, sub_string) != NULL)
            add_product(new_list, product_list->product[i]);

    // Bubble sort the new_list by quantity
    for (int i = 0; i < new_list->length - 1; i++) {
        for (int j = 0; j < new_list->length - i - 1; j++) {
            if (getQuantity(&new_list->product[j]) > getQuantity(&new_list->product[j + 1])) {
                Product aux = new_list->product[j];
                new_list->product[j] = new_list->product[j + 1];
                new_list->product[j + 1] = aux;
            }
        }
    }

    return new_list;
}

DynamicArray *filter_products(DynamicArray *product_list, char *category, char *x, int sort) {
    DynamicArray *result = createDynamicArray(1);

    for(int i = 0; i < product_list->length; i++) {
        if ((strcmp(getCategory(&product_list->product[i]), category) == 0 || strcmp(category, "") == 0)
            && strcmp(getDate(&product_list->product[i]), x) < 0) {
            Add(result, product_list->product[i]);
        }
    }

    if(sort == 1) {
        //Sort the repository using bubble sort
        for (int i = 0; i < result->length - 1; i++) {
            for (int j = 0; j < result->length - i - 1; j++) {
                if (strcmp(getDate(&result->product[j]), getDate(&result->product[j + 1])) < 0) {
                    Product aux = result->product[j];
                    result->product[j] = result->product[j + 1];
                    result->product[j + 1] = aux;
                }
            }
        }
    }

    return result;
}

DynamicArray *filter_quantity(DynamicArray *product_list, int min_quantity) {
    DynamicArray *result = createDynamicArray(1);

    for(int i = 0; i < product_list->length; i++)
        if(getQuantity(&product_list->product[i]) >= min_quantity) {
            Add(result, product_list->product[i]);
        }

    //Sort the repository using bubble sort
    for (int i = 0; i < result->length - 1; i++) {
        for (int j = 0; j < result->length - i - 1; j++) {
            if (result->product[j].quantity >= result->product[j + 1].quantity) {
                Product aux = result->product[j];
                result->product[j] = result->product[j + 1];
                result->product[j + 1] = aux;
            }
        }
    }

    return result;
}

void add_undo(UndoRedoDynamicArray *undo_list, DynamicArray *Repository) {
    addListToUndoRedoDynamicArray(undo_list, Repository);
}

DynamicArray *make_undo(UndoRedoDynamicArray *undo_list, UndoRedoDynamicArray *redo_list) {
    if(undo_list->size == 1)
        return NULL;

    //Save the current list for the redo function.
    DynamicArray *last_repo = createDynamicArray(1);
    for(int i = 0; i < undo_list->elements[undo_list->size - 1].length; i++)
        add(last_repo, undo_list->elements[undo_list->size - 1].product[i]);
    add_redo(redo_list, last_repo);
    undo_list->size--;


    last_repo = createDynamicArray(1);
    for(int i = 0; i < undo_list->elements[undo_list->size - 1].length; i++)
        add(last_repo, undo_list->elements[undo_list->size - 1].product[i]);

    return last_repo;
}

void add_redo(UndoRedoDynamicArray *redo_list, DynamicArray *Repository) {
    addListToUndoRedoDynamicArray(redo_list, Repository);
}

DynamicArray *make_redo(UndoRedoDynamicArray *redo_list, UndoRedoDynamicArray *undo_list) {
    if(redo_list->size == 0)
        return NULL;

    DynamicArray *last_repo = createDynamicArray(1);
    for(int i = 0; i < redo_list->elements[redo_list->size - 1].length; i++)
        add(last_repo, redo_list->elements[redo_list->size - 1].product[i]);
    redo_list->size--;
    add_undo(undo_list, last_repo);

    return last_repo;
}




