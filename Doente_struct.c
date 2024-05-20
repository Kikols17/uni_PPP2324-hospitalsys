#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doente_struct.h"
#include "Data_struct.h"


// Doente ---------------------------------

Doente *createDoente(int id, char *name, struct Data *birthday, char *cc, int tele, char *email) {
    /* Returns pointer to newly allocated Doente struct
     * Also introduces the info "id", "name", "birthday", "cc", "tele" and "email" into the struct
     *
     * Returns:
     *      -> NULL if malloc fails or if the date is invalid
     *      -> valid pointer to Doente struct if success
     */
    Doente *new_Doente = malloc(sizeof(Doente));
    if (new_Doente == NULL) {
        // malloc failed, download more RAM at downloadmoreram.com
        return NULL;
    }

    new_Doente->id = id;
    strcpy(new_Doente->name, name);
    if ( Datacpy(&new_Doente->birthday, birthday)!=0 ) {
        // invalid date
        free(new_Doente);
        return NULL;
    }
    strcpy(new_Doente->cc, cc);
    new_Doente->tele = tele;
    strcpy(new_Doente->email, email);

    return new_Doente;
}

Doente *createEmptyDoente() {
    /* Returns pointer to newly allocated Doente struct
     * Also introduces the info "id", "name", "birthday", "cc", "tele" and "email" into the struct
     *
     * Returns:
     *      -> NULL if malloc fails or if the date is invalid
     *      -> valid pointer to Doente struct if success
     */
    struct Doente *new_Doente;
    struct Data *new_Data = createEmptyData();

    new_Doente = createDoente(0, "", new_Data, "", 0, "");
    destroyData(new_Data);

    return new_Doente;
}

int setDoente(struct Doente *doente, int id, char *name, struct Data *birthday, char *cc, int tele, char *email) {
    /* Sets the values "id", "name", "birthday", "cc", "tele" and "email" into the struct
     *
     * Returns:
     *      -> -1 date pointer is NULL
     *      -> 0 if success
     */
    if (doente == NULL) {
        // invalid pointer
        return -1;
    }

    doente->id = id;
    strcpy(doente->name, name);
    Datacpy(&doente->birthday, birthday);
    strcpy(doente->cc, cc);
    doente->tele = tele;
    strcpy(doente->email, email);

    return 0;
}

int copyDoente(struct Doente *dest, struct Doente *src) {
    /* Copies the values from "src" to "dest"
     *
     * Returns:
     *      -> -1 if invalid pointer
     *      ->  0 if success
     */
    if (dest == NULL || src == NULL) {
        // invalid pointer
        return -1;
    }

    dest->id = src->id;
    strcpy(dest->name, src->name);
    Datacpy(&dest->birthday, &src->birthday);
    strcpy(dest->cc, src->cc);
    dest->tele = src->tele;
    strcpy(dest->email, src->email);

    return 0;

}

int destroyDoente(Doente *doente) {
    /* Frees the memory allocated for the Doente struct */
    if (doente == NULL) {
        // invalid pointer
        return -1;
    }

    free(doente);
    return 0;
}

int printDoente(Doente *doente) {
    /* Prints the Doente struct
     * Returns:
     *      -> -1 if Doente pointer is NULL
     *     ->  0 if success
     */
    if (doente == NULL) {
        // invalid pointer
        return -1;
    }

    char buff[DATA_STRING_SIZE];
    data_toStr(&doente->birthday, buff);
    printf("ID: %d\nName: %s\nBirthday: %s\nCC: %s\nTele: %d\nEmail: %s\n", doente->id, doente->name, buff, doente->cc, doente->tele, doente->email);

    return 0;
}



// NodeDoente ---------------------------------

struct NodeDoente *createNodeDoente(Doente *doente) {
    /* Returns pointer to newly allocated NodeDoente struct
     * Also introduces the info "doente" into the struct
     *
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to NodeDoente struct if success
     */
    NodeDoente *new_NodeDoente = malloc(sizeof(NodeDoente));
    if (new_NodeDoente == NULL) {
        // malloc failed, download more RAM at downloadmoreram.com
        return NULL;
    }

    new_NodeDoente->doente = doente;
    new_NodeDoente->next = NULL;
    new_NodeDoente->prev = NULL;

    return new_NodeDoente;
}

int setNodeDoente(struct NodeDoente *nodeD, Doente *doente) {
    /* Sets the value "doente" into the struct, and frees the previous one
     *
     * Returns:
     *      -> -1 date pointer is NULL
     *      -> 0 if success
     */
    if (nodeD == NULL) {
        // invalid pointer
        return -1;
    }

    destroyDoente(nodeD->doente);
    nodeD->doente = doente;
    return 0;
}

int destroyNodeDoente(struct NodeDoente *nodeD) {
    /* Frees the memory allocated for the NodeDoente struct, frees the Doente struct and joins next and prev nodes
     * Returns:
     *      -> -1 date pointer is NULL
     *      -> 0 if success
     */
    if (nodeD == NULL) {
        // invalid pointer
        return -1;
    }

    // join prev and next nodes
    struct NodeDoente *auxPrev, *auxNext;
    auxPrev = nodeD->prev;
    auxNext = nodeD->next;
    if (auxPrev != NULL) {
        auxPrev->next = auxNext;
    }
    if (auxNext != NULL) {
        auxNext->prev = auxPrev;
    }

    free(nodeD->doente);
    free(nodeD);
    return 0;
}

