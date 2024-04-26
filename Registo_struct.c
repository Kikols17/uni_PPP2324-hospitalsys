#ifndef REGISTO_C
#define REGISTO_C

#include <stdio.h>
#include <stdlib.h>

#include "Registo_struct.h"
#include "Data_struct.h"


Registo *createRegisto() {
    /* Return pointer to newly aloocated "Registo" struct */
    return malloc(sizeof(Registo));
}

void toFile_Registo(struct Registo *registo, FILE *fd) {
    toString_Data(&registo->date);
    fprintf(fd, "%d\n%s\n%d\n%d\n%d\n%d", registo->id, registo->date.str, registo->tens_max, registo->tens_min, registo->weight, registo->height);
}







#ifndef main
int main() {
    /* Test Case for "Regist_struct" */
    struct Registo *test_registo = createRegisto();
    
    if (test_registo!=NULL) {
        printf("\"test_registo\" created successfully\n");
    } else {
        printf("error creating \"test_registo\"\n");
    }
    return 0;
}
#endif



#endif