#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doente_struct.h"
#include "Data_struct.h"

#define BUFFER_SIZE 50
#define PARAMS_DOENTE 6



// FILES -----------------------------------------

// Write a Doente in a file in the correct format
void toFile_Doente(Doente doente, FILE *fd) {
    char buff[DATA_STRING_SIZE];
    data_toStr(doente.birthday, buff);
    fprintf(fd, "%d\n%s\n%s\n%s\n%d\n%s\n", doente.id, doente.name, buff, doente.cc, doente.tele, doente.email);
}

// Reads the list of Doentes - use at the start of the program only
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
        //print_Doente(newD);

        insertD(list,newD);
    }

    fclose(fp);
    return 0;

}

// Writes the list of Doentes - use at the end and after every change to the list
int write_Doentes(listaD list){
    FILE * fp;
    if ((fp = fopen("doentes.txt","w")) == NULL){
        perror("[ERROR] Erro ao abrir o ficheiro\n");
        return -1;
    }

    listaD aux = list->next;
    while(aux!=NULL){
        toFile_Doente(aux->doente,fp);
        aux = aux->next;
    }

    fclose(fp);
    return 0;
}



// LIST -----------------------------------------

// Initializes the list of Doentes
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

// Checks if list is empty
int emptyListD(listaD list){
    if (list->next == NULL) return 1;
    return 0;
}

// Frees all pointers in the list
void destroyListD(listaD list){
    listaD aux;
    while(!emptyListD(list)){
        aux = list;
        list = list->next;
        free(aux);
    }
    free(list);
}

// Checks if Doente is on list by its CC
int in_listDoente(listaD list, Doente d){
    // in list = 1 | not in list = 0
    listaD cur = list;
    char *cc = d.cc;

    while(cur->next != NULL) {
        if (strcmp(cur->doente.cc, cc)==0){
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}

// Inserts Doente in the list in the correct position by ID - first open ID
int insertD(listaD list, Doente d){
    // error = 0 | success = 1 | already in = -1


    if (in_listDoente(list, d)) return -1;


    listaD node = (listaD) malloc(sizeof(nodeD));
    listaD cur = list;
    if (node == NULL){
        perror("Erro ao inserir Doente na lista\n");
        return 0;
    }
    
    // goes through the list to find an open space and gives Doente that id
    // or goes to the  end of the list and inserts Doente there
    int check_id = 1;
    while(cur->next != NULL) {
        if (cur->next->doente.id != check_id){
            check_id++;
            break;
        }
        cur = cur->next;
        check_id++;
    }

    // set new Doente id
    d.id = check_id;

    node->next = cur->next;
    node->doente = d;
    cur->next = node;

    // Update the DataBase (txt)
    write_Doentes(list);
    return 1;
}

// REMOVE


// LIST EXTRA -----------------------------------------

// Prints all data stored in struct Doente
void print_Doente(Doente doente) {
    printf("ID: %d\n", doente.id);
    printf("Name: %s\n", doente.name);
    printf("Birthday: %d/%d/%d\n", doente.birthday.day, doente.birthday.month, doente.birthday.year);
    printf("CC: %s\n", doente.cc);
    printf("Telephone: %d\n", doente.tele);
    printf("Email: %s\n", doente.email);
}

// Prints ID and Name - minimalist print 
void print_D(Doente doente) {
    printf("ID: %d ", doente.id);
    printf("Name: %s\n", doente.name);
}


// SORT - Insertion Sort :)


// Looks for a Doente by it's id
Doente* searchDoente_byID(listaD list, int id){
    
    // found = pointer to Doente in the list
    // not found =  NULL
    listaD cur = list;    

    while(cur->next != NULL){
        cur = cur->next;
        if (cur->doente.id==id) {
            return &cur->doente;
        }
    }
    
    return NULL;
}

// Looks for a Doente by its name
int searchDoente_byName(listaD list, char *name, Doente **newD){
    // found =  pointer to Doente (returned in newD)
    // not found = NULL (returned in newD)
    listaD cur = list;
    
    while(cur->next != NULL){
        cur = cur->next;
        if (strcmp(cur->doente.name,name)==0) {
            *newD = &cur->doente;
            return 1;
        }
    }
    // check this
    *newD = NULL;
    return 0;
}



#endif