int swapNodeDoente(struct NodeDoente *nodeD1, struct NodeDoente *nodeD2) {
    /* Swaps the values of two NodeDoente structs
     *
     * Returns:
     *      -> -1 if invalid pointer
     *      ->  0 if success
     */
    if (nodeD1 == NULL || nodeD2 == NULL) {
        // invalid pointer
        return -1;
    }

    struct Doente *temp = nodeD1->doente;
    nodeD1->doente = nodeD2->doente;
    nodeD2->doente = temp;

    return 0;
}

int printNodeDoente(struct NodeDoente *nodeD) {
    /* Prints the NodeDoente struct
     * Returns:
     *      -> -1 if NodeDoente pointer is NULL
     *     ->  0 if success
     */
    if (nodeD == NULL) {
        // invalid pointer
        return -1;
    }

    printDoente(nodeD->doente);
    printf("self->%p\nprev->%p\nnext->%p\n", nodeD, nodeD->prev, nodeD->next);
    return 0;
}



// ListaDoente ---------------------------------

struct ListaDoente *createListaDoente() {
    /* Returns pointer to newly allocated NodeDoente struct
     *
     * Returns:
     *      -> NULL if malloc fails
     *      -> valid pointer to NodeDoente struct if success
     */
    struct ListaDoente *new_ListaDoente = malloc(sizeof(ListaDoente));
    if (new_ListaDoente == NULL) {
        // malloc failed, download more RAM at downloadmoreram.com
        return NULL;
    }
    new_ListaDoente->first = NULL;
    return new_ListaDoente;
}

