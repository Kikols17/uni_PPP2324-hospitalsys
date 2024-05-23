#include <stdio.h>
#include <stdlib.h>


#include "Registo_struct.h"
#include "Data_struct.h"


int main() {
    /* Test Case for "Registo_struct" */
    int ret = 0;


    struct ListaRegisto *test_list = createListaRegisto();
    if ( test_list == NULL ) {
        printf("[TESTCASES] error creating list\n");
        return -1;
    }
    printf("[TESTCASES] list created\n");

    ret = ListaRegisto_readFile("registos.txt", test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] file read sucessfully\n");
    } else {
        printf("[TESTCASES] error reading file %d\n", ret);
        return -1;
    }


    printf("[TESTCASES] printing list:\n");
    printListaRegisto(test_list);


    struct Data *new_data = createData(2023, 4, 14);
    if (new_data!=NULL) {
        printf("[TESTCASES] new data created successfully\n");
    } else {
        printf("[TESTCASES] error creating new data\n");
        return -1;
    }
    struct Registo *new_registo=createRegisto(3, new_data, 1, 1, 1, 1);
    if ( new_registo!=NULL ) {
        printf("[TESTCASES] new registo created successfully\n");
    } else {
        printf("[TESTCASES] error creating new registo\n");
        return -1;
    }


    printf("[TESTCASES] appending new registo to list\n");
    pushListaRegisto(test_list, createNodeRegisto(new_registo));
    printf("[TESTCASES] new registo appended\n");


    printf("[TESTCASES] printing list:\n");
    printListaRegisto(test_list);


    ret = ListaRegisto_toFile("registos2.txt", test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] file appended sucessfully\n");
    } else {
        printf("[TESTCASES] error overwritten file %d\n", ret);
        return -1;
    }


    ret = sortListRegistoID(test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] list sorted\n");
    } else {
        printf("[TESTCASES] error sorting list\n");
        return -1;
    }

    printf("[TESTCASES] printing list:\n");
    printListaRegisto(test_list);
    printf("[TESTCASES] list printed\n");


    ret = destroyListaRegisto(test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] list destroyed\n");
    } else {
        printf("[TESTCASES] error destroying list\n");
        return -1;
    }

    return 0;
}