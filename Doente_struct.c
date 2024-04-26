#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doente_struct.h"
#include "Data_struct.h"

#define BUFFERS_SIZE 50
#define PARAMS_DOENTE 6

struct Doente *createDoente() {
    /* Return pointer to newly allocated "Doente" struct */
    return malloc(sizeof(Doente));
}

listaD createListD(){
    listaD aux;
    Doente dnull = {0,"",{0,0,0},"",0,""};
    aux = (listaD) malloc(sizeof(nodeD));

    if(aux != NULL){
        aux->doente = dnull;
        aux->next = NULL;
    }

    return aux;
}

void insertD(listaD list, Doente d){
    listaD node = (listaD) malloc(sizeof(nodeD));
    listaD cur = list;
    if (node == NULL){
        printf("Erro ao inserir Doente na lista\n");
        return;
    }
    node->next = NULL;
    node->doente = d;
    
    while(cur->next != NULL) cur = cur->next;
    cur->next = node;
    return;
}

void toFile_Doente(struct Doente *doente, FILE *fd) {
    char buff[DATA_STRING_SIZE];
    toString_Data(&doente->birthday, buff);
    fprintf(fd, "%d\n%s\n%s\n%s\n%d\n%s", doente->id, doente->name, buff, doente->cc, doente->tele, doente->email);
}

void print_Doente(struct Doente *doente){
    printf("ID: %d\n", doente->id);
    printf("Name: %s\n", doente->name);
    printf("Birthday: %d/%d/%d\n", doente->birthday.day, doente->birthday.month, doente->birthday.year);
    printf("CC: %s\n", doente->cc);
    printf("Telephone: %d\n", doente->tele);
    printf("Email: %s\n", doente->email);
    printf("Birthday: %d/%d/%d\n", doente->birthday.day, doente->birthday.month, doente->birthday.year);
}

int read_Doentes(){
    FILE * fp;
    if ((fp = fopen("doentes.txt","r")) == NULL){
        ferror("[ERROR] Erro ao abrir o ficheiro");
        return -1;
    }

    char buffer[PARAMS_DOENTE][BUFFERS_SIZE];
    Doente newD;
    

    while(fgets(buffer[0], BUFFERS_SIZE, fp)!=NULL){
        for (int i = 1; i < PARAMS_DOENTE; i++){
            fgets(buffer[i], BUFFERS_SIZE, fp);
            buffer[i][strlen(buffer[i])-1] = '\0';
        }

        newD.id = atoi(buffer[0]);
        strcpy(newD.name,buffer[1]);
        newD.birthday = str_toData(buffer[2]);
        strcpy(newD.cc,buffer[3]);
        newD.tele = atoi(buffer[4]);
        strcpy(newD.email,buffer[5]);
        print_Doente(&newD);

        //insertD();
    }

    

    fclose(fp);

}







/*
int main2() {
    / Test Case for "Doente_struct" /
    struct Doente *test_doente = createDoente();
    if (test_doente!=NULL) {
        printf("\"test_doente\" created successfully\n");
    } else {
        printf("error creating \"test_doente\"\n");
        return -1;
    }

    printf("\nWriting to File:\n");
    toFile_Doente(test_doente, stdout);
    return 0;
}
*/


#endif