#ifndef DOENTE_H
#define DOENTE_H

#include <stdio.h>
#include "Data_struct.h"

#define BUFFER_SIZE 50
#define PARAMS_DOENTE 6
#define CHARS_CC 15
#define DOENTE_NOME_SIZE 64

typedef struct Doente {
    int id;
    char name[DOENTE_NOME_SIZE];
    struct Data birthday;
    char cc[CHARS_CC];
    int tele;
    char email[DOENTE_NOME_SIZE];
} Doente;


typedef struct NodeDoente{
    Doente *doente;
    struct NodeDoente *next;
    struct NodeDoente *prev;
}NodeDoente;

typedef struct ListaDoente{
    struct NodeDoente *first;
} ListaDoente;


// Doente ---------------------------------
Doente *createDoente(int id, char *name, struct Data *birthday, char *cc, int tele, char *email);
Doente *createEmptyDoente();
int setDoente(struct Doente *doente, int id, char *name, struct Data *birthday, char *cc, int tele, char *email);
int copyDoente(struct Doente *dest, struct Doente *src);
int destroyDoente(struct Doente *doente);
int printDoente(struct Doente *doente);
int tostrDoente(struct Doente *doente, char *str);


// NodeDoente ---------------------------------
struct NodeDoente *createNodeDoente(Doente *doente);
int setNodeDoente(struct NodeDoente *nodeD, Doente *doente);
int destroyNodeDoente(struct ListaDoente *listaD, struct NodeDoente *nodeD);
int swapNodeDoente(struct NodeDoente *node1, struct NodeDoente *node2);
int printNodeDoente(struct NodeDoente *nodeD);
int tostrNodeDoente(struct NodeDoente *nodeD, char *str);


// ListaDoente ---------------------------------
struct ListaDoente *createListaDoente();
int destroyListaDoente(struct ListaDoente *listD);
int pushListDoente(ListaDoente *listD, struct NodeDoente *nodeD);
struct NodeDoente *findNameListDoente(struct ListaDoente *listD, char *name);
struct NodeDoente *findIDListDoente(struct ListaDoente *listD, int id);

int sortListDoenteID(struct ListaDoente *lista);
int sortListDoenteAlpha(struct ListaDoente *lista);
int printListDoente(struct ListaDoente *listD);
int tostrListDoente(struct ListaDoente *listD, char *str);


// File ---------------------------------
int Doente_appendFile(FILE *file, Doente *doente);
int Doente_readFile(FILE *file, Doente *doente);
int ListaDoente_toFile(char *filepath, struct ListaDoente *listD);
int ListaDoente_readFile(char *filepath, struct ListaDoente *listD);






#endif