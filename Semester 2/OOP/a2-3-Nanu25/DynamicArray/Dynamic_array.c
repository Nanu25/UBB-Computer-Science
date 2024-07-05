#include "Dynamic_array.h"
#include <stdlib.h>
#include <assert.h>
#include <intrin.h>

DynamicArray* createDynamicArray(int capacity)
{
    DynamicArray* da = malloc(sizeof(DynamicArray));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;

    da->capacity = capacity;
    da->length = 0;

    // allocate space for the elements
    da->product = malloc(capacity * sizeof(TElement));
    if (da->product == NULL)
        return NULL;

    return da;
}

void destroy(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    // free the space allocated for the planets
    free(arr->product);
    arr->product = NULL;

    // free the space allocated for the dynamic array
    free(arr);
    //arr = NULL; // !!!
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    arr->capacity *= 2;
    TElement* aux = realloc(arr->product, arr->capacity * sizeof(TElement));
    if (aux == NULL)
        return;
    arr->product = aux;
}

void add(DynamicArray* arr, TElement t)
{
    if (arr == NULL)
        return;
    if (arr->product == NULL)
        return;

    // resize the array, if necessary
    if (arr->length == arr->capacity)
        resize(arr);
    arr->product[arr->length] = t;
    arr->length++;
}

int getLength(DynamicArray* arr)
{
    if (arr == NULL)
        return 0;
    return arr->length;
}

int getCapacity(DynamicArray* arr)
{
    if (arr == NULL)
        return 0;
    return arr->capacity;
}

void remove_product(DynamicArray *product_list, char *name, char *category, int position) {
    //Delete the current product
    for (int j = position; j < product_list->length; j++)
        product_list->product[j] = product_list->product[j + 1];
    product_list->length--;
}

int Find(DynamicArray *product_list, char *name, char *category) {
    for(int i = 0; i < product_list->length; i++)
        if(strcmp(getName(&product_list->product[i]), name) == 0 && strcmp(getCategory(&product_list->product[i]), category) == 0) {
            return i;
        }
    return -1;
}

void Update_product(DynamicArray *product_list, char *name, char *category, int new_quantity, char *new_date, int position) {
    product_list->product[position].quantity = new_quantity;
    strcpy(product_list->product[position].date, new_date);
}

DynamicArray* copyDynamicArray(DynamicArray* original) {
    if (original == NULL)
        return NULL;

    DynamicArray* copy = createDynamicArray(original->capacity);
    if (copy == NULL)
        return NULL;

    copy->length = original->length;
    for (int i = 0; i < original->length; i++) {
        copy->product[i] = original->product[i]; // No need for casting or malloc if TElement is Product
    }
    return copy;
}

void testsDynamicArray()
{
    DynamicArray* da = createDynamicArray(2);
    if (da == NULL)
        assert(0);

    assert(getCapacity(da) == 2);
    assert(getLength(da) == 0);

    Product p1 = createProduct("milk", "dairy", 10, "2020/1/1");
    add(da, p1);
    assert(getLength(da) == 1);

    Product p2 = createProduct("cheese", "dairy", 5, "2021/1/1");
    add(da, p2);
    assert(getLength(da) == 2);

    // capacity must double
    Product p3 = createProduct("cheese", "dairy", 5, "2021/1/1");
    add(da, p3);
    assert(getLength(da) == 3);
    assert(getCapacity(da) == 4);

    destroy(da);
}

UndoRedoDynamicArray* createUndoRedoDynamicArray(int capacity)
{
    UndoRedoDynamicArray* dynamicArray = malloc(sizeof(UndoRedoDynamicArray));

    if (dynamicArray == NULL)
        return NULL;

    dynamicArray->elements = malloc(capacity * sizeof(DynamicArray*));

    if (dynamicArray->elements == NULL)
        return NULL;

    dynamicArray->size = 0;
    dynamicArray->capacity=capacity;
    return dynamicArray;
}

void addListToUndoRedoDynamicArray(UndoRedoDynamicArray *dynamicArray, DynamicArray *list) {
    if (dynamicArray->size == dynamicArray->capacity)
        resizeUndoRedoDynamicArray(dynamicArray);

    dynamicArray->elements[dynamicArray->size].length = list->length;
    dynamicArray->elements[dynamicArray->size].capacity = list->capacity;
    dynamicArray->elements[dynamicArray->size].product = malloc(list->capacity * sizeof(Product));
    if (dynamicArray->elements[dynamicArray->size].product == NULL) {
        // Handle memory allocation failure
        return;
    }
    for (int i = 0; i < list->length; ++i) {
        dynamicArray->elements[dynamicArray->size].product[i] = list->product[i];
    }
    dynamicArray->size++;
}

void resizeUndoRedoDynamicArray(UndoRedoDynamicArray* dynamicArray) {
    if (dynamicArray == NULL)
        return;

    int newCapacity = dynamicArray->capacity * 2;

    DynamicArray *aux = malloc(newCapacity * sizeof(DynamicArray));

    for (int i = 0; i < dynamicArray->size; i++) {
        aux[i] = dynamicArray->elements[i];
    }
    free(dynamicArray->elements);

    dynamicArray->capacity = newCapacity;
    dynamicArray->elements = aux;
}

void destroyUndoRedoDynamicArray(UndoRedoDynamicArray* dynamicArray)
{
    if (dynamicArray == NULL)
        return;

    free(dynamicArray->elements);
    free(dynamicArray);
}