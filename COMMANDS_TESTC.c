#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Commands.h"
#include "Doente_struct.h"
#include "Registo_struct.h"
#include "Data_struct.h"



int main() {
    /* Test Case for "commands" */
    int ret = 0;
    ListaDoente *listaD = createListaDoente();
    ListaRegisto *listaR = createListaRegisto();
    if ( listaD == NULL ) {
        printf("[TESTCASES] error creating list\n");
        return -1;
    }
    printf("[TESTCASES] list created\n");
    if ( listaR == NULL ) {
        printf("[TESTCASES] error creating list\n");
        return -1;
    }
    printf("[TESTCASES] list created\n");

    

    ret = ListaDoente_readFile("doentes.txt", listaD);
    if ( ret==0 ) {
        printf("[TESTCASES] file \"doentes.txt\" read sucessfully\n");
    } else {
        printf("[TESTCASES] error reading file \"doentes.txt\" %d\n", ret);
        return -1;
    }
    ret = ListaRegisto_readFile("registos.txt", listaR);
    if ( ret==0 ) {
        printf("[TESTCASES] file \"registos.txt\" read sucessfully\n");
    } else {
        printf("[TESTCASES] error reading file \"registos.txt\" %d\n", ret);
        return -1;
    }


    char response[1000];
    response[0] = '\0';
    cmd_help(response);
    printf("[TESTCASES] help message:\n\"%s\"\n", response);

    response[0] = '\0';
    cmd_AddDoente(listaD, 3, "Joao", "12/12/2000", "01234567-8-AB1", 912345678, "francisco.lapamsilva@gmail.com", response);
    printf("[TESTCASES] possible response:\n\"%s\"\n", response);
    printListDoente(listaD);

    response[0] = '\0';
    cmd_AddDoente(listaD, 3, "Joao", "12/12/2000", "01234567-8-AB1", 912345678, "franciso.lapamsilva@gmail.com", response);
    printf("[TESTCASES] impossible response (same id):\n\"%s\"\n", response);
    printListDoente(listaD);


    response[0] = '\0';
    cmd_AddRegisto(listaD, listaR, 1, "12/12/2000", 120, 80, 70, 180, response);
    printf("[TESTCASES] possible response:\n\"%s\"\n", response);
    printListaRegisto(listaR);

    response[0] = '\0';
    cmd_AddRegisto(listaD, listaR, 5, "12/12/2000", 120, 80, 70, 180, response);
    printf("[TESTCASES] impossible response (no user id=5):\n\"%s\"\n", response);
    printListaRegisto(listaR);

    response[0] = '\0';
    cmd_RmvDoente(listaD, "Joao", response);
    printf("[TESTCASES] possible response:\n\"%s\"\n", response);
    printListDoente(listaD);


    response[0] = '\0';
    cmd_listAlpha(listaD, response);
    printf("[TESTCASES] Listing ALPHA:\n\"%s\"\n", response);

    response[0] = '\0';
    cmd_listTens(listaD, listaR, 1, 125, response);
    printf("[TESTCASES] Listing TENSION >=125:\n\"%s\"\n", response);


    response[0] = '\0';
    cmd_displayDoente(listaD, listaR, "Francisco", response);
    printf("[TESTCASES]Impossible Displaying \"Francisco\":\n\"%s\"\n", response);

    response[0] = '\0';
    cmd_displayDoente(listaD, listaR, "Paulo Silva", response);
    printf("[TESTCASES] possible Displaying \"Paulo Silva\":\n\"%s\"\n", response);


    ret = destroyListaDoente(listaD);
    if ( ret==0 ) {
        printf("[TESTCASES] listD destroyed\n");
    } else {
        printf("[TESTCASES] error destroying listD %d\n", ret);
        return -1;
    }

    ret = destroyListaRegisto(listaR);
    if ( ret==0 ) {
        printf("[TESTCASES] listR destroyed\n");
    } else {
        printf("[TESTCASES] error destroying listR %d\n", ret);
        return -1;
    }

}