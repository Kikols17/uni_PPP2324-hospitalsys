#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Commands.h"
#include "Doente_struct.h"
#include "Registo_struct.h"
#include "Data_struct.h"

#define MAX_REQUEST_SIZE 1024


int request_handler(struct ListaDoente *ListD, struct ListaRegisto *ListR, char *request, char *response);



int main() {

    struct ListaDoente *ListD = createListaDoente();
    struct ListaRegisto *ListR = createListaRegisto();
    if ( ListD==NULL || ListR==NULL ) {
        printf("Error creating lists\n");
        return -1;
    }

    char request[MAX_REQUEST_SIZE];
    char response[MAX_REQUEST_SIZE];

    printf("Welcome to the Health System\n\t-> Try \"help\" for list of commands\n\n");
    while (1) {
        printf("> ");
        fgets(request, MAX_REQUEST_SIZE, stdin);
        request[strlen(request)-1] = '\0'; // remove '\n'

        response[0] = '\0';
        if (request_handler(ListD, ListR, request, response)==-1) {
            break;
        }
        printf("%s\n\n", response);
    }

    printf("--EXITING--\n");

    return 0;
}





int request_handler(struct ListaDoente *ListD, struct ListaRegisto *ListR, char *request, char *response) {
    /* Handles the request and returns the response
     * Returns:
     *      -> -1 end of program
     *      -> 0 if success
     *      -> 1 command not found
     *      -> 2 invalid format
     *      -> 3 error on command
     */
    char request_copy[MAX_REQUEST_SIZE];
    char *command;
    char *arg1, *arg2, *arg3, *arg4, *arg5, *arg6, *end;

    strcpy(request_copy, request);
    command = strtok(request_copy, " ");

    // Interpret the command
    if ( strcmp(command, "help")==0 ) {
        // HELP
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> help\n");
            return 2;
        }
        if ( cmd_help(response)!=0 ) {
            sprintf(response, "!!Error!! on help command\n");
            return 3;
        }
        return 0;
    

    } else if ( strcmp(command, "exit")==0 ) {
        // EXIT
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> exit\n");
            return 2;
        }
        return -1;


    } else if ( strcmp(command, "add_doente")==0 ) {
        // ADD_DOENTE
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, " ");
        arg4 = strtok(NULL, " ");
        arg5 = strtok(NULL, " ");
        arg6 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || arg2==NULL || arg3==NULL || arg4==NULL || arg5==NULL || arg6==NULL || end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> add_doente <id> <name> <birthday> <cc> <tele> <email>\n");
            return 2;
        }
        if ( cmd_AddDoente(ListD, atoi(arg1), arg2, arg3, arg4, atoi(arg5), arg6, response)!=0 ) {
            sprintf(response, "!!Error!! on add_doente command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "rmv_doente")==0 ) {
        // RMV_DOENTE
        arg1 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> rmv_doente <name>\n");
            return 2;
        }
        if ( cmd_RmvDoente(ListD, ListR, arg1, response)!=0 ) {
            sprintf(response, "!!Error!! on rmv_doente command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "list_alpha")==0 ) {
        // LIST_ALPHA
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> list_alpha\n");
            return 2;
        }
        if ( cmd_listAlpha(ListD, response)!=0 ) {
            sprintf(response, "!!Error!! on list_alpha command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "list_tens")==0 ) {
        // LIST_TENS
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || arg2==NULL || end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> list_tens <id> <min_tension>\n");
            return 2;
        }
        if ( cmd_listTens(ListD, ListR, atoi(arg1), atoi(arg2), response)!=0 ) {
            sprintf(response, "!!Error!! on list_tens command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "display_doente")==0 ) {
        // DISPLAY_DOENTE
        arg1 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> display_doente <name>\n");
            return 2;
        }
        if ( cmd_displayDoente(ListD, ListR, arg1, response)!=0 ) {
            sprintf(response, "!!Error!! on display_doente command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "add_registo")==0 ) {
        // ADD_REGISTO
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, " ");
        arg4 = strtok(NULL, " ");
        arg5 = strtok(NULL, " ");
        arg6 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || arg2==NULL || arg3==NULL || arg4==NULL || arg5==NULL || arg6==NULL || end!=NULL ) {
            sprintf(response, "Invalid format:\n\t-> add_registo <id> <date> <tens_max> <tens_min> <weight> <height>\n");
            return 2;
        }
        if ( cmd_AddRegisto(ListD, ListR, atoi(arg1), arg2, atoi(arg3), atoi(arg4), atoi(arg5), atoi(arg6), response)!=0 ) {
            sprintf(response, "!!Error!! on add_registo command\n");
            return 3;
        }
        return 0;
    }


    sprintf(response, "Command not found!\n\t-> Try \"help\" for list of commands\n");
    return 1;
}

