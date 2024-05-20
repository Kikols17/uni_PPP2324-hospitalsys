#ifndef REGISTO_H
#define REGISTO_H

#include <stdio.h>

#include "Data_struct.h"


#define PARAMS_REGISTO 6


typedef struct Registo {
    int id;
    struct Data date;
    int tens_max;
    int tens_min;
    int weight;
    int height;
} Registo;

typedef struct NodeRegisto{
    Registo *registo;
    struct NodeRegisto *prev;
    struct NodeRegisto *next;
} NodeRegisto;

typedef struct ListaRegisto{
    struct NodeRegisto *first;
} ListaRegisto;


// Registo ---------------------------------
struct Registo *createRegisto(int id, struct Data *date, int tens_max, int tens_min, int weight, int height);
struct Registo *createEmptyRegisto();
struct Registo *createCopyRegisto(struct Registo *registo);
int copyRegisto(struct Registo *registo1, struct Registo *registo2);
int destroyRegisto(struct Registo *registo);
int printRegisto(struct Registo *registo);

// NodeRegisto ---------------------------------
struct NodeRegisto *createNodeRegisto(struct Registo *registo);
struct NodeRegisto *setNodeRegisto(struct NodeRegisto *node, struct Registo *registo);
int destroyNodeRegisto(struct ListaRegisto *listaR, struct NodeRegisto *nodeR);
int swapNodeRegisto(struct NodeRegisto *node1, struct NodeRegisto *node2);
int printNodeRegisto(struct NodeRegisto *node);

// ListaRegisto ---------------------------------
struct ListaRegisto *createListaRegisto();
int destroyListaRegisto(struct ListaRegisto *lista) ;
int pushListaRegisto(struct ListaRegisto *lista, struct NodeRegisto *nodeR);
struct NodeRegisto *findIDListRegisto(struct ListaRegisto *lista, int id);

int sortListRegistoID(struct ListaRegisto *lista);
int printListaRegisto(struct ListaRegisto *lista);

// File ---------------------------------
int Registo_appendFile(FILE *file, Registo *registo);
int Registo_readFile(FILE *file, Registo *registo);
int ListaRegisto_toFile(char *filename, struct ListaRegisto *lista);
int ListaRegisto_readFile(char *filename, struct ListaRegisto *lista);





#endif