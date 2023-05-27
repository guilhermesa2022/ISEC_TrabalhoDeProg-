#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tamCodigo 4
#define tamNome 30
//#include <math.h>


typedef struct paragenslinhas linhaparagem, *PLinhaParagem;
typedef struct dadolinha linhas, *Plinhas;

struct paragenslinhas{
    char nome[tamNome];
    char codigo[tamCodigo + 1];
    PLinhaParagem Prox;
    PLinhaParagem ant;
};

struct dadolinha {
    int numDePagagens;
    char Nome[tamNome];
    Plinhas Prolinha;
    PLinhaParagem InicioParagem;
};

typedef struct paragens{
    char codigo[tamCodigo + 1];
    char nome[tamNome];
    int numLinhas;
}paragem;


void geracodigo(char p[], paragem* PGEM, int tam);
void escrevecomandos();
paragem* addParagem(paragem* PGEM, int *tam);
paragem registarParagem(paragem* PGEM, int tam);
void pritparagens(paragem* PGEM, int tam);
paragem* eliminaParagem(paragem* PGE, int* tam);
void ListarLinhas(Plinhas p);
Plinhas addlinha(Plinhas p);
Plinhas eliminalinha(Plinhas p);
void preenche(Plinhas Novo, Plinhas p);
int verificaSeExiste(char nome[tamNome], Plinhas p);
void liberta_lista(Plinhas p);
void inserirNoInicio(Plinhas p, paragem *Pgem, int num, int pos);
void localizar_paragem(paragem* Pgem, int numparagem, Plinhas p);
void eliminarNoDaLinha(Plinhas p, paragem *Pgem, int num);
void guardaDados(paragem *b, int total, Plinhas  p);
int recuperaDadosDeParagens(paragem** Pgem, int *total, Plinhas* p);
Plinhas insere_linha_final(Plinhas p, Plinhas novo);
PLinhaParagem insere_paragemnNaLinha_final(PLinhaParagem p, PLinhaParagem novo);
Plinhas inserir_linha(Plinhas L, paragem* p,  int NumParagens);
void calcularpercurso(Plinhas L, paragem* P,  int NumParagens);
int funcaoCalculaUmLinha(PLinhaParagem P, char origem[tamCodigo+1], char destinio[tamCodigo+1], PLinhaParagem* Ppercurso, int* num);

int funcaoCalculaUmLinha(PLinhaParagem P, char origem[tamCodigo+1], char destinio[tamCodigo+1], PLinhaParagem* Ppercurso, int* num){
    printf("destino %s", destinio);
    *num = 0;
    PLinhaParagem AUXP = P, aux = NULL;
    while(AUXP != NULL){
        if((aux = realloc(*Ppercurso, sizeof (linhaparagem)*(*num+1))) == NULL){
            printf("Erro na realocacao de memoria");
        }

        printf("\n\t\t\t-->---> %s", AUXP->nome);
        if(!strcmp(AUXP->codigo, destinio)){
            printf("\n\t\t VOLTAR PARA A FUNCAO \n\n");
            return 1;
        }
        AUXP = AUXP->Prox;
    }
    AUXP = P;
    while(AUXP != NULL){
        printf("\n\t\t\t-->---> %s", AUXP->nome);
        if(!strcmp(AUXP->codigo, destinio)){
            printf("\n\t\t VOLTAR PARA A FUNCAO \n\n");
            return 1;
        }
        AUXP = AUXP->ant;
    }
    return 0;
}

