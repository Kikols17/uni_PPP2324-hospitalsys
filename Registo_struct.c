#ifndef REGISTO_C
#define REGISTO_C

#include <stdio.h>
#include <stdlib.h>

#include "Registo_struct.h"


Registo *createRegisto() {
    /* Return pointer to newly aloocated "Registo" struct */
    return malloc(sizeof(Registo));
}


#endif