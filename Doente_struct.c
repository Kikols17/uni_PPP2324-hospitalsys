#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>

#include "Doente_struct.h"


struct Doente *createDoente() {
    /* Return pointer to newly allocated "Doente" struct */
    return malloc(sizeof(Doente));
}

#endif