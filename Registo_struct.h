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
int tostrRegisto(struct Registo *registo, char *str);

// NodeRegisto ---------------------------------
struct NodeRegisto *createNodeRegisto(struct Registo *registo);
struct NodeRegisto *setNodeRegisto(struct NodeRegisto *node, struct Registo *registo);
int destroyNodeRegisto(struct ListaRegisto *ListR, struct NodeRegisto *nodeR);
int swapNodeRegisto(struct NodeRegisto *node1, struct NodeRegisto *node2);
int printNodeRegisto(struct NodeRegisto *node);
int tostrNodeRegisto(struct NodeRegisto *node, char *str);

// ListaRegisto ---------------------------------
struct ListaRegisto *createListaRegisto();
int destroyListaRegisto(struct ListaRegisto *ListR) ;
int pushListaRegisto(struct ListaRegisto *ListR, struct NodeRegisto *nodeR);
struct NodeRegisto *findIDListRegisto(struct ListaRegisto *ListR, int id);

int sortListRegistoID(struct ListaRegisto *ListR);
int printListaRegisto(struct ListaRegisto *ListR);
int tostrListaRegisto(struct ListaRegisto *ListR, char *str);

// File ---------------------------------
int Registo_appendFile(FILE *file, Registo *registo);
int Registo_readFile(FILE *file, Registo *registo);
int ListaRegisto_toFile(char *filename, struct ListaRegisto *ListR);
int ListaRegisto_readFile(char *filename, struct ListaRegisto *ListR);





#endif