#ifndef REGISTO_C
#define REGISTO_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Registo_struct.h"
#include "Data_struct.h"



// Registo struct

struct Registo *createRegisto(int id, struct Data *date, int tens_max, int tens_min, int weight, int height) {
    /* Allocates memory for a new "Registo" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to Registo struct if success
     */
    struct Registo *new_Registo = malloc(sizeof(Registo));
    if (new_Registo == NULL) {
        // malloc failed
        return NULL;
    }

    new_Registo->id = id;
    if ( Datacpy(&new_Registo->date, date)!=0 ) {
        // invalid date
        free(new_Registo);
        return NULL;
    }
    new_Registo->tens_max = tens_max;
    new_Registo->tens_min = tens_min;
    new_Registo->weight = weight;
    new_Registo->height = height;

    return new_Registo;
}

struct Registo *createEmptyRegisto() {
    /* Allocates memory for a new "Registo" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to Registo struct if success
     */
    return createRegisto(0, createEmptyData(), 0, 0, 0, 0);
}

struct Registo *createCopyRegisto(struct Registo *registo) {
    /* Allocates memory for a new "Registo" struct and true copies the info of another "Registo" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to Registo struct if success
     */
    if (registo == NULL) {
        // invalid pointer
        return NULL;
    }

    return createRegisto(registo->id, &registo->date, registo->tens_max, registo->tens_min, registo->weight, registo->height);
}

int copyRegisto(struct Registo *registo1, struct Registo *registo2) {
    /* Copies the info of a "Registo" struct to another "Registo" struct
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (registo1 == NULL || registo2 == NULL) {
        // invalid pointer
        return -1;
    }

    registo1->id = registo2->id;
    if ( Datacpy(&registo1->date, &registo2->date)!=0 ) {
        // invalid date
        return -1;
    }
    registo1->tens_max = registo2->tens_max;
    registo1->tens_min = registo2->tens_min;
    registo1->weight = registo2->weight;
    registo1->height = registo2->height;

    return 0;

}

int destroyRegisto(struct Registo *registo) {
    /* Frees memory allocated for a "Registo" struct
     * Returns:
     *      -> -1 if invalid pointer
     *     -> 0 if success
     */
    if (registo == NULL) {
        // invalid pointer
        return -1;
    }
    free(registo);
    return 0;
}

int printRegisto(struct Registo *registo) {
    /* Prints the info of a "Registo" struct
     */
    if (registo == NULL) {
        // invalid pointer
        return -1;
    }

    char strData[DATA_STRING_SIZE];
    data_toStr(&registo->date, strData);
    printf("Registo %d:\n\tDate: %s\n\tTensão Máxima: %d\n\tTensão Mínima: %d\n\tPeso: %d\n\tAltura: %d\n", registo->id, strData, registo->tens_max, registo->tens_min, registo->weight, registo->height);
    return 0;
}

int tostrRegisto(struct Registo *registo, char *str) {
    /* Converts the info of a "Registo" struct to a string
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (registo == NULL) {
        // invalid pointer
        return -1;
    }

    char strData[DATA_STRING_SIZE];
    data_toStr(&registo->date, strData);
    sprintf(str+strlen(str), "Registo %d:\n\tDate: %s\n\tTensão Máxima: %d\n\tTensão Mínima: %d\n\tPeso: %d\n\tAltura: %d\n", registo->id, strData, registo->tens_max, registo->tens_min, registo->weight, registo->height);
    return 0;
}



// NodeRegisto struct

struct NodeRegisto *createNodeRegisto(struct Registo *registo) {
    /* Allocates memory for a new "NodeRegisto" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to NodeRegisto struct if success
     */
    struct NodeRegisto *new_NodeRegisto = malloc(sizeof(NodeRegisto));
    if (new_NodeRegisto == NULL) {
        // malloc failed
        return NULL;
    }

    if (registo == NULL) {
        // invalid pointer
        free(new_NodeRegisto);
        return NULL;
    }

    new_NodeRegisto->registo = registo;
    new_NodeRegisto->prev = NULL;
    new_NodeRegisto->next = NULL;

    return new_NodeRegisto;
}

struct NodeRegisto *setNodeRegisto(struct NodeRegisto *node, struct Registo *registo) {
    /* Sets the info of a "NodeRegisto" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to NodeRegisto struct if success
     */
    if (node == NULL) {
        // invalid pointer
        return NULL;
    }

