#ifndef COMMANDS_C
#define COMMANDS_C


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Doente_struct.h"
#include "Registo_struct.h"
#include "Data_struct.h"




int cmd_help(char *response) {
    /* Appends the help message to the response */
    sprintf(response+strlen(response), "Available commands:\n"
                                       "\t-> help\n"
                                       "\t-> exit\n"
                                       "\t-> add_doente \"name\" <birthday> <cc> <tele> <email>\n"
                                       "\t-> rmv_doente \"name\"\n"
                                       "\t-> list\n"
                                       "\t-> list_tens \"name\" <min_tension>\n"
                                       "\t-> display_doente \"name\"\n"
                                       "\t-> add_registo <id> <date> <tens_max> <tens_min> <weight> <height>\n");
    return 0;
}


int cmd_AddDoente(struct ListaDoente *listaD, char *name, char *birthday_char, char *cc, int tele, char *email, char *response) {
    /* Adds a doente to the list
     * 
     * Returns:
     *      -> -2 if invalid format
     *      -> -1 if error on creation of node+doente and insertion on list
     *      -> 0 if success
     *      -> 1 if doente already in system
     */
    struct Data birthday;
    char auxbuff[DATA_STRING_SIZE];
    int ret;

    // validate birthday
    strcpy(auxbuff, birthday_char);
    if ( str_toData(auxbuff, &birthday)!=0 ) {
        // data not in format "dd/mm/yyyy" or not valid
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Invalid birthday    dd/mm/yyyy\n");
        return -2;
    }

    // validate cc (must be in format 00000000-0-AA0)
    if ( strlen(cc)!=CHARS_CC-1 || cc[8]!='-' || cc[10]!='-' ) {
        // invalid cc
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Invalid cc          00000000-0-AAA\n");
        return -2;
    }

    // validate tele (must have 9 digits)
    if ( !(tele>=100000000 && tele<=999999999) ) {
        // invalid tele
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Invalid tele        123456789\n");
        return -2;
    }



    // find next available ID
    struct NodeDoente *cur = listaD->first;
    int id=0;
    sortListDoenteID(listaD);
    while ( cur!=NULL ) {
        if ( cur->doente->id==id ) {
            // used ID found, increment
            id++;
            cur = listaD->first;
        } else {
            // unused ID found, use it
            cur = cur->next;
            break;
        }
    }

    struct Doente *doente = createDoente(id, name, &birthday, cc, tele, email);
    if ( doente==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error creating doente:\n\t\tNot enought memory\n");
        return -1;
    }
    struct NodeDoente *node = createNodeDoente(doente);
    if ( node==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error creating node:\n\t\tNot enought memory.\n");
        destroyDoente(doente);
        return -1;
    }

    ret = pushListDoente(listaD, node);
    if ( ret==-1 ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error pushing node\n");
        destroyNodeDoente(listaD, node);
        return -1;
    } else if (ret==1) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente's ID already in system\n");
        destroyNodeDoente(listaD, node);
        return 1;
    } else if (ret==2) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente's name already in system\n");
        destroyNodeDoente(listaD, node);
        return 1;
    } else if (ret==3) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente's cc already in system\n");
        destroyNodeDoente(listaD, node);
        return 1;
    }
    sprintf(response+strlen(response), "Doente \"%s\" with ID%d added to system\n", name, id);
    return 0;
}

int cmd_RmvDoente(struct ListaDoente *listaD, struct ListaRegisto *listR, char *name, char *response) {
    /* Searches for doente by name in "lista" and removes it
     * 
     * Returns:
     *      -> -1 if error on removal
     *      -> 0 if success
     *      -> 1 if doente not in system
     */
    struct NodeDoente *node = findNameListDoente(listaD, name);
    if ( node==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente not in system\n");
        return 1;
    }
    if ( destroyNodeDoente(listaD, node)!=0 ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error destroying node\n");
        return -1;
    }

    // sort list by ID, so that all registo's from doente with ID "id" are together
    sortListRegistoID(listR);
    struct NodeRegisto *curR = findIDListRegisto(listR, node->doente->id);  // find first registo from doente with ID "id"
    struct NodeRegisto *nextR;
    while ( curR!=NULL && curR->registo->id==node->doente->id ) {
        // remove all registo's from doente with ID "id"
        nextR = curR->next;
        if (destroyNodeRegisto(listR, curR)!=0) {
            printf("Error destroying registo\n");
        }
        curR = nextR;
    }


    sprintf(response+strlen(response), "Doente \"%s\" removed from system\n(all \"registos\" for this user deleted as well)", name);
    return 0;
}

int cmd_listAlpha(struct ListaDoente *listaD, char *response) {
    /* Lists all doentes in "lista" in alphabetical order */
    struct NodeDoente *node = listaD->first;
    if ( node==NULL ) {
        sprintf(response+strlen(response), "-> No doentes in system\n");
        return 1;
    }
    if ( sortListDoenteAlpha(listaD)!=0 ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error sorting list\n");
        return -1;
    }

    sprintf(response+strlen(response), "Doentes in system:\n");
    while ( node!=NULL ) {
        sprintf(response+strlen(response), "\tID%d - %s\n", node->doente->id, node->doente->name);
        node = node->next;
    }
    return 0;
}

