#include <stdio.h>
#include <stdlib.h>

#include "Doente_struct.h"
//#include "Registo_struct.h"
#include "Data_struct.h"

#define MAIN
int main() {
    // criação da lista ligada dos doentes
    listaD doentes = createListD();

    read_Doentes(doentes);




    destroyListD(doentes);
    return 0;
}