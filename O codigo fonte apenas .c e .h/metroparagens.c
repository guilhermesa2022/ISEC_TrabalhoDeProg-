//
// paulo guilherme lopes sá a2021142819
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "metroparagens.h"

void geracodigo(char p[], paragem* PGEM, int tam){
    int i;
    // Inicializa o gerador de números aleatórios com o tempo atual;
    srand((unsigned int)time(NULL));
    do{
        printf("\nvou criar uum codigo");
        for(i=0; i < tamCodigo ; i++){
            if (i == 0){
                p[i] = 'A' + (rand() % 26);
            }else{
                p[i] = '0' + (rand() % 10);
            }
        }
        p[i+1]= '\0';

        for(i = 0; i < tam && strcmp(p,PGEM[i].codigo) != 0; i++)
            ;

    } while (i != tam);
}

void escrevecomandos(){
    printf("\n\t comando: \"adicionar paragem\"      - para adicionar uma paragem.");
    printf("\n\t comando: \"eliminar paragem\"       - para apagar uma paragem.");
    printf("\n\t comando: \"ver paragens\"           - para ver todas as paragens.");
    printf("\n\t comando: \"adicionar linha\"        - para adicionar uma linha");
    printf("\n\t comando: \"eliminar linha\"         - para apagar uma linha");
    printf("\n\t comando: \"ver linhas\"             - para ver todas as linhas");
    printf("\n\t comando: \"adicionar no a linha\"   - para associar uma paragem a uma linha");
    printf("\n\t comando: \"eliminar no a linha\"    - para desassociar uma paragem de uma linha");
    printf("\n\t comando: \"localizar\"              - para ver todas as linhas que aquela paragem está associada");
    printf("\n\t comando: \"inserir linha\"          - para inserir uma linha completa tem que ter um ficheiro como a informacao");
    printf("\n\t comando: \"calcular percurso\"      - para calcular percurso até mudança para uma linha");
    printf("\n\t comando: \"sair\"                   - para terminar.");
    putchar('\n');
}

paragem* addParagem(paragem* PGEM, int *tam){
    paragem* AUX;
    AUX = realloc(PGEM, sizeof(paragem) * (*tam+1));
    if (AUX != NULL){
        PGEM = AUX;
        PGEM[*tam] = registarParagem(PGEM, *tam);
        (*tam)++;
    }else{
        printf("\n\t-----\ndeu algum erro no realloc desculpe!\n\t-----");
    }
    return PGEM;
}

paragem registarParagem(paragem* PGEM, int tam){
    paragem info;

    //nome da paragem
    //gerar codigo da paragem
    geracodigo(info.codigo, PGEM, tam);
    printf("\no cogido gerado para essa paragem e: %s", info.codigo);

    //nome da paragem
    printf("\nqual e o nome da paragem: ");
    scanf(" %29[^\n]", info.nome);


    info.numLinhas = 0;
    return info;
}

void pritparagens(paragem PGEM[], int tam){
    if(tam == 0){
        printf("Nao Ha Paragens");
        return ;
    }
    for (int i = 0; i < tam; ++i) {
        printf("\nCodigo: %s\t", PGEM[i].codigo);
        printf("Numero De Paragem : %i\t", PGEM[i].numLinhas);
        printf("Nome Da Paragem: %s", PGEM[i].nome);
    }
    putchar('\n');

}

paragem* eliminaParagem(paragem* PGEM, int* tam){

    if(*tam == 0){
        printf("\n nao ha paragem para eliminar");
        return PGEM;
    }

    char stg[tamCodigo+2];
    int i;
    paragem *aux, guarda;
    printf("\nescreva o codigo da paragem que quer eliminar: ");
    scanf("%s", stg);
    fflush(stdin);

    for(i = 0; i < *tam && strcmp(stg, PGEM[i].codigo) != 0; i++)
        ;
    fflush(stdin);

    if(i == *tam){
        printf("\nParagem nao existe");
        return PGEM;
    }else
    if(PGEM[i].numLinhas != 0){
        printf("\nParagem esta associada a alguma linha");
        return PGEM;
    }else
    if(*tam == 1){
        free(PGEM);
        *tam = 0;
        printf("\nparagem eliminada com sucesso");
        return NULL;
    }else{
        guarda = PGEM[i];
        PGEM[i] = PGEM[*tam - 1];
        aux = realloc(PGEM, sizeof(paragem) * (*tam-1));

        if(aux == NULL){
            PGEM[i] = guarda;
            return PGEM;
        }else{
            printf("\nparagem eliminada com sucesso");
            PGEM = aux;
            (*tam)--;
            return PGEM;
        }
    }
}