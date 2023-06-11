//
// paulo guilherme lopes sá a2021142819
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "metroLinhasParagens.h"

void ListarLinhas(Plinhas p){
    if(p == NULL){
        printf("Nao Ha Linhas");
        return ;
    }
    PLinhaParagem aux;
    while (p != NULL){
        printf("\n%s numero de paragens = %i", p->Nome, p->numDePagagens);
        aux = p->InicioParagem;
        while (aux != NULL){
            printf("\n\t-->nome: %s //codigo: %s", aux->nome, aux->codigo);
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }
}

Plinhas addlinha(Plinhas p){
    Plinhas Novo;
    Novo = malloc(sizeof(linhas));
    if(Novo == NULL){
        printf("\nErro na alocacao de memoria");
    }else{
        preenche(Novo, p);
        Novo->Prolinha = p;
        p = Novo;
    }
    return p;
}

Plinhas eliminalinha(Plinhas p){
    if(p == NULL){
        printf("noa ha linhas para eliminar");
        return p;
    }
    char nome[30];
    Plinhas aux = p, TEMP = NULL;
    printf("que linha quer eliminar: ");
    scanf(" %29[^\n]", nome);
    if(strcmp(nome, aux->Nome) ==0){
        if (aux->InicioParagem != NULL){
            printf("\nEsta linha nao pode ser eliminada porque tem paragens");
            return p;
        }
        //printf("\nentrei no primero if");
        aux = aux->Prolinha;
        free(p);
        p = aux;
    }else{
        while (aux != NULL && strcmp(nome, aux->Prolinha->Nome) !=0){
            aux = aux->Prolinha;
        }
        if(aux->Prolinha->InicioParagem != NULL){
            printf("\nEsta linha nao pode ser eliminada porque tem paragens");
            return p;
        }
        TEMP = aux->Prolinha;
        aux->Prolinha = aux->Prolinha->Prolinha;
        free(TEMP);
    }

    return p;
}

void preenche(Plinhas Novo, Plinhas p){
    do {
        printf("\nNome da linha: ");
        scanf(" %29[^\n]", Novo->Nome);
    } while (verificaSeExiste(Novo->Nome, p));
    Novo->numDePagagens = 0;
    Novo->InicioParagem = NULL;
    Novo->Prolinha = NULL;
}

int verificaSeExiste(char nome[30], Plinhas p){
    while (p != NULL){
        if(!strcmp(p->Nome, nome)){
            printf("\no nome da linha ja existe por favor tente novamente como outro nome");
            return 1;
        }
        p = p->Prolinha;
    }
    return 0;
}

void liberta_lista(Plinhas p)
{
    Plinhas aux;
    while(p != NULL)
    {
        aux = p;
        p = p->Prolinha;
        free(aux);
    }
}

void inserirNoInicio(Plinhas p, paragem *Pgem, int num, int pos){
    if(p != NULL && Pgem != NULL){
        char linhanome[30];
        int i, j;
        PLinhaParagem Pparagem = NULL, aux = NULL;


        printf("\nEscreva O Nome Da Linha: ");
        scanf(" %29[^\n]", linhanome);
        //aponta para o inicio da lista que quer inserir paragens e ver se existe;
        while(p != NULL && strcmp(linhanome, p->Nome) != 0){
            printf("linha - %s", p->Nome);
            p = p->Prolinha;
        }
        if(p == NULL){
            printf("\nnome da linha nao existe por favor voltar a tentar");
            return ;
        }

        if(pos == -1 || pos == -2){
            if(pos == -2){
                pos = p->numDePagagens+1;
            }else{
                printf("\nEscreva o  lugar da paragem: ");
                scanf("%d", &pos);
                if(pos <= 1 || pos > p->numDePagagens){
                    printf("Esse lugar nao existe");
                    return ;
                }
            }
        }

        Pparagem = malloc(sizeof(linhaparagem));

        printf("\nEscreva o codigo da paragem que quer inserir : ");
        scanf(" %29[^\n]", Pparagem->codigo);

        for (i = 0; i < num && strcmp(Pparagem->codigo, Pgem[i].codigo) != 0 ; ++i)
            ;
        if(i == num){
            printf("\nCodigo da paragem nao existe por favor voltar a tentar");
            free(Pparagem);
            return ;
        }

        strcpy(Pparagem->nome, Pgem[i].nome);
        Pparagem->ant = NULL;
        Pparagem->Prox = NULL;


        if(p->InicioParagem == NULL){
            p->numDePagagens++;
            (Pgem[i].numLinhas)++;
            p->InicioParagem = Pparagem;
        }else if(pos == 1){
            p->numDePagagens++;
            (Pgem[i].numLinhas)++;
            Pparagem->Prox = p->InicioParagem;
            p->InicioParagem->ant = Pparagem;
            p->InicioParagem = Pparagem;
        }else{
            aux = p->InicioParagem;
            for (j = 1; aux->Prox!=NULL && j<pos-1; j++)
                aux = aux->Prox;

            Pparagem->Prox = aux->Prox;
            if(aux->Prox != NULL)
                aux->Prox->ant = Pparagem;
            Pparagem->ant = aux;
            aux->Prox = Pparagem;
            p->numDePagagens++;
            (Pgem[i].numLinhas)++;
        }
        return ;
    }else{
        printf("\n\t\t--->nao ha paragem ou linha registado no programa para fazer essa operacao");
    }
}

void localizar_paragem(paragem* Pgem, int numparagem, Plinhas p){
    int i;
    PLinhaParagem aux;
    char codigo[tamCodigo + 1];

    printf("Escreva o codigo da paragem que ter procurar:");
    scanf("%s", codigo);

    for(i=0; i < numparagem && strcmp(codigo, Pgem[i].codigo) != 0; i++)
        ;

    if(i == numparagem){
        printf("essa paragens nao existe");
        return ;
    }

    while(p != NULL){
        aux = p->InicioParagem;
        while(aux != NULL){
            if(strcmp(aux->codigo, codigo) == 0){
                printf("\nEssa paragem existe na linha : %s", p->Nome);
                break;
            }
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }
}

void eliminarNoDaLinha(Plinhas p, paragem *Pgem, int num){

    if(p == NULL){
        printf("\nnao ha linha");
        return ;
    }

    int i;
    char nomeDaLinha[tamNome], codigo[tamCodigo + 1];
    printf("\nescreva o nome da linha, que a paragem que você quer eliminar pertence: ");
    scanf(" %29[^\n]", nomeDaLinha);

    while (p != NULL && strcmp(p->Nome, nomeDaLinha) != 0)
        p = p->Prolinha;

    if(p == NULL){
        printf("\n o nome que voce inserou nao existe");
        return ;
    }

    PLinhaParagem aux;
    aux = p->InicioParagem;
    printf("\nescreva o codigo da paragem que voce perdende eliminar da linha: ");
    scanf(" %s", codigo);

    while (aux != NULL && strcmp(aux->codigo, codigo) != 0)
        aux = aux->Prox;

    if(aux == NULL){
        printf("nao existe essa paragem nessa linha");
        return ;
    }

    // encontrae a onde esta a paregem no array dinamoco para diminor o numero de linhas que a paragem esta;;
    for (i = 0; i < num && strcmp(codigo, Pgem[i].codigo) != 0 ; ++i)
        ;


    if(aux == p->InicioParagem)
    {
        p->numDePagagens--;
        Pgem[i].numLinhas--;
        p->InicioParagem = aux->Prox;
        if(p->InicioParagem != NULL)
            p->InicioParagem->ant = NULL;
    }else{
        p->numDePagagens--;
        Pgem[i].numLinhas--;
        aux->ant->Prox = aux->Prox;
        if(aux->Prox != NULL)
            aux->Prox->ant = aux->ant;
    }
    free(aux);
}

int calcularpercursoNumalinha(Plinhas L, paragem* P, int O, int D){
    //printf("%i %i", O, D);
    //perguntar nos nome de origem e de destino
    int numorigem_destino;

    Plinhas lnova = L, auxlinha = NULL;
    PLinhaParagem aux = NULL, arryDeParagens = NULL;

    //printf(" vou para o lop");
    int sair_while_externo = 0, encontrei = 0;
    //carcolar em uma linha sem mudansas de linha


    for (int i = 0; i < P[O].numLinhas && !encontrei  ; ++i) {
        arryDeParagens = NULL;
        while (lnova != NULL && !sair_while_externo){
            //printf("\n%s numero de paragens = %i", lnova->Nome, lnova->numDePagagens);
            aux = lnova->InicioParagem;
            while (aux != NULL){
                //    printf("\n\t-->nome: %s //codigo: %s ", aux->nome, aux->codigo);
                if (!strcmp(P[O].codigo, aux->codigo))
                {
                    sair_while_externo = 1; // Sai do laço while externo
                    break; // Sai do laço while interno
                }
                aux = aux->Prox;
            }
            auxlinha = lnova;
            lnova = lnova->Prolinha;
        }

        lnova = auxlinha;
        //printf("\n\t\t\tteste ___ nome da linha #%s# nome paragens p.codigo = %s 66 %s", lnova->Nome, aux->codigo, P[O].codigo);
        encontrei = funcaoCalculaUmLinha(aux, P[D].codigo, &arryDeParagens, &numorigem_destino);
        if(encontrei == 3){
            return 0;
        }
        //printf("\n----------%i---------------------\n", encontrei);
        sair_while_externo = 0;
        lnova = lnova->Prolinha;
    }

    if (encontrei){
        //printf("paragens da paragem %s # %s ate a paragens %s # %s sem mudanca de linha",  P[O].nome, P[O].codigo, P[D].nome,  P[D].codigo);
        for (int i = 0; i < numorigem_destino; ++i) {
            printf("\nparagens %s # %s", arryDeParagens[i].nome, arryDeParagens[i].codigo);
        }
        putchar('\n');
        free(arryDeParagens);
        arryDeParagens = NULL;
        return 1;
    }

    free(arryDeParagens);
    arryDeParagens = NULL;

    return 0;
}

int funcaoCalculaUmLinha(PLinhaParagem P, char destinio[tamCodigo+1], PLinhaParagem* Ppercurso, int* num){
    *num = 0;
    PLinhaParagem AUXP = P, aux = NULL;
    while(AUXP != NULL){

        if((aux = realloc(*Ppercurso, sizeof (linhaparagem)*(*num+1))) == NULL){
            printf("Erro na realocacao de memoria");
            free(*Ppercurso);
            return 3;
        }
        *Ppercurso = aux;
        (*num)++;
        strcpy((*Ppercurso)[(*num)-1].nome, AUXP->nome);
        strcpy((*Ppercurso)[(*num)-1].codigo, AUXP->codigo);
        (*Ppercurso)[(*num)-1].ant = NULL; (*Ppercurso)[(*num)-1].ant = NULL;

        //printf("\n\t\t\t-->---> %s", AUXP->nome);
        if(!strcmp(AUXP->codigo, destinio)){
            //    printf("\n\t\t VOLTAR PARA A FUNCAO \n\n");
            return 1;
        }
        AUXP = AUXP->Prox;
    }

    free(*Ppercurso);
    *Ppercurso = NULL;
    AUXP = P;
    *num = 0;

    while(AUXP != NULL){

        if((aux = realloc(*Ppercurso, sizeof (linhaparagem)*(*num+1))) == NULL){
            printf("Erro na realocacao de memoria");
            return 3;
        }
        *Ppercurso = aux;
        (*num)++;
        strcpy((*Ppercurso)[(*num)-1].nome, AUXP->nome);
        strcpy((*Ppercurso)[(*num)-1].codigo, AUXP->codigo);
        (*Ppercurso)[(*num)-1].ant = NULL; (*Ppercurso)[(*num)-1].ant = NULL;

        //printf("\n\t\t\t-->---> %s", AUXP->nome);
        if(!strcmp(AUXP->codigo, destinio)){
            //    printf("\n\t\t VOLTAR PARA A FUNCAO \n\n");
            return 1;
        }
        AUXP = AUXP->ant;
    }

    free(*Ppercurso);
    *Ppercurso = NULL;
    *num = 0;

    return 0;
}

void calcularpercurso(Plinhas L, paragem* P,  int NumParagens){

    char origem[tamNome], destino[tamNome];
    int O, D;

    printf("inserir o codigo da paragem de origem: ");
    scanf(" %29[^\n]", origem);
    printf("inserir o codigo da paragem de destino: ");
    scanf(" %29[^\n]", destino);
    putchar('\n');


    for(O = 0; O < NumParagens && strcmp(origem, P[O].codigo) != 0; O++)
        ;
    for(D = 0; D < NumParagens && strcmp(destino, P[D].codigo) != 0; D++)
        ;
    if(D == NumParagens || O == NumParagens || P[D].numLinhas == 0 || P[O].numLinhas == 0 || strcmp(P[O].codigo, P[D].codigo) == 0){
        printf("\nErro a inserir as paragens de destino e de origem tente de novo");
        return ;
    }


    if (calcularpercursoNumalinha(L, P, O, D)){
        return ;
    }

    if(calcularpercursoEm2Linhas(L, P, O, D, NumParagens)) {
        return;
    }

    printf("Nao foi possivel calcular percurso um linha");

}

void percurcer(Plinhas L, paragem* P, int O, int D, char nomelinha[30]){
    Plinhas laux = L;

    int encontrei, numorigem_destino = 0;
    PLinhaParagem arryDeParagens = NULL;
    PLinhaParagem aux = NULL;

    while (strcmp(nomelinha, laux->Nome) != 0)
        laux = laux->Prolinha;
    aux = laux->InicioParagem;
    while (strcmp(P[O].codigo, aux->codigo) != 0){
        aux = aux->Prox;
    }


    encontrei = funcaoCalculaUmLinha(aux, P[D].codigo, &arryDeParagens, &numorigem_destino);
    if(encontrei == 3){
        return;
    }

    printf("\n%s", nomelinha);
    for (int i = 0; i < numorigem_destino; ++i) {
        printf("\nparagens %s # %s", arryDeParagens[i].nome, arryDeParagens[i].codigo);
    }

    free(arryDeParagens);
}

int calcularpercursoEm2Linhas(Plinhas L, paragem* P, int O, int D, int NumParagens){
    arrylinha* linhas1[2];
    int numDeLinhas[2] = {0,0};
    int numMeio, p, k;

    if((linhas1[0] = localizarlinhas(L, P[O], &numDeLinhas[0])) == NULL){
        printf("Erro a encontar a linha que pertece a paragem %s", P[O].nome);
        return 0;
    }

    if((linhas1[1] = localizarlinhas(L, P[D], &numDeLinhas[1])) == NULL){
        printf("Erro a encontar a linha que pertece a paragem %s", P[D].nome);
        free(linhas1[0]);
        return 0;
    }

    /*for (int j = 0; j < numDeLinhas[0]; j++) ;
        //printf("\n\tteste depois de funcao = %s, %i", linhas1[0][j].nome, numDeLinhas[0]);
    printf("\na outra");
    for (int j = 0; j < numDeLinhas[1]; j++) ;
        //printf("\n\tteste depois de funcao = %s, %i", linhas1[1][j].nome, numDeLinhas[1]);*/

    // descuber o paragnes do meio
    char paragemDoMeio[tamCodigo+1];
    int Adeus = 0;

    for (p = 0; p < numDeLinhas[0]; p++) {
        for (k = 0; k < numDeLinhas[1]; k++) {
            //printf("\nteste linhas= %s\t%s",linhas1[0][p].nome ,linhas1[1][k].nome);
            if ((Adeus = calcularmeio(L ,linhas1[0][p].nome, linhas1[1][k].nome, paragemDoMeio))==1) {
                printf("\n\t paragem que de mudanca  = %s\n", paragemDoMeio);
                break;
            }
        }
        if (Adeus)
            break;
    }

    //printf("\n\nwwwdswddw");

    if(Adeus){

        for(numMeio = 0; numMeio < NumParagens && strcmp(paragemDoMeio, P[numMeio].codigo) != 0; numMeio++)
            ;

        percurcer(L, P, O, numMeio, linhas1[0][p].nome);
        percurcer(L, P, numMeio, D, linhas1[1][k].nome);
        for (int i = 0; i < 2; ++i) {
            free(linhas1[i]);
        }
        return 1;
    }
    for (int i = 0; i < 2; ++i) {
        free(linhas1[i]);
    }
    return 0;

}

arrylinha* localizarlinhas(Plinhas p, paragem paragem1, int *numDeLinha){
    arrylinha *returnar =   NULL, *temp = NULL;
    PLinhaParagem aux;
    int i = 0;
    while(p != NULL) {
        aux = p->InicioParagem;
        while (aux != NULL) {
            if (strcmp(aux->codigo, paragem1.codigo) == 0) {
                temp = realloc(returnar, sizeof(arrylinha) * (i + 1));
                if (temp == NULL) {
                    printf("\nErro alocar memoria");
                    free(returnar);
                    return NULL;
                }
                returnar = temp;
                strcpy(returnar[i].nome, p->Nome);
                //printf("\n+nao sie se isto esta certo caralho %s /// %i", returnar[i].nome, i);
                i++;
                (*numDeLinha)++;
                break;
            }
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }

    return returnar;

}

int calcularmeio(Plinhas L , char* linhas1, char* linhas2, char* paragemDoMeio){
    PLinhaParagem paragemLinha1 = NULL;
    PLinhaParagem paragemLinha2 = NULL;
    int numparagemLinha1, numparagemLinha2;
    Plinhas aux = L;

    //printf("\ntt (l= %s  %s)", linhas1 , linhas2);

    while (strcmp(aux->Nome, linhas1) != 0) {
        aux = aux->Prolinha;
       // printf("\nsssss %s", aux->Nome);
    }
    //printf("\naux -> nome %s  %s", aux->Nome, linhas1);
    paragemLinha1 = aux->InicioParagem;
    numparagemLinha1 = aux->numDePagagens;
    aux = L;
    while (strcmp(aux->Nome, linhas2) != 0) {
        aux = aux->Prolinha;
       // printf("\nsssss %s", aux->Nome);
    }
    //printf("\naux -> nome %s  %s", aux->Nome, linhas2);
    paragemLinha2 = aux->InicioParagem;
    numparagemLinha2 = aux->numDePagagens;
    //printf("\nnumparagemLinha1 = %i, numparagemLinha2 = %i",numparagemLinha1,numparagemLinha2);

    for (int i = 0; i < numparagemLinha1; i++) {
        for (int j = 0; j < numparagemLinha2; j++) {
            //printf("\n\tteste-> linha1 %s linha2 %s", paragemLinha1->nome, paragemLinha2->nome);
            if(strcmp(paragemLinha2->codigo, paragemLinha1->codigo) == 0){
                strcpy(paragemDoMeio,paragemLinha2->codigo);
                return 1;
            }
            paragemLinha2 = paragemLinha2->Prox;
        }
        paragemLinha2 = aux->InicioParagem;
        paragemLinha1 = paragemLinha1->Prox;
    }

    return 0;
}