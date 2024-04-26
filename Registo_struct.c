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
    char strData[DATA_STRING_SIZE];
    toString_Data(&registo->date, strData);
    fprintf(fd, "%d\n%s\n%d\n%d\n%d\n%d\n", registo->id, strData, registo->tens_max, registo->tens_min, registo->weight, registo->height);
}






/*
int main2() {
    / Test Case for "Regist_struct" /
    struct Registo *test_registo = createRegisto();
    
    if (test_registo!=NULL) {
        printf("\"test_registo\" created successfully\n");
    } else {
        printf("error creating \"test_registo\"\n");
        return -1;
    }

    printf("\nWriting to File:\n");
    toFile_Registo(test_registo, stdout);
    return 0;
}
*/



#endif