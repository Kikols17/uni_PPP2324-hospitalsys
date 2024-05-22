#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Doente_struct.h"
#include "Registo_struct.h"
#include "Data_struct.h"



int cmd_help(char *response);

int cmd_AddDoente(struct ListaDoente *listaD, char *name, char *birthday_char, char *cc, int tele, char *email, char *response);
int cmd_RmvDoente(struct ListaDoente *listaD, struct ListaRegisto *listR, char *name, char *response);
int cmd_listAlpha(struct ListaDoente *listaD, char *response);
int cmd_listTens(struct ListaDoente *listaD, struct ListaRegisto *listaR, char *name, int min_tension, char *response);
int cmd_displayDoente(struct ListaDoente *listaD, struct ListaRegisto *listaR, char *name, char *response);
int cmd_AddRegisto(struct ListaDoente *listaD, struct ListaRegisto *listaR, int id, char *date_char, int tens_max, int tens_min, int weight, int height, char *response);



#endif