int cmd_listTens(struct ListaDoente *listaD, struct ListaRegisto *listaR, char *name, int min_tension, char *response) {
    /* Creates a temporary ListRegisto with all registo's from doente with ID "id" with tension above "min_tension"
     * Returns:
     *      -> -1 if error on creation of temporary list
     *      ->  0 if success
     *      ->  1 if doente not in system
     */
    struct NodeDoente *curD;
    struct NodeRegisto *curR;
    struct ListaRegisto *tempList;
    char auxbuff[DATA_STRING_SIZE];

    // find first registo from doente with ID "id"
    strcpy(auxbuff, name);
    curD = findNameListDoente(listaD, auxbuff);
    if ( curD==NULL ) {
        // Doente by ID not in system
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente not in system\n");
        return 1;
    }

    // sort list by ID, so that all registo's from doente with ID "id" are together
    sortListRegistoID(listaR);
    curR = findIDListRegisto(listaR, curD->doente->id);
    if ( curR==NULL ) {
        // Registo by ID not in system
        sprintf(response+strlen(response), "->Doente \"%s\" with id %d does not have any registos\n", curD->doente->name, curD->doente->id);
        return 1;
    }

    // create temporary list
    tempList = createListaRegisto();
    if ( tempList==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error creating temporary list\n");
        return -1;
    }

    // push all registo's with id and tension above "min_tension" to temporary list
    while ( curR!=NULL && curR->registo->id==curD->doente->id ) {
        if ( curR->registo->tens_max>=min_tension ) {
            // pushes true copy of registo to temporary list (must be true copy to avoid freeing at end of function)
            if ( pushListaRegisto(tempList, createNodeRegisto( createCopyRegisto(curR->registo) ))!=0 ) {
                // one step of pushing failed, destroy temporary list and return error
                sprintf(response+strlen(response), "->!ERROR!\n\t-> Error pushing registo to temporary list\n");
                destroyListaRegisto(tempList);
                return -1;
            }
        }
        curR = curR->next;
    }

    // print temporary list
    if ( min_tension!=-1 ) {
        // if min_tension is -1, don't print the message, it means we want to list all registo's from doente with ID "id"
        sprintf(response+strlen(response), "Registo's from doente \"%s\" with ID%d with tension above %d:\n", curD->doente->name, curD->doente->id, min_tension);
    }
    tostrListaRegisto(tempList, response+strlen(response));

    // destroy temporary list
    destroyListaRegisto(tempList);

    return 0;
}

int cmd_displayDoente(struct ListaDoente *listaD, struct ListaRegisto *listaR, char *name, char *response) {
    /* Displays all information about doente with name "name"
     * 
     * Returns:
     *      -> -1 if doente not in system
     *      ->  0 if success
     */
    struct NodeDoente *node;
    char auxbuff[DATA_STRING_SIZE];
    
    strcpy(auxbuff, name);
    node = findNameListDoente(listaD, auxbuff);
    if ( node==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente \"%s\" not in system\n", auxbuff);
        return -1;
    }
    // display doente's information
    sprintf(response+strlen(response), "->Doente \"%s\" with ID%d:\n", auxbuff, node->doente->id);
    tostrDoente(node->doente, response+strlen(response));

    // fetch all registo's from doente with ID "id".
    sprintf(response+strlen(response), "\nRegistos:\n");
    return cmd_listTens(listaD, listaR, auxbuff, -1, response);
}

int cmd_AddRegisto(struct ListaDoente *listaD, struct ListaRegisto *listaR, int id, char *date_char, int tens_max, int tens_min, int weight, int height, char *response) {
    /* Adds a registo to the list.
     * Only adds new registo if a doente with the same ID exists in the system
     * 
     * Returns:
     *      -> -2 if invalid date format
     *      -> -1 if error on creation of node+registo and insertion on list
     *      -> 0 if success
     */
    struct NodeDoente *nodeD;
    struct Registo *new_registo;
    struct NodeRegisto *nodeR;
    struct Data date;
    char auxbuff[DATA_STRING_SIZE];

    // search for doente with matching ID
    nodeD = findIDListDoente(listaD, id);
    if ( nodeD==NULL ) {
        // doente not in system, abort
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Doente not in system\n");
        return -1;
    }

    // create registo
    strcpy(auxbuff, date_char);
    if ( str_toData(auxbuff, &date)!=0 ) {
        // data not in format "dd/mm/yyyy"
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Invalid date\n");
        return -2;
    }
    new_registo = createRegisto(id, &date, tens_max, tens_min, weight, height);
    if ( new_registo==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error creating registo\n");
        return -1;
    }

    // create node and push to list
    nodeR = createNodeRegisto(new_registo);
    if ( nodeR==NULL ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error creating node\n");
        return -1;
    }
    if ( pushListaRegisto(listaR, nodeR)==-1 ) {
        sprintf(response+strlen(response), "->!ERROR!\n\t-> Error pushing node\n");
        return -1;
    }
    
    sprintf(response+strlen(response), "Registo added to system\n");
    return 0;
}


#endif