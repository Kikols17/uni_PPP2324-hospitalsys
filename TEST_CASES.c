#include <stdio.h>
#include <stdlib.h>

#include "Data_struct.h"
#include "Registo_struct.h"
#include "Doente_struct.h"


int main() {
    printf("TEST CASES FILE.\n");
    printf("\nTesting \"Data_struct\":\n");

    /* Test Case for "Data_struct" */
    // test "struct Data"'s "createData"
    struct Data *test_data = createData(2024, 12, 31);
    if (test_data!=NULL) {
        printf("\"test_data\" created successfully\n");
    } else {
        printf("error creating \"test_data\"\n");
        return -1;
    }

    // test "struct Data"'s "toString_Data"
    char buff[DATA_STRING_SIZE];
    toString_Data(test_data, buff);
    fprintf(stdout, "TEST_DATA string:\n\texpected:\t31/12/2024\n\tgot:\t%s\n", buff);

    return 0;
}