    destroyRegisto(node->registo);
    node->registo = registo;
    return node;
}

int destroyNodeRegisto(struct ListaRegisto *listaR, struct NodeRegisto *nodeR) {
    /* Frees memory allocated for a "NodeRegisto" struct
     */
    if (nodeR == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeRegisto *auxPrev, *auxNext;
    auxPrev = nodeR->prev;
    auxNext = nodeR->next;
    if (auxPrev != NULL) {
        // store prev node
        auxPrev->next = auxNext;
    } else {
        // node is first, update first
        listaR->first = auxNext;
    }
    if (auxNext != NULL) {
        // store next node
        auxNext->prev = auxPrev;
    }

    destroyRegisto(nodeR->registo);
    free(nodeR);
    return 0;
}

int swapNodeRegisto(struct NodeRegisto *node1, struct NodeRegisto *node2) {
    /* Swaps the info of two "NodeRegisto" structs
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (node1 == NULL || node2 == NULL) {
        // invalid pointer
        return -1;
    }

    struct Registo *temp = node1->registo;
    node1->registo = node2->registo;
    node2->registo = temp;
    return 0;
}

int printNodeRegisto(struct NodeRegisto *node) {
    /* Prints the info of a "NodeRegisto" struct */
    printRegisto(node->registo);
    return 0;
}

int tostrNodeRegisto(struct NodeRegisto *node, char *str) {
    /* Converts the info of a "NodeRegisto" struct to a string
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (node == NULL) {
        // invalid pointer
        return -1;
    }

    tostrRegisto(node->registo, str);
    return 0;
}


// ListaRegisto struct

struct ListaRegisto *createListaRegisto() {
    /* Allocates memory for a new "ListaRegisto" struct
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to ListaRegisto struct if success
     */
    struct ListaRegisto *new_ListaRegisto = malloc(sizeof(ListaRegisto));
    if (new_ListaRegisto == NULL) {
        // malloc failed
        return NULL;
    }

    new_ListaRegisto->first = NULL;

    return new_ListaRegisto;
}

int destroyListaRegisto(struct ListaRegisto *lista) {
    /* Frees memory allocated for a "ListaRegisto" struct
     */
    struct NodeRegisto *current = lista->first;
    struct NodeRegisto *next = NULL;
    while (current != NULL) {
        next = current->next;
        destroyNodeRegisto(lista, current);
        current = next;
    }
    free(lista);
    return 0;
}

int pushListaRegisto(struct ListaRegisto *lista, struct NodeRegisto *nodeR) {
    /* Adds a "NodeRegisto" struct to the end of a "ListaRegisto" struct
     * Returns:
     *      -> -1 if malloc fails
     *      -> 0 if success
     */
    if (lista == NULL || nodeR == NULL) {
        // invalid pointer
        return -1;
    }

    if (lista->first == NULL) {
        lista->first = nodeR;
        return 0;
    }

    struct NodeRegisto *current = lista->first;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = nodeR;
    nodeR->prev = current;
    return 0;
}

struct NodeRegisto *findIDListRegisto(struct ListaRegisto *lista, int id) {
    /* Finds a "NodeRegisto" struct in a "ListaRegisto" struct by ID
     * Returns:
     *      -> NULL if not found
     *      -> valid pointer to NodeRegisto struct if success
     */
    struct NodeRegisto *current;
    if (lista == NULL) {
        // invalid pointer
        return NULL;
    }

    current = lista->first;
    while (current != NULL) {
        if (current->registo->id == id) {
            // firt registo with ID found
            return current;
        }
        current = current->next;
    }
    return NULL;

}


int sortListRegistoID(struct ListaRegisto *lista) {
    /* Sorts a "ListaRegisto" struct by ID with simple Bubble Sort
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (lista == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeRegisto *current = lista->first;
    struct NodeRegisto *next = NULL;
    while (current != NULL) {
        next = current->next;
        while (next != NULL) {
            if (current->registo->id > next->registo->id) {
                // swap
                swapNodeRegisto(current, next);
            }
            next = next->next;
        }
        current = current->next;
    }
    return 0;
}

int printListaRegisto(struct ListaRegisto *lista) {
    /* Prints the info of a "ListaRegisto" struct */
    struct NodeRegisto *current = lista->first;
    while (current != NULL) {
        if (printNodeRegisto(current)!=0) {
            // error printing node
            return -1;
        }
        current = current->next;
    }
    return 0;
}

int tostrListaRegisto(struct ListaRegisto *lista, char *str) {
    /* Converts the info of a "ListaRegisto" struct to a string
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    struct NodeRegisto *current = lista->first;
    while (current != NULL) {
        if (tostrNodeRegisto(current, str)!=0) {
            // error converting node to string
            return -1;
        }
        current = current->next;
    }
    return 0;

}



// FILE

int Registo_appendFile(FILE *file, Registo *registo) {
    /* Appends the info of a "Registo" struct to a file
     * Returns:
     *      -> 0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 invalid registo
     *      -> -3 if error writing to file
     */
    if (file == NULL) {
        // invalid pointer
        return -1;
    }
    if (registo == NULL) {
        // invalid pointer
        return -2;
    }

    char strData[DATA_STRING_SIZE];
    data_toStr(&registo->date, strData);

    if (fprintf(file, "%d\n%s\n%d\n%d\n%d\n%d\n", registo->id, strData, registo->tens_max, registo->tens_min, registo->weight, registo->height) < 0) {
        // error writing to file
        return -3;
    }
    return 0;
}

int Registo_readFile(FILE *file, Registo *registo) {
    /* Reads the info of a "Registo" struct from a file
     * Returns:
     *      -> 0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 invalid registo
     *      -> -3 if error reading from file
     */
    if (file == NULL) {
        // invalid pointer
        return -1;
    }
    if (registo == NULL) {
        // invalid pointer
        return -2;
    }


    // read from file
    char buff[PARAMS_REGISTO][DATA_STRING_SIZE];
    for (int i=0; i<PARAMS_REGISTO; i++) {
        if (fgets(buff[i], DATA_STRING_SIZE, file) == NULL) {
            // error reading file
            if (i==0) {
                // file at EOF
                return 1;
            } else {
                // error reading file
                return -3;
            }
        }
        buff[i][strlen(buff[i])-1] = '\0';      // remove '\n'
    }

    // write to registo
    registo->id = atoi(buff[0]);
    if (str_toData(buff[1], &registo->date)!=0) {
        // invalid date
        return -3;
    }
    registo->tens_max = atoi(buff[2]);
    registo->tens_min = atoi(buff[3]);
    registo->weight = atoi(buff[4]);
    registo->height = atoi(buff[5]);


    return 0;
}

int ListaRegisto_toFile(char *filename, struct ListaRegisto *lista) {
    /* Writes the info of a "ListaRegisto" struct to a file
     * Returns:
     *      -> 0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 if error writing to file
     */
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        // error opening file
        return -1;
    }

    struct NodeRegisto *current = lista->first;
    while (current != NULL) {
        if (Registo_appendFile(file, current->registo)!=0) {
            // error writing to file
            fclose(file);
            return -2;
        }
        current = current->next;
    }

    fclose(file);
    return 0;
}

int ListaRegisto_readFile(char *filename, struct ListaRegisto *lista) {
    /* Reads the info of a "ListaRegisto" struct from a file
     * Returns:
     *      -> 0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 if error reading from file
     */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // error opening file
        return -1;
    }

    struct Registo *new_registo;
    int ret = 0;
    while (1) {
        new_registo = createEmptyRegisto();
        ret = Registo_readFile(file, new_registo);
        if (ret==0) {
            // success
            pushListaRegisto(lista, createNodeRegisto(new_registo));
        } else if (ret==1) {
            // EOF
            break;
        } else {
            // error reading file
            destroyRegisto(new_registo);
            fclose(file);
            return -2;
        }
    }

    destroyRegisto(new_registo);
    fclose(file);
    return 0;
}


/*
int main2() {
    / Test Case for "Regist_struct" /
    struct Registo *test_registo = createRegisto();
    
    if (test_registo!=NULL) {
        printf("\"test_registo\" created successfully\n");
    } else {
        printf("error creating \"test_registo\"\n");
        return -1;
    }

    printf("\nWriting to File:\n");
    toFile_Registo(test_registo, stdout);
    return 0;
}
*/



#endif