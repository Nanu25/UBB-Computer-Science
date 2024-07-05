#pragma once
#include "../Domain/domain.h"

typedef Product TElement;

typedef struct
{
    TElement* product;
    int length;			// actual length of the array
    int capacity;
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(DynamicArray* arr);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add(DynamicArray* arr, TElement t);

int getLength(DynamicArray* arr);
int getCapacity(DynamicArray* arr);

int Find(DynamicArray *product_list, char *name, char *category);
void remove_product(DynamicArray *product_list, char *name, char *category, int position);
void Update_product(DynamicArray *product_list, char *name, char *category, int new_quantity, char *new_date, int position);
DynamicArray* copyDynamicArray(DynamicArray* original);

// Tests
void testsDynamicArray();


typedef struct
{
    DynamicArray *elements;
    int size, capacity;
} UndoRedoDynamicArray;

UndoRedoDynamicArray* createUndoRedoDynamicArray(int capacity);

void addListToUndoRedoDynamicArray(UndoRedoDynamicArray* dynamicArray, DynamicArray *list);
void resizeUndoRedoDynamicArray(UndoRedoDynamicArray *dynamicArray);
void destroyUndoRedoDynamicArray(UndoRedoDynamicArray *dynamicArray);
