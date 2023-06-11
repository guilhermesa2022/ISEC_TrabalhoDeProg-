//
// Created by 35193 on 05/06/2023.
//

#include "metroFicheiros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void guardaDados(paragem *b, int total, Plinhas  p){
    FILE *f;

    f = fopen("dadosDePragemELinhas.dat", "wb");
    if(f==NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        return ;
    }

    fwrite(&total, sizeof(int), 1, f);
    fwrite(b, sizeof(paragem), total, f);

    PLinhaParagem aux;

    while (p != NULL){
        fwrite(p, sizeof(linhas), 1, f);
        aux = p->InicioParagem;
        while (aux != NULL){
            fwrite(aux, sizeof(linhaparagem), 1, f);
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }

    fclose(f);
}

int recuperaDadosDeParagens(paragem** Pgem, int *total, Plinhas* p){
    FILE *f;
    paragem* b = NULL;
    Plinhas novo, TEMP = NULL;
    linhas linhaAUX;
    int numParagensNaLinha;
    PLinhaParagem novoPagagem;
    linhaparagem paragemAUX;

    f = fopen("dadosDePragemELinhas.dat", "rb");
    if (f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return 1;
    }

    fread(total, sizeof(int), 1, f);
    b = malloc(sizeof(paragem) * (*total));
    if(b == NULL){
        fclose(f);
        *total = 0;
        return 1;
    }

    fread(b, sizeof(paragem), *total, f);

    *Pgem = b;

    printf("\nos dados das paragens foi restaurado sem problemas");

    while(fread(&linhaAUX, sizeof(linhas), 1, f) == 1){
        novo = malloc(sizeof (linhas));
        if(novo == NULL){   fclose(f);  return 1;}
        *novo = linhaAUX;
        novo->Prolinha = NULL;
        novo->InicioParagem = NULL;
        TEMP =insere_linha_final(TEMP, novo);
        numParagensNaLinha = novo->numDePagagens;

        for (int i = 0; i < numParagensNaLinha; i++) {
            fread(&paragemAUX, sizeof(linhaparagem), 1, f);
            novoPagagem = malloc(sizeof(linhaparagem));
            if(novoPagagem == NULL){   fclose(f);  return 1;}
            *novoPagagem = paragemAUX;
            novoPagagem->Prox = NULL;
            novoPagagem->ant = NULL;
            novo->InicioParagem = insere_paragemnNaLinha_final(novo->InicioParagem, novoPagagem);
        }

    }
    printf("\ndeu tudo certo na restaurado dos dados");
    *p = TEMP;

    fclose(f);

    return 0;

}

Plinhas insere_linha_final(Plinhas p, Plinhas novo){
    Plinhas aux;
    if(p == NULL)
        p = novo;
    else
    {
        aux = p;
        while(aux->Prolinha != NULL)
            aux = aux->Prolinha;
        aux->Prolinha = novo;
    }
    return p;
}

PLinhaParagem insere_paragemnNaLinha_final(PLinhaParagem p, PLinhaParagem novo){
    PLinhaParagem aux;
    if(p == NULL)
        p = novo;
    else{
        aux = p;
        while(aux->Prox != NULL)
            aux = aux->Prox;
        aux->Prox = novo;
        novo->ant = aux;
    }
    return p;
}

Plinhas inserir_linha(Plinhas L, paragem* p,  int NumParagens){
    FILE *f;
    char nomeDoFicheiro[40];
    char nomelinha[tamNome];
    Plinhas aux = L;
    //printf("L == %p  aux == %p", aux,L);

    // pedir o nome do ficheiro e abrir se der certo contunioar se nao returnar para a main;
    printf("\nNome do ficheiro do que tem o dados da linha:");
    scanf(" %39[^\n]", nomeDoFicheiro);
    f = fopen(nomeDoFicheiro, "r");

    if(f == NULL){
        printf("\nErro no acesso ao ficheiro");
        return L;
    }

    // Pegar a primeira linha da ficheiro de txt que deve ser a nome da linha
    if(fgets(nomelinha, sizeof(nomelinha), f) == NULL){
        printf("\nErro na leitura do nome da linha");
        fclose(f);
        return L;
    }
    nomelinha[strlen(nomelinha) - 1] = '\0';

    if(aux != NULL) {
        //printf("\nqwweqeweqeqweqweqwewqe %s  %i", aux->Nome, strcmp(nomelinha, aux->Nome) != 0);
        while (aux->Prolinha != NULL && strcmp(nomelinha, aux->Nome) != 0){
            //printf("\nqwweqeweqeqweqweqwewqe %s qeweqwe", aux->Nome);
            aux = aux->Prolinha;
        }


        if (aux->Prolinha != NULL || strcmp(nomelinha, aux->Nome) == 0) {
            printf("\na linha \" %s \" ja existe!", aux->Nome);
            fclose(f);
            return L;
        }
    }

    // criar uma espaço de memória para a nova linha se der errado fechar o arquivo e retornar para a main

    Plinhas novaLinha = NULL;
    if((novaLinha = malloc(sizeof(linhas))) == NULL){
        printf("\nErro na alocacao de memoria");
        fclose(f);
        return L;
    }else{
        strcpy(novaLinha->Nome, nomelinha);
        novaLinha->InicioParagem = NULL;
        novaLinha->Prolinha = NULL;
        novaLinha->numDePagagens = 0;
    }
    printf("\n\t%s", novaLinha->Nome);

    /*ler as paragens lê o nome e o código até o que não for lido nao for 3 argumentos e
     * fazer um molloc para criar espaço para por as informações da paragem na linha */
    char nomeDaParagem[tamNome];
    char codigoParagem[tamCodigo+1];
    char espaco;
    PLinhaParagem Novaparagem = NULL;
    int i;

    while (fscanf(f, " %29[^#] %c %s",nomeDaParagem ,&espaco ,codigoParagem) == 3){
        nomeDaParagem[strlen(nomeDaParagem)-1] = '\0';
        if((Novaparagem = malloc(sizeof (linhaparagem))) == NULL){
            printf("\nErro na malloc para a paragem");
            free(novaLinha);
            fclose(f);
            return L;

        }else{
            for (i = 0; i < NumParagens && strcmp(codigoParagem, p[i].codigo) != 0 ; ++i)
                ;

            if(i == NumParagens){
                printf("\n\tEssa paragem \\\"%s\\\" nao existe  por isso nao vai ser implementada",codigoParagem);
            }else{
                if (strcmp(p[i].nome, nomeDaParagem) != 0) {
                    printf("\n\tO nome da paragem como o codigo %s nao condiz "
                           "\n\tPor essa motivo vai ser modificado de %s para %s", codigoParagem, nomeDaParagem,
                           p[i].nome);

                    strcpy(nomeDaParagem, p[i].nome);
                }
                //printf("\nvou priencer e por no final da lista de paragem");
                Novaparagem->Prox = NULL;
                Novaparagem->ant = NULL;
                strcpy(Novaparagem->codigo, codigoParagem);
                strcpy(Novaparagem->nome, nomeDaParagem);
                novaLinha->InicioParagem = insere_paragemnNaLinha_final(novaLinha->InicioParagem, Novaparagem);
                p[i].numLinhas++;
                novaLinha->numDePagagens++;
            }
        }
    }

    novaLinha->Prolinha = L;
    L = novaLinha;
    fclose(f);
    return L;
}