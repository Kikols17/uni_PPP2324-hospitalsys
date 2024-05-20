#include <stdio.h>
#include <stdlib.h>


#include "Doente_struct.h"
#include "Data_struct.h"


int main() {
    /* Test Case for "Doente_struct" */
    int ret = 0;


    struct ListaDoente *test_list = createListaDoente();
    if ( test_list == NULL ) {
        printf("[TESTCASES] error creating list\n");
        return -1;
    }
    printf("[TESTCASES] list created\n");

    ret = ListaDoente_readFile("doentes.txt", test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] file read sucessfully\n");
    } else {
        printf("[TESTCASES] error reading file %d\n", ret);
        return -1;
    }

    printf("[TESTCASES] printing list:\n");
    printListDoente(test_list);

    ret = ListaDoente_toFile("doentes2.txt", test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] file overwritten sucessfully\n");
    } else {
        printf("[TESTCASES] error appending file %d\n", ret);
        return -1;
    }

    printf("[TESTCASES] sorting list by Name\n");
    ret = sortListDoenteAlpha(test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] list sorted by Name\n");
    } else {
        printf("[TESTCASES] error sorting list by Name %d\n", ret);
        return -1;
    }


    printf("[TESTCASES] printing list:\n");
    printListDoente(test_list);


    printf("[TESTCASES] sorting list by ID\n");
    ret = sortListDoenteID(test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] list sorted by ID\n");
    } else {
        printf("[TESTCASES] error sorting list by ID %d\n", ret);
        return -1;
    }


    printf("[TESTCASES] printing list:\n");
    printListDoente(test_list);


    printf("[TESTCASES] destroying list\n");
    ret = destroyListaDoente(test_list);
    if ( ret==0 ) {
        printf("[TESTCASES] list destroyed\n");
    } else {
        printf("[TESTCASES] error destroying list %d\n", ret);
        return -1;
    }

    return 0;
}