#include <stdio.h>
#include <string.h>
#include "Ui.h"
#include "Domain/domain.h"
#include "Service/service.h"
#include "Repository/repository.h"

void Display_menu() {
    printf("1 for add a new product\n");
    printf("2 for remove a new product\n");
    printf("3 for update a product\n");
    printf("4 for display all products whose name contains a given string\n");
    printf("5 for display all products from a given category, which expires before a date x\n");
    printf("6 for undo last operation\n");
    printf("7 for redo the last operation\n");
    printf("8 for display the product that has quantities at least x\n");   //bonus.
    printf("0 for exit\n");
}


void print_list(DynamicArray product_list) {
    printf("\n");
    for (int i = 0; i < product_list.length; ++i) {
        printf("Name is: %s\n", getName(&product_list.product[i]));
        printf("Category is: %s\n", getCategory(&product_list.product[i]));
        printf("Quantity: %d\n", getQuantity(&product_list.product[i]));
        printf("Date is: %s\n", getDate(&product_list.product[i]));
        printf("\n");
    }
}

void init_list(DynamicArray *product_list) {
    Product x = createProduct("corn", "sweets", 20, "2024/1/10");
    Product y = createProduct("milk", "dairy", 1, "2020/1/1");
    Product z = createProduct("cheese", "dairy", 3, "1999/1/1");


    add_product(product_list, x);
    add_product(product_list, y);
    add_product(product_list, z);
    add_product(product_list, createProduct("beef", "meat", 5, "2004/1/1"));
    add_product(product_list, createProduct("apple", "fruit", 40, "2010/10/2"));
    add_product(product_list, createProduct("chocolate", "sweets", 100, "2025/2/3"));
    add_product(product_list, createProduct("cherry", "fruit", 100, "2010/5/1"));
    add_product(product_list, createProduct("chips", "sweets", 50, "2015/2/3"));
    add_product(product_list, createProduct("mars", "sweets", 11, "1902/2/5"));
    add_product(product_list, createProduct("pear", "fruit", 15, "2021/2/13"));
}


void Ui_start(DynamicArray *product_list, UndoRedoDynamicArray *undo_list, UndoRedoDynamicArray *redo_list) {
    init_list(product_list);
    DynamicArray *last_repository = createDynamicArray(1);
    add_undo(undo_list, product_list);

    int ok = 1;
    while(ok) {
        Display_menu();
        int comand;
        printf("Tell the comand: ");
        scanf("%d", &comand);
        getchar();          //read the new line

        if(comand == 1) {
            char name[50], category[50], date[50];
            int quantity;
            printf("Tell the product name: ");
            scanf("%s", name);

            printf("Tell the category type: ");
            scanf("%s", category);

            printf("Tell the quantity: ");
            scanf("%d", &quantity);

            printf("Tell the date(aaaa/mm/zz): ");
            scanf("%s", date);

            if(strcmp(category, "dairy") != 0 &&  strcmp(category, "sweets") != 0 && strcmp(category, "meat") != 0 && strcmp(category, "fruit") != 0)
                printf("This is an invalid category\n\n");
            else {
                add_product(product_list, createProduct(name, category, quantity, date));
                last_repository = copyDynamicArray(product_list);
                add_undo(undo_list, last_repository);
                print_list(*product_list);
            }
        }else if(comand == 2) {
            char name[50], category[50];
            printf("Tell the product name to remove: ");
            scanf("%s", name);

            printf("Tell the  product category : ");
            scanf("%s", category);

            if(strcmp(category, "dairy") != 0 &&  strcmp(category, "sweets") != 0 && strcmp(category, "meat") != 0 && strcmp(category, "fruit") != 0)
                printf("This is an invalid category\n\n");
            else {
                int aux = Remove_product(product_list, name, category);
                if(aux == -1) {
                    printf("This product doesn't exist\n");
                }else {
                    last_repository = copyDynamicArray(product_list);
                    add_undo(undo_list, last_repository);
                    print_list(*product_list);
                }
            }
        }else if(comand == 3) {
            char name[50], category[50], date[50];
            int quantity;
            printf("Tell the product name to update: ");
            scanf("%s", name);

            printf("Tell the product category: ");
            scanf("%s", category);

            printf("Tell the new quantity: ");
            scanf("%d", &quantity);

            printf("Tell the new date(aaaa/mm/zz): ");
            scanf("%s", date);

            if(strcmp(category, "dairy") != 0 &&  strcmp(category, "sweets") != 0 && strcmp(category, "meat") != 0 && strcmp(category, "fruit") != 0)
                printf("This is an invalid category\n\n");
            else {
                int aux = update_product(product_list, name, category, quantity, date);
                if(aux == -1)
                    printf("This product doesn't exist\n");
                else {
                    last_repository = copyDynamicArray(product_list);
                    add_undo(undo_list, last_repository);
                    print_list(*product_list);
                }
            }
        }else if(comand == 4) {
            char substr[50] = "\0";
            printf("Tell the sub string: ");
            fgets(substr, sizeof(substr), stdin);       //reads the whitespaces
            substr[strlen(substr) - 1] = '\0';                             //delete the last whitespace

            DynamicArray *new_repo = search_string(product_list, substr);
            print_list(*new_repo);
            destroy(new_repo);

        }else if(comand == 5) {
            char new_category[50], exp_date[50];

            printf("Tell the category: ");

            fgets(new_category, sizeof(new_category), stdin);       //reads the whitespaces
            new_category[strlen(new_category) - 1] = '\0';    //delete the last whitespace

            printf("Tell me the date(format aaaa/mm/zz): ");

            scanf("%s", exp_date);



            if(strcmp(new_category, "dairy") != 0 &&  strcmp(new_category, "sweets") != 0 && strcmp(new_category, "meat") != 0 && strcmp(new_category, "fruit") != 0)
                printf("This is an invalid category\n\n");
            else {
                int sort = 0;
                printf("Press 1 to sort items in descending order by date or 0 for no sort: ");
                scanf("%d", &sort);
                DynamicArray *filtered_repo = filter_products(product_list, new_category, exp_date, sort);
                print_list(*filtered_repo);
                destroy(filtered_repo);
            }

        }else if(comand == 6){
            DynamicArray *aux_repo = make_undo(undo_list, redo_list);

            if(aux_repo == NULL)
                printf("No more undo's\n");
            else {
                product_list = copyDynamicArray(aux_repo);
                print_list(*product_list);
            }
            destroy(aux_repo);
        }else if(comand == 7){
            DynamicArray *aux_repo = make_redo(redo_list, undo_list);

            if(aux_repo == NULL)
                printf("No more redo's\n");
            else{
                product_list = copyDynamicArray(aux_repo);
                print_list(*product_list);
            }
            destroy(aux_repo);

        }else if(comand == 8) {
            int min_quantity;
            printf("Tell the minimum quantity ");
            scanf("%d", &min_quantity);

            DynamicArray *new_repo = filter_quantity(product_list, min_quantity);
            print_list(*new_repo);
            destroy(new_repo);

        }else if(comand == 0)
            ok = 0;
        else printf("Invalid comand/n");
    }

    destroy(last_repository);
}

