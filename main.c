#include <stdio.h>
#include <stdlib.h>

#include "Doente_struct.h"
//#include "Registo_struct.h"
#include "Data_struct.h"


/*
    DÚVIDAS RELATIVAS AO PROGRAMA:
        - ID gerado ou atribuído na criação? - de momento atribuído
        - implementar extras?
        - eliminação por ID e nome ou só id? - de momento só ID
        - necessário guardar de imediato as alterações no txt ou só são guardados no fim da execução - de momento de imediato para não existir perda de dados

    VERIFICAR:
        - Não sei quanto a retornarmo algumas coisas na variável passada no parâmetro, ela muitas vezes não tem uso suficiente para justificar isto

    IDEIAS
        - talvez implementar na main uma struct q contenha os ponteiros das listas e o número de dados de cada uma
*/



#define MAIN
int main() {
    // criação da lista ligada dos doentes
    listaD doentes = createListD();

    read_Doentes(doentes);
    Doente d = {0,"Ulisses Catla",{20,2,2004},"30200000-7-ZX2",914123123,"ulisses@gmail.com"};
    //Doente *d1;
    /*if ((d1 = searchDoente_byID(doentes,3)) != NULL){
        print_Doente(*d1);
    }*/
    

    //insertD(doentes,d);

    /*if ((d1 = searchDoente_byID(doentes,3)) != NULL){
        print_Doente(*d1);
    }*/
    removeD(doentes,3);
    print_Alpha(doentes);

    destroyListD(doentes);
    return 0;
}