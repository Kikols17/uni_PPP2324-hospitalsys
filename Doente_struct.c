#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doente_struct.h"
#include "Data_struct.h"

#define BUFFER_SIZE 50
#define PARAMS_DOENTE 6


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

int emptyListD(listaD list){
    if (list->next == NULL) return 1;
    return 0;
}

void destroyListD(listaD list){
    listaD aux;
    while(!emptyListD(list)){
        aux = list;
        list = list->next;
        free(aux);
    }
    free(list);
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
    //str_Data(&doente->birthday, buff);
    fprintf(fd, "%d\n%s\n%s\n%s\n%d\n%s", doente->id, doente->name, buff, doente->cc, doente->tele, doente->email);
}

void print_Doente(Doente doente) {
    printf("ID: %d\n", doente.id);
    printf("Name: %s\n", doente.name);
    printf("Birthday: %d/%d/%d\n", doente.birthday.day, doente.birthday.month, doente.birthday.year);
    printf("CC: %s\n", doente.cc);
    printf("Telephone: %d\n", doente.tele);
    printf("Email: %s\n", doente.email);
}


int read_Doentes(listaD list){
    FILE * fp;
    if ((fp = fopen("doentes.txt","r")) == NULL){
        perror("[ERROR] Erro ao abrir o ficheiro\n");
        return -1;
    }

    char buffer[PARAMS_DOENTE][BUFFER_SIZE];
    Doente newD;
    Data birth;
    
    while(fgets(buffer[0], BUFFER_SIZE, fp)!=NULL){
        for (int i = 1; i < PARAMS_DOENTE; i++){
            fgets(buffer[i], BUFFER_SIZE, fp);
            buffer[i][strlen(buffer[i])-1] = '\0';
        }

        newD.id = atoi(buffer[0]);
        strcpy(newD.name,buffer[1]);
        str_toData(buffer[2],&birth);
        newD.birthday = birth;
        strcpy(newD.cc,buffer[3]);
        newD.tele = atoi(buffer[4]);
        strcpy(newD.email,buffer[5]);
        print_Doente(newD);

        //insertD(list,newD);
    }

    

    fclose(fp);
    
    return 0;

}


#endif