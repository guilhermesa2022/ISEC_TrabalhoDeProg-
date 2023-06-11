//
// paulo guilherme lopes sá a2021142819
//

#ifndef PTHF2023_ESTRUTURAS_H
#define PTHF2023_ESTRUTURAS_H
#define tamCodigo 4
#define tamNome 30

typedef struct paragens{
    char codigo[tamCodigo + 1];
    char nome[tamNome];
    int numLinhas;
}paragem;

typedef struct paragenslinhas linhaparagem, *PLinhaParagem;
typedef struct dadolinha linhas, *Plinhas;

struct paragenslinhas{
    char nome[tamNome];
    char codigo[tamCodigo + 1];
    PLinhaParagem Prox;
    PLinhaParagem ant;
};

typedef struct nomelinha{
    char nome[tamNome];
}arrylinha;

struct dadolinha {
    int numDePagagens;
    char Nome[tamNome];
    Plinhas Prolinha;
    PLinhaParagem InicioParagem;
};

#endif //PTHF2023_ESTRUTURAS_H
