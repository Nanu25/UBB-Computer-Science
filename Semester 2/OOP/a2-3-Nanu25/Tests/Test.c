#include "Tests/Test.h"
#include <assert.h>
#include <string.h>
#include "Domain/domain.h"
#include "DynamicArray/Dynamic_array.h"
#include "Repository/repository.h"
#include "Service/service.h"

void test_domain() {
    Product x = createProduct("corn", "sweets", 20, "2024/1/10");
    assert(strcmp(getName(&x), "corn") == 0);
    assert(strcmp(getCategory(&x), "sweets") == 0);
    assert(getQuantity(&x) == 20);
    assert(strcmp(getDate(&x), "2024/1/10") == 0);
}

void test_repo() {
    Product x = createProduct("corn", "sweets", 20, "2024/1/10");
    DynamicArray *prod_list = createDynamicArray(1);
    Add(prod_list, x);
    assert(prod_list->length == 1);
    Update(prod_list, "corn", "sweets", 10, "2020/1/10");
    assert(getQuantity(&prod_list->product[0]) == 10);
    assert(strcmp(getDate(&prod_list->product[0]), "2020/1/10") == 0);
    Remove(prod_list, "corn", "sweets");
    assert(prod_list->length == 0);
}

void test_service() {
    Product x = createProduct("corn", "sweets", 20, "2024/1/10");
    DynamicArray *prod_list = createDynamicArray(1);
    add_product(prod_list, x);
    assert(prod_list->length == 1);
    update_product(prod_list, "corn", "sweets", 10, "2020/1/10");
    assert(getQuantity(&prod_list->product[0]) == 10);
    assert(strcmp(getDate(&prod_list->product[0]), "2020/1/10") == 0);
    Remove_product(prod_list, "corn", "sweets");
    assert(prod_list->length == 0);

    x = createProduct("corn", "sweets", 20, "2024/1/10");
    Product y = createProduct("milk", "dairy", 1, "2020/1/1");
    Product z = createProduct("cheese", "dairy", 3, "2030/1/1");


    add_product(prod_list, x);
    add_product(prod_list, y);
    add_product(prod_list, z);

    DynamicArray *s_string = search_string(prod_list, "");
    assert(s_string->product[0].quantity == 1);

    DynamicArray *fil_string = filter_products(prod_list, "dairy", "2050/1/1", 1);
    assert(strcmp(getName(&fil_string->product[0]), "cheese") == 0);

    fil_string = filter_quantity(prod_list, 1);
    assert(getQuantity(&s_string->product[0]) == 1);

}

void test_undo_redo() {
    DynamicArray *prod_list = createDynamicArray(1);
    Product y = createProduct("milk", "dairy", 1, "2020/1/1");
    Product z = createProduct("cheese", "dairy", 3, "2030/1/1");
    add_product(prod_list, y);
    add_product(prod_list, z);

    UndoRedoDynamicArray *undo_list = createUndoRedoDynamicArray(1), *redo_list = createUndoRedoDynamicArray(1);
    DynamicArray *last_repo = createDynamicArray(1);
    last_repo = copyDynamicArray(prod_list);
    add_undo(undo_list, last_repo);

    Product x = createProduct("corn", "sweets", 20, "2024/1/10");
    add_product(prod_list, x);
    last_repo = copyDynamicArray(prod_list);
    add_undo(undo_list, last_repo);
    make_undo(undo_list, redo_list);
    assert(undo_list->size == 1);

    make_redo(redo_list, undo_list);
    assert(undo_list->size == 2);

}


void test_all() {
    test_domain();
    test_repo();
    test_service();
    test_undo_redo();
}




