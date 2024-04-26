#ifndef DOENTE_H
#define DOENTE_H

#include <stdio.h>
#include "Data_struct.h"

#define DOENTE_NOME_SIZE 64
#define CC_SIZE 15

typedef struct Doente {
    int id;
    char name[DOENTE_NOME_SIZE];
    struct Data birthday;
    char cc[CC_SIZE];
    int tele;
    char email[DOENTE_NOME_SIZE];
} Doente;


struct Doente *createDoente();
void toFile_Doente(struct Doente *doente, FILE *fd);




#endif