void calcularpercurso(Plinhas L, paragem* P,  int NumParagens){
    //perguntar nos nome de origem e de destino
    char origem[tamNome], destino[tamNome];
    int O, D, numorigem_destino;

    Plinhas lnova = L, auxlinha = NULL;
    PLinhaParagem aux = NULL, arryDeParagens = NULL;

    printf("inserir o codigo da paragem de origem: ");
    scanf(" %29[^\n]", origem);
    printf("inserir o codigo da paragem de destino: ");
    scanf(" %29[^\n]", destino);

    for(O = 0; O < NumParagens && strcmp(origem, P[O].codigo) != 0; O++)
        ;
    for(D = 0; D < NumParagens && strcmp(destino, P[D].codigo) != 0; D++)
        ;
    if(D == NumParagens || O == NumParagens || P[D].numLinhas == 0 || P[O].numLinhas == 0){
        printf("\nErro a inserir as paragens de destino e de origem tente de novo");
        return ;
    }

    printf(" vou para o lop");
    int sair_while_externo = 0, encontrei = 0;

    //carcolar em uma linha sem mudansas de linha
    for (int i = 0; i < P[O].numLinhas && !encontrei  ; ++i) {

        while (lnova != NULL && !sair_while_externo){
            printf("\n%s numero de paragens = %i", lnova->Nome, lnova->numDePagagens);
            aux = lnova->InicioParagem;
            while (aux != NULL && !sair_while_externo){
                printf("\n\t-->nome: %s //codigo: %s ", aux->nome, aux->codigo);
                if (!strcmp(P[O].codigo, aux->codigo))
                {
                    sair_while_externo = 1; // Sai do laço while externo
                    break; // Sai do laço while interno
                }
                aux = aux->Prox;
            }
            auxlinha = lnova;
            lnova = lnova->Prolinha->Prolinha;
        }
        lnova = auxlinha;
        printf("\n\t\t\tteste ___ nome da linha #%s# nome paragens p.codigo = %s 66 %s", lnova->Nome, aux->codigo, P[O].codigo);
        encontrei = funcaoCalculaUmLinha(aux, P[O].codigo, P[D].codigo, &arryDeParagens, &numorigem_destino);
        printf("\n-------------------------------\n");
        sair_while_externo = 0;
        lnova = lnova->Prolinha;
    }


}

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


    do{
        escrevecomandos();
        printf("\n\t\tcomando:");
        scanf(" %28[^\n]", cmd);

        if(!strcmp(cmd, "ver paragens")){
            pritparagens(PGEM, tamPGEM);
        }else
            if(!strcmp(cmd, "adicionar paragem")){
                PGEM = addParagem(PGEM, &tamPGEM);
        }else
            if(!strcmp(cmd, "eliminar paragem")){
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
                    printf("\nh nao existe");
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

Plinhas inserir_linha(Plinhas L, paragem* p,  int NumParagens){
    FILE *f;
    char nomeDoFicheiro[40];
    char nomelinha[tamNome];
    Plinhas aux = L;
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

    if(aux != NULL) {
        while (aux->Prolinha != NULL && strcmp(nomelinha, aux->Nome) != 0)
            aux = aux->Prolinha;

        if (aux->Prolinha != NULL) {
            printf("\na linha \" %s \" ja existe!", aux->Nome);
            fclose(f);
            return L;
        }
    }

    // criar uma espaço de memória para a nova linha se der errado fechar o arquivo e retornar para a main
    printf("\n\t\ttesteee");

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
    printf("\n\t\t\tteste ---=== %s", novaLinha->Nome);

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
                printf("\n\tEssa paragem \\\"%s\\\" nao existe  por isso nao vai ser implementadaa",codigoParagem);
            }else{
                if (strcmp(p[i].nome, nomeDaParagem) != 0) {
                    printf("\n\tO nome da paragem como o codigo %s nao condiz "
                           "\n\tPor essa motivo vai ser modificado de %s para %s", codigoParagem, nomeDaParagem,
                           p[i].nome);
                    strcpy(nomeDaParagem, p[i].nome);
                }
                printf("\nvou priencer e por no final da lista de paragem");
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

void preenche(Plinhas Novo, Plinhas p){
    do {
        printf("\nNome da linha: ");
        scanf(" %29[^\n]", Novo->Nome);
    } while (verificaSeExiste(Novo->Nome, p));
    Novo->numDePagagens = 0;
    Novo->InicioParagem = NULL;
    Novo->Prolinha = NULL;
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
        printf("\nentrei no primero if");
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
            printf("\n\t-->nome: %s //codigo: %s ", aux->nome, aux->codigo);
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }
}

void escrevecomandos(){
    printf("\n\t comando: \"adicionar paragem\"      - para adicionar uma paragem.");
    printf("\n\t comando: \"eliminar paragem\"       - para apagar uma paragem.");
    printf("\n\t comando: \"ver paragens\"           - para ver todas as paragens.");
    printf("\n\t comando: \"adicionar linha\"        - para adicionar uma linha");
    printf("\n\t comando: \"eliminar linha\"         - para apagar uma linha");
    printf("\n\t comando: \"ver linhas\"             - para ver todas as linhas");
    printf("\n\t comando: \"adicionar no a linha\"   - para ver todas as linhas");
    printf("\n\t comando: \"eliminar no a linha\"    - para ver todas as linhas");
    printf("\n\t comando: \"localizar\"              - para ver todas as linhas");
    printf("\n\t comando: \"inserir linha\"          - para inserir uma linha completa tem que ter um ficheiro como a informacao");
    printf("\n\t comando: \"sair\"                   - para terminar.");
    putchar('\n');
}