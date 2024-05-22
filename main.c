#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Commands.h"
#include "Doente_struct.h"
#include "Registo_struct.h"
#include "Data_struct.h"

#define MAX_REQUEST_SIZE 1024
#define DOENTE_FILEPATH "doentes.txt"
#define REGISTO_FILEPATH "registos.txt"

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
    ListaDoente_readFile(DOENTE_FILEPATH, ListD);
    printf("Loading from file: \"%s\"\n", DOENTE_FILEPATH);
    ListaRegisto_readFile(REGISTO_FILEPATH, ListR);
    printf("Loading from file: \"%s\"\n", REGISTO_FILEPATH);
    while (1) {
        printf("\033[1;31m");
        printf("\n\n> ");
        fgets(request, MAX_REQUEST_SIZE, stdin);
        printf("\033[0m");
        request[strlen(request)-1] = '\0'; // remove '\n'

        response[0] = '\0';
        if (request_handler(ListD, ListR, request, response)==-1) {
            break;
        }
        printf("%s", response);
    }

    printf("--EXITING--\n");

    // destroy both lists
    destroyListaDoente(ListD);
    destroyListaRegisto(ListR);

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
    if ( command==NULL ) {
        return 1;
    }

    // Interpret the command
    if ( strcmp(command, "help")==0 ) {
        // HELP
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> help\n");
            return 2;
        }
        if ( cmd_help(response)<0 ) {
            sprintf(response+strlen(response), "!!Error!! on help command\n");
            return 3;
        }
        return 0;
    

    } else if ( strcmp(command, "exit")==0 ) {
        // EXIT
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> exit\n");
            return 2;
        }
        return -1;


    } else if ( strcmp(command, "add_doente")==0 ) {
        // ADD_DOENTE
        // arg1 is all that is between the first and second "
        arg1 = strtok(NULL, "\"");  // get the second "          add_doente "miguel castela" 12/04/2004 12345678-1-AAA 123456789 kiko@gmail.com
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, " ");
        arg4 = strtok(NULL, " ");
        arg5 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || strlen(arg1)==0 || arg2==NULL || arg3==NULL || arg4==NULL || arg5==NULL || end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:"
                                               "\n\t-> add_doente \"name\" <birthday> <cc> <tele> <email>\n"
                                               "\n\t\t(make sure that \"name\" is between \"\")\n");
            return 2;
        }
        if ( cmd_AddDoente(ListD, arg1, arg2, arg3, atoi(arg4), arg5, response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on add_doente command\n");
            return 3;
        }
        // add_doente "miguel castela" 12/04/2004 12345678-1-AAA 123456789 kiko@gmail.com
        return 0;


    } else if ( strcmp(command, "rmv_doente")==0 ) {
        // RMV_DOENTE
        // arg1 is all that is between the first and second "
        arg1 = strtok(NULL, "\"");
        end = strtok(NULL, " ");
        if ( arg1==NULL || end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> rmv_doente <name>\n"
                                               "\n\t\t(make sure that \"name\" is between \"\")\n");
            return 2;
        }
        if ( cmd_RmvDoente(ListD, ListR, arg1, response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on rmv_doente command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "list")==0 ) {
        // LIST_ALPHA
        end = strtok(NULL, " ");
        if ( end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> list\n");
            return 2;
        }
        if ( cmd_listAlpha(ListD, response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on list command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "list_tens")==0 ) {
        // LIST_TENS
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        end = strtok(NULL, " ");
        if ( arg1==NULL || arg2==NULL || end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> list_tens <id> <min_tension>\n");
            return 2;
        }
        if ( cmd_listTens(ListD, ListR, atoi(arg1), atoi(arg2), response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on list_tens command\n");
            return 3;
        }
        return 0;


    } else if ( strcmp(command, "display_doente")==0 ) {
        // DISPLAY_DOENTE
        // arg1 is all that is between the first and second "
        arg1 = strtok(NULL, "\"");
        end = strtok(NULL, " ");
        if ( arg1==NULL || end!=NULL ) {
            sprintf(response+strlen(response), "Invalid format:\n\t-> display_doente <name>\n"
                                               "\n\t\t(make sure that \"name\" is between \"\")\n");
            return 2;
        }
        if ( cmd_displayDoente(ListD, ListR, arg1, response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on display_doente command\n");
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
            sprintf(response+strlen(response), "Invalid format:\n\t-> add_registo <id> <date> <tens_max> <tens_min> <weight> <height>\n");
            return 2;
        }
        if ( cmd_AddRegisto(ListD, ListR, atoi(arg1), arg2, atoi(arg3), atoi(arg4), atoi(arg5), atoi(arg6), response)<0 ) {
            //sprintf(response+strlen(response), "!!Error!! on add_registo command\n");
            return 3;
        }
        return 0;
    }


    sprintf(response, "Command not found!\n\t-> Try \"help\" for list of commands\n");
    return 1;
}

