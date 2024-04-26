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
    /* Write to file "fd" the string version of "Doente"  in "doente" */
    toString_Data(&doente->birthday);
    fprintf(fd, "%d\n%s\n%s\n%d\n%d\n%s", doente->id, doente->name, doente->birthday.str, doente->cc, doente->tele, doente->email);
}







#ifndef main
int main() {
    /* Test Case for "Doente_struct" */
    struct Doente *test_doente = createDoente();
    if (test_doente!=NULL) {
        printf("\"test_doente\" created successfully\n");
    } else {
        printf("error creating \"test_doente\"\n");
    }
    return 0;
}
#endif


#endif