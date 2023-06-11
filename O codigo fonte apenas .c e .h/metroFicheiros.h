//
// Created by 35193 on 05/06/2023.
//

#ifndef PTHF2023_METROFICHEIROS_H
#define PTHF2023_METROFICHEIROS_H
#include "estruturas.h"

void guardaDados(paragem *b, int total, Plinhas  p);
int recuperaDadosDeParagens(paragem** Pgem, int *total, Plinhas* p);
Plinhas insere_linha_final(Plinhas p, Plinhas novo);
PLinhaParagem insere_paragemnNaLinha_final(PLinhaParagem p, PLinhaParagem novo);
Plinhas inserir_linha(Plinhas L, paragem* p,  int NumParagens);
#endif //PTHF2023_METROFICHEIROS_H
