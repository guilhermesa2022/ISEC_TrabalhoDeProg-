#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tamCodigo 4
#define tamNome 30
//#include <math.h>
typedef struct dadolinha linhas, *Plinhas;
typedef struct paragenslinhas linhaparagem, *PLinhaParagem;

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

void localizar_paragem(paragem* Pgem, int numparagem, Plinhas p){
    int i, j;
    PLinhaParagem aux;
    char codigo[tamCodigo];

    printf("Escreva o codigo da paragem que ter procurar:");
    scanf("%s", codigo);
    printf("\nswswwsw");

    for(i=0; i < numparagem && strcmp(codigo, Pgem[i].codigo) != 0; i++)
        printf("\tppp");

    while(p != NULL){
        printf("\n\tentrei");
            aux = p->InicioParagem;
            while(aux != NULL){
                printf("\n\t\tque mundo");
                printf("\nEssa paragem existe na linha : %s", p->Nome);
                if(strcmp(aux->codigo, codigo) == 0){
                    printf("\nEssa paragem existe na linha : %s", p->Nome);
                    break;
                }
                aux = aux->Prox;
            }
        p = p->Prolinha;
    }
}

int main() {
    char cmd[29];
    paragem *PGEM = NULL;
    int tamPGEM = 0;
    Plinhas listalinhas = NULL;
    int escolha = 0;

    do{
        escrevecomandos();
        printf("\n\t\tcomando:");
        scanf(" %28[^\n]", &cmd);

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

                printf("\nClicar 1 Para Inserir No Inicio\tClicar 2 Para Inserir No Meio\tClicar 3 Para Inserir No Final: ");
                scanf("%i", &escolha);

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

        }else
            if(!strcmp(cmd, "localizar")){
                localizar_paragem(PGEM, tamPGEM, listalinhas);
        }else
            printf("\n\t\t\t--->comando nao existe\n");


    } while (strcmp(cmd, "sair") != 0);

    if(PGEM != NULL)
        free(PGEM);
    liberta_lista(listalinhas);
    return 0;
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

int verificaSeExiste(char nome[30], Plinhas p){
    printf("--------------------%s", nome);
    while (p != NULL){
        printf("\nvericocar 1");
        if(!strcmp(p->Nome, nome)){
            printf("\no nome da linha ja existe por favor;");
            return 1;
        }
        p = p->Prolinha;
    }
    printf("\nvericicar sair");
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
            printf("\nainda nao existe paragens");
        }else if(pos == 1){
            p->numDePagagens++;
            (Pgem[i].numLinhas)++;
            Pparagem->Prox = p->InicioParagem;
            p->InicioParagem->ant = Pparagem;
            p->InicioParagem = Pparagem;
            printf("\nainda ja existe paragens");
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
        printf("\nentrei no primero if");
        aux = aux->Prolinha;
        free(p);
        p = aux;
    }else{
        while (aux != NULL && strcmp(nome, aux->Prolinha->Nome) !=0){
            aux = aux->Prolinha;
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
        printf("\nNome da linha: %s", p->Nome);
        aux = p->InicioParagem;
        while (aux != NULL){
            printf("\n\t-->nome: %s //codigo: %s ", aux->nome, aux->codigo);
            printf("\n\t-->ant: %p //depois: %p // numparagem = %i ", aux->ant, aux->Prox, p->numDePagagens); //teste;;
            aux = aux->Prox;
        }
        p = p->Prolinha;
    }
}

void escrevecomandos(){
    printf("\n\t comando: \"adicionar paragem\"         - para adicionar uma paragem.");
    printf("\n\t comando: \"eliminar paragem\"          - para apagar uma paragem.");
    printf("\n\t comando: \"ver paragens\"              - para ver todas as paragens.");
    printf("\n\t comando: \"adicionar linha\"           - para adicionar uma linha");
    printf("\n\t comando: \"eliminar linha\"            - para apagar uma linha");
    printf("\n\t comando: \"ver linhas\"                - para ver todas as linhas");
    printf("\n\t comando: \"adicionar no a linha\"      - para ver todas as linhas");
    printf("\n\t comando: \"eliminar no a linha\"       - para ver todas as linhas");
    printf("\n\t comando: \"localizar\"                 - para ver todas as linhas");
    printf("\n\t comando: \"sair\"                      - para terminar.");
    putchar('\n');
}