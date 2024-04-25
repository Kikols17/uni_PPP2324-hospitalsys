#ifndef DOENTE_C
#define DOENTE_C

#include <stdio.h>
#include <stdlib.h>

#include "Doente_struct.h"


struct Doente *createDoente() {
    /* Return pointer to newly allocated "Doente" struct */
    return malloc(sizeof(Doente));
}

void toFile_Doente(struct Doente *doente, FILE *fd) {
    toString_Data(&doente->birthday);
    fprintf(fd, "%d\n%s\n%s\n%d\n%d\n%s", doente->id, doente->name, doente->birthday.str, doente->cc, doente->tele, doente->email);
}

#ifndef main
int main() {
    return 0;
}
#endif


#endif