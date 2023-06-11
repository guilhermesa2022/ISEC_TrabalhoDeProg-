//
// paulo guilherme lopes sá a2021142819
//

#ifndef PTHF2023_METROPARAGENS_H
#define PTHF2023_METROPARAGENS_H
#include "estruturas.h"

void geracodigo(char p[], paragem* PGEM, int tam);
void escrevecomandos();
paragem* addParagem(paragem* PGEM, int *tam);
paragem registarParagem(paragem* PGEM, int tam);
void pritparagens(paragem* PGEM, int tam);
paragem* eliminaParagem(paragem* PGE, int* tam);


#endif //PTHF2023_METROPARAGENS_H
