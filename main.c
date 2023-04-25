#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include <string.h>
#define tamCodigo 4
#define tamNome 30

typedef struct paragens{
    char codigo[tamCodigo + 1];
    char nome[tamNome];
    int numLinhas;
}paragem;


void geracodigo(char* p, paragem* PGEM, int tam);
void escrevecomandos();
paragem* addParagem(paragem* PGEM, int *tam);
paragem registarParagem(paragem* PGEM, int tam);
void pritparagens(paragem* PGEM, int tam);
paragem* eliminaParagem(paragem* PGE, int* tam);

int main() {
    char cmd[29];
    paragem *PGEM = NULL;
    int tamPGEM = 0;

    do{
        escrevecomandos();
        printf("\n\t\tcomando:");
        scanf("%28[^\n]", &cmd);
        fflush(stdin);

        if(strcmp(cmd, "ver paragens") == 0){
            pritparagens(PGEM, tamPGEM);
        }else
            if(strcmp(cmd, "adicionar paragem") == 0){
                PGEM = addParagem(PGEM, &tamPGEM);
        }else
            if(strcmp(cmd, "eliminar paragem") == 0){
                PGEM = eliminaParagem(PGEM, &tamPGEM);
        }else
            if(strcmp(cmd, "123") == 0){
                printf("numero de paragem no sistema = %i", tamPGEM);
        }else{
                printf("\n\t\t\t--->comando nao existe\n");
            }


    } while (strcmp(cmd, "sair") != 0);


    if(PGEM != NULL)
        free(PGEM);
    return 0;
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

void geracodigo(char p[], paragem* PGEM, int tam){
    int i;

    // Inicializa o gerador de números aleatórios com o tempo atual;
    srand(time(NULL));
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

paragem registarParagem(paragem* PGEM, int tam){
    paragem info;

    //nome da paragem
    printf("\nqual e o nome da paragem: ");
    scanf("%29[^\n]", &info.nome);
    fflush(stdin);

    //gerar codigo da paragem
    geracodigo(&info.codigo, PGEM, tam);
    printf("\no cogido gerado para essa paragem e: %s", info.codigo);

    info.numLinhas = 0;
    return info;
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
        printf("\nParagem esta acusiada a alguma linha");
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

void pritparagens(paragem PGEM[], int tam){
    if(tam == 0){
        printf("nao ha paragens");
    }
    for (int i = 0; i < tam; ++i) {
        printf("\nnome da paragem: %s\t", PGEM[i].nome);
        printf("codigo: %s\t", PGEM[i].codigo);
        printf("numero de paragem : %i", PGEM[i].numLinhas);
    }
    putchar('\n');

}

void escrevecomandos(){
    printf("\n\t comando: \"sair\" - para terminar.");
    printf("\n\t comando: \"ver paragens\" - para ver todas as paragens.");
    printf("\n\t comando: \"eliminar paragem\" - para apagar uma paragem.");
    printf("\n\t comando: \"adicionar paragem\" - para adicionar uma paragem.");
    printf("\n\t comando: \"eliminar paragens\" - &&&&&");
    printf("\n\t comando: \"eliminar paragens\" - &&&&&&");
    printf("\n\t comando: \"eliminar paragens\" - &&&&&");
    putchar('\n');

}