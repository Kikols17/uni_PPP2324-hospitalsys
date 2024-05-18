#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doente_struct.h"
#include "Data_struct.h"


void print_D(Doente doente);
void print_Doente(Doente doente);


// FILES -----------------------------------------

// PODE SER DESNECESSÁRIA MAS VERIFICAR ISSO
// Write a Doente in a file in the correct format
void toFile_Doente(Doente doente, FILE *fd) {
    char buff[DATA_STRING_SIZE];
    data_toStr(doente.birthday, buff);
    fprintf(fd, "%d\n%s\n%s\n%s\n%d\n%s\n", doente.id, doente.name, buff, doente.cc, doente.tele, doente.email);
}

// PERFECT DONT TOUCH!!!
// Reads the list of Doentes - use at the start of the program only
int read_Doentes(listaD list){
    FILE * fp;
    if ((fp = fopen("doentes.txt","r")) == NULL){
        perror("Erro ao abrir o ficheiro\n");
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

// PERFECT DONT TOUCH!!!
// Writes the list of Doentes - use at the end and after every change to the list
int write_Doentes(listaD list){
    FILE * fp;
    if ((fp = fopen("doentes.txt","w")) == NULL){
        perror("Erro ao abrir o ficheiro\n");
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
        aux->prev = NULL;
    }

    return aux;
}

// PERFECT DONT TOUCH!!!
// Checks if list is empty
int emptyListD(listaD list){
    if (list->next == NULL) return 1;
    return 0;
}

// PERFECT DONT TOUCH!!!
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
    listaD cur = list->next;
    char *cc = d.cc;

    while(cur != NULL) {
        //print_D(cur->doente);
        //printf("%s\n",cur->doente.cc);
        if (strcmp(cur->doente.cc, cc)==0){
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}

// Looks for a Doente by it's id
listaD searchDoente_byID(listaD list, int id){
    
    // found = pointer to Doente in the list
    // not found =  NULL
    listaD cur = list;    

    while(cur->next != NULL){
        cur = cur->next;
        if (cur->doente.id==id) {
            return cur;
        }
    }
    
    return NULL;
}

// Looks for a Doente by its name
listaD searchDoente_byName(listaD list, char *name){
    // found =  pointer to Doente (returned in newD)
    // not found = NULL (returned in newD)
    listaD cur = list;
    
    while(cur->next != NULL){
        cur = cur->next;
        if (strcmp(cur->doente.name,name)==0) {
            return cur;
        }
    }

    return NULL;
}

// Inserts Doente in the list in the correct position by ID - first open ID
int insertD(listaD list, Doente d){
    // error = 0 | success = 1 | already in = -1
    if (in_listDoente(list, d)) return -1;

    listaD new_node = (listaD) malloc(sizeof(nodeD));
    listaD cur = list;
    if (new_node == NULL){
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

    new_node->next = cur->next;
    new_node->doente = d;
    cur->next = new_node;
    new_node->prev = cur;

    // Update the DataBase (txt)
    write_Doentes(list);
    return 1;
}

// Removes Doente by ID
int removeD(listaD list, int id){
    // not found = 0 | removed = 1
    
    listaD prior;
    listaD following;
    listaD d;
    
    d = searchDoente_byID(list, id);
    printf("%d\n",id);
    

    if (d != NULL){
        //print_D(d->doente);
        prior = d->prev;
        following = d->next;
        
        // make sure the pointers aren't NULL
        if (prior != NULL) prior->next = following;
        
        if (following != NULL) following->prev = prior;
        
        free(d);
        write_Doentes(list);
        // remove Registo associated with Doente
        return 1;

    }

    return 0;
}


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


// Print Doentes sorted by alphabetical order - Insertion Sort :)
// Check this please - there might be better solutions with less memory needed
void print_Alpha(listaD list){
    // list_size should ignore the header in the list
    listaD cur = list->next;
    int list_size = 0;

    while(cur != NULL){
        list_size++;
        cur = cur->next;
    }

    cur = list->next;
    // list of pointers to Doente - storing the address uses less memory than the storing the struct
    Doente *pointers[list_size]; 
    for (int i = 0; i < list_size; i++){
        //printf("%d",i);
        //print_D(*pointers[i]);
        pointers[i] = &(cur->doente);
        cur = cur->next;
    }

    for (int i = 1; i < list_size; i++){
        int j = i;
        // até elemento direita maior esquerda
        while (j > 0 && (strcmp(pointers[j]->name, pointers[j-1]->name) < 0)){
            // Check this
            Doente *aux = pointers[j];
            pointers[j] = pointers[j-1];
            pointers[j-1] = aux;
            j--;
        }
    }    

    for (int i = 0; i < list_size; i++){
        print_D(*pointers[i]);
    }

}

#endif