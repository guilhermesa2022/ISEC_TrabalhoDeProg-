//
// paulo guilherme lopes sá a2021142819
//

#ifndef PTHF2023_METROLINHASPARAGENS_H
#define PTHF2023_METROLINHASPARAGENS_H
#include "estruturas.h"

void ListarLinhas(Plinhas p);
Plinhas addlinha(Plinhas p);
Plinhas eliminalinha(Plinhas p);
void preenche(Plinhas Novo, Plinhas p);
int verificaSeExiste(char nome[tamNome], Plinhas p);
void liberta_lista(Plinhas p);
void inserirNoInicio(Plinhas p, paragem *Pgem, int num, int pos);
void localizar_paragem(paragem* Pgem, int numparagem, Plinhas p);
void eliminarNoDaLinha(Plinhas p, paragem *Pgem, int num);


int calcularpercursoNumalinha(Plinhas L, paragem* P, int O, int D);
int funcaoCalculaUmLinha(PLinhaParagem P, char destinio[tamCodigo+1], PLinhaParagem* Ppercurso, int* num);
void calcularpercurso(Plinhas L, paragem* P,  int NumParagens);
int calcularpercursoEm2Linhas(Plinhas L, paragem* P, int O, int D, int NumParagens);
arrylinha* localizarlinhas(Plinhas p, paragem paragem1, int *numDeLinha);
int calcularmeio(Plinhas L , char* linhas1, char* linhas2, char* paragemDoMeio);
void percurcer(Plinhas L, paragem* P, int O, int D, char nomelinha[30]);

#endif //PTHF2023_METROLINHASPARAGENS_H
