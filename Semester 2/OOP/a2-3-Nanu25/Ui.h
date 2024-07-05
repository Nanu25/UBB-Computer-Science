#pragma once
#include "Repository/repository.h"


void Ui_start(DynamicArray *product_list, UndoRedoDynamicArray *undo_list,  UndoRedoDynamicArray *redo_list);

//Display the menu of options.
void Display_menu();

//Input: A dynamic array which represent a produc list.
void print_list(DynamicArray product_list);

//Generates 10 products and add them to the initial repository.
void init_list(DynamicArray *product_list);