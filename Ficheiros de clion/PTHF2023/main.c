//
// paulo guilherme lopes sá a2021142819
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metroFicheiros.h"
#include "metroLinhasParagens.h"
#include "metroparagens.h"



int main() {
    char cmd[29];
    paragem *PGEM = NULL;
    int tamPGEM = 0;
    Plinhas listalinhas = NULL;
    int escolha = 0;

    //por os dados do ficheiros para memoria
     if (recuperaDadosDeParagens(&PGEM ,&tamPGEM, &listalinhas) == 1){
         printf("nao foi possivel returnar os dados do sistema");
     }


    do {
        escrevecomandos();
        printf("\n\t\tcomando:");
        scanf(" %28[^\n]", cmd);

        if (strcmp(cmd, "ver paragens") == 0) {
            pritparagens(PGEM, tamPGEM);
        } else if (!strcmp(cmd, "adicionar paragem")) {
            PGEM = addParagem(PGEM, &tamPGEM);
        } else if (!strcmp(cmd, "eliminar paragem")) {
            PGEM = eliminaParagem(PGEM, &tamPGEM);
        }else
        if(!strcmp(cmd, "123")){
            printf("numero de paragem no sistema = %i", tamPGEM);
        }else
        if(!strcmp(cmd, "adicionar linha")){
            listalinhas = addlinha(listalinhas);
        }else
        if(!strcmp(cmd, "ver linhas")){
            ListarLinhas(listalinhas);
        }else
        if(!strcmp(cmd, "eliminar linha")){
            listalinhas = eliminalinha(listalinhas);
        }else
        if(!strcmp(cmd , "adicionar no a linha")){

            printf("\n\tClicar 1 Para Inserir No Inicio;");
            printf("\n\tClicar 2 Para Inserir No Meio   - a linha tem que ter pelo menos 2 paragens;");
            printf("\n\tClicar 3 Para Inserir No Final; \n ===>");
            scanf("%d", &escolha);

            if(escolha == 1){
                inserirNoInicio(listalinhas, PGEM, tamPGEM, 1);
            } else if(escolha == 2){
                inserirNoInicio(listalinhas, PGEM, tamPGEM, -1);
            } else if (escolha == 3){
                inserirNoInicio(listalinhas, PGEM, tamPGEM, -2);
            } else{
                printf("\nnao existe essa escolha");
            }
        }else
        if(!strcmp(cmd, "eliminar no a linha")){
            eliminarNoDaLinha(listalinhas, PGEM, tamPGEM);
        }else
        if(!strcmp(cmd, "localizar")){
            localizar_paragem(PGEM, tamPGEM, listalinhas);
        }else
        if(!strcmp(cmd, "inserir linha")){
            listalinhas = inserir_linha(listalinhas, PGEM, tamPGEM);

        }else
        if(!strcmp(cmd, "calcular percurso")){
            calcularpercurso(listalinhas, PGEM, tamPGEM);
        }else
            printf("\n\t\t\t--->comando nao existe\n");


    } while (strcmp(cmd, "sair") != 0);

   guardaDados(PGEM, tamPGEM, listalinhas);

    if(PGEM != NULL)
        free(PGEM);
    liberta_lista(listalinhas);
        return 0;
    }