int destroyListaDoente(struct ListaDoente *listD) {
    /* Frees the memory allocated for the ListaDoente struct, frees the Doente structs and joins next and prev nodes
     * Returns:
     *      -> -1 date pointer is NULL
     *      -> 0 if success
     */
    if (listD == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeDoente *cur = listD->first;
    struct NodeDoente *aux;
    while (cur != NULL) {
        aux = cur->next;
        destroyNodeDoente(cur);
        cur = aux;
    }

    free(listD);
    return 0;
}

int pushListDoente(struct ListaDoente *listD, struct NodeDoente *nodeD) {
    /* Adds a new NodeDoente to the list, and checks if ID, name and CC are unique
     *
     * Returns:
     *      -> -1 if list pointer is NULL
     *      ->  0 if success
     *      ->  1 id already exists
     *      ->  2 name already exists
     *      ->  3 CC already exists
     */
    if (listD == NULL) {
        // invalid pointer
        return -1;
    }
    if (listD->first == NULL) {
        listD->first = nodeD;
        return 0;
    }

    struct NodeDoente *cur = listD->first;
    while ( cur->next!=NULL ) {
        if (cur->doente->id == nodeD->doente->id) {
            // can't have two doentes with the same ID
            return 1;
        } else if ( strcmp(cur->doente->name, nodeD->doente->name)==0 ) {
            // can't have two doentes with the same name
            return 2;
        } else if ( strcmp(cur->doente->cc, nodeD->doente->cc)==0 ) {
            // can't have two doentes with the same CC
            return 3;
        }
        cur = cur->next;        // insert at the end
    }

    // check again for last node
    if (cur->doente->id == nodeD->doente->id) {
        // can't have two doentes with the same ID
        return 1;
    } else if ( strcmp(cur->doente->name, nodeD->doente->name)==0 ) {
        // can't have two doentes with the same name
        return 2;
    } else if ( strcmp(cur->doente->cc, nodeD->doente->cc)==0 ) {
        // can't have two doentes with the same CC
        return 3;
    }
    cur->next = nodeD;
    nodeD->prev = cur;

    return 0;

}

struct NodeDoente *findNameListDoente(struct ListaDoente *listD, char *name) {
    /* Finds a Doente struct by name in the ListDoente
     *
     * Returns:
     *      -> NULL if pointer / name is invalid / Doente not found
     *      -> valid pointer to NodeDoente struct if success
     */
    if (listD == NULL) {
        // invalid pointer
        return NULL;
    }

    if (name == NULL) {
        // invalid name
        return NULL;
    }

    struct NodeDoente *cur = listD->first;
    while (cur != NULL) {
        if ( strcmp(cur->doente->name, name)==0 ) {
            return cur;
        }
        //printf("no: \"%s\"\n", cur->doente->name);
        cur = cur->next;
    }

    return NULL;
}

struct NodeDoente *findIDListDoente(struct ListaDoente *listD, int id) {
    /* Finds a Doente struct by ID in the ListDoente
     *
     * Returns:
     *      -> NULL if pointer is invalid / Doente not found
     *      -> valid pointer to NodeDoente struct if success
     */
    if (listD == NULL) {
        // invalid pointer
        return NULL;
    }

    struct NodeDoente *cur = listD->first;
    while (cur != NULL) {
        if (cur->doente->id == id) {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

int sortListDoenteID(struct ListaDoente *lista) {
    /* Sorts a "ListaRegisto" struct by ID with simple Bubble Sort
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (lista == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeDoente *cur = lista->first;
    struct NodeDoente *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        while (next != NULL) {
            if (cur->doente->id > next->doente->id) {
                // swap
                swapNodeDoente(cur, next);
            }
            next = next->next;
        }
        cur = cur->next;
    }
    return 0;
}

int sortListDoenteAlpha(struct ListaDoente *lista) {
    /* Sorts a "ListaRegisto" struct by Name in alphabetical order with simple Bubble Sort
     * Returns:
     *      -> -1 if invalid pointer
     *      -> 0 if success
     */
    if (lista == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeDoente *cur = lista->first;
    struct NodeDoente *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        while (next != NULL) {
            if (strcmp(cur->doente->name, next->doente->name) > 0) {
                // swap
                swapNodeDoente(cur, next);
            }
            next = next->next;
        }
        cur = cur->next;
    }
    return 0;
}

int printListDoente(struct ListaDoente *listD) {
    /* Prints the ListDoente struct
     * Returns:
     *      -> -1 if ListDoente pointer is NULL
     *     ->  0 if success
     */
    if (listD == NULL) {
        // invalid pointer
        return -1;
    }

    struct NodeDoente *cur = listD->first;
    while (cur != NULL) {
        printf("\n");
        printNodeDoente(cur);
        cur = cur->next;
    }

    return 0;
}



// File ---------------------------------

int Doente_appendFile(FILE *file, Doente *doente) {
    /* Appends the Doente struct to a file
     *
     * Returns:
     *      ->  0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 if Doente pointer is NULL
     */
    if (doente == NULL) {
        // invalid pointer
        return -2;
    }

    char buff[DATA_STRING_SIZE];
    data_toStr(&doente->birthday, buff);
    fprintf(file, "%d\n%s\n%s\n%s\n%d\n%s\n", doente->id, doente->name, buff, doente->cc, doente->tele, doente->email);

    return 0;
}

int Doente_readFile(FILE *file, Doente *doente) {
    /* Reads the Doente struct from a file
     *
     * Returns:
     *      ->  1 file at EOF
     *      ->  0 if success
     *      -> -1 if error read
     *      -> -2 if Doente pointer is NULL
     */
    if (doente == NULL) {
        // invalid pointer
        return -2;
    }

    // read from file
    char buff[PARAMS_DOENTE][DATA_STRING_SIZE];
    for (int i=0; i<PARAMS_DOENTE; i++) {
        if (fgets(buff[i], DATA_STRING_SIZE, file) == NULL) {
            // error reading file
            if (i==0) {
                // file at EOF
                return 1;
            } else {
                // error reading file
                return -1;
            }
        }
        buff[i][strlen(buff[i])-1] = '\0';      // remove '\n'
    }

    // set values
    doente->id = atoi(buff[0]);
    strcpy(doente->name, buff[1]);
    if (str_toData(buff[2], &doente->birthday)!=0) {
        // invalid date
        return -1;
    }
    strcpy(doente->cc, buff[3]);
    doente->tele = atoi(buff[4]);
    strcpy(doente->email, buff[5]);


    return 0;
}

int ListaDoente_toFile(char *filepath, struct ListaDoente *listD) {
    /* Writes the ListDoente to a file
     *
     * Returns:
     *      ->  0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 if ListDoente pointer is NULL
     */
    if (listD == NULL) {
        // invalid pointer
        return -2;
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        // invalid file
        return -1;
    }

    NodeDoente *cur = listD->first;
    while (cur != NULL) {
        if ( Doente_appendFile(file, cur->doente)!=0 ) {
            // error writing to file
            fclose(file);
            return -2;
        }
        cur = cur->next;
    }

    fclose(file);

    return 0;
}

int ListaDoente_readFile(char *filepath, struct ListaDoente *listD) {
    /* Reads the ListDoente from a file
     *
     * Returns:
     *      ->  1 if list is not empty
     *      ->  0 if success
     *      -> -1 if file pointer is NULL
     *      -> -2 if ListDoente pointer is NULL
     */
    if (listD == NULL) {
        // invalid pointer
        return 1;
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        // invalid file
        return -1;
    }

    struct Doente *new_Doente = createEmptyDoente();        // create new doente
    struct NodeDoente *new_NodeDoente;
    while ( Doente_readFile(file, new_Doente)==0 ) {
        new_NodeDoente = createNodeDoente(new_Doente);      // } create node
        if (new_NodeDoente == NULL) {
            // malloc failed
            fclose(file);
            return -2;
        }
        pushListDoente(listD, new_NodeDoente);              // push node to list

        new_Doente = createEmptyDoente();                   // create new doente
        if (new_Doente == NULL) {
            // malloc failed
            fclose(file);
            return -2;
        }
    }


    fclose(file);
    return 0;
}



#endif