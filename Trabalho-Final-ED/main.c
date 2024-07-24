#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAMTOTAL 5964


//=-=-=-=-STRUCTS=-=-=-=-=
typedef struct{
    char cidade[50];
    int mes;
    int homicidio_doloso;
    int total_vitimas_homicidio_doloso;
    int latrocinio;
    int furto;
    int abigeato;
    int furto_veiculo;
    int roubo;
    int roubo_veiculo;
    int estelionato;
    int delito_relacionado_arma_municao;
    int entorpecente_posse;
    int entorpecente_trafico;
    int vitima_latrocinio;
    int vitima_lesao_corp_seg_morte;
    int total_vitimas_cvli;
}Dados;


typedef struct no{
	Dados *dado;
	struct no *proximo;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int totComparacoes = 0;

//=-=-=-=-=-=-=PRINTF=-=-=-=-=-=-=-=-=-=

void converteMes(int mes) {

    switch (mes) {
        case 1:
            printf("\nMes: Janeiro");
            break;
        case 2:
            printf("\nMes: Fevereiro");
            break;
        case 3:
            printf("\nMes: Marco");
            break;
        case 4:
            printf("\nMes: Abril");
            break;
        case 5:
            printf("\nMes: Maio");
            break;
        case 6:
            printf("\nMes: Junho");
            break;
        case 7:
            printf("\nMes: Julho");
            break;
        case 8:
            printf("\nMes: Agosto");
            break;
        case 9:
            printf("\nMes: Setembro");
            break;
        case 10:
            printf("\nMes: Outubro");
            break;
        case 11:
            printf("\nMes: Novembro");
            break;
        case 12:
            printf("\nMes: Dezembro");
            break;
    }
}


void printaDados(Dados *d) {

    printf("\nMunicipio: %s", d->cidade);
    converteMes(d->mes);
    printf("\nHomicidio doloso: %d", d->homicidio_doloso);
    printf("\nTotal de vitimas de homicidio doloso: %d", d->total_vitimas_homicidio_doloso);
    printf("\nLatrocinio: %d", d->latrocinio);
    printf("\nFurto: %d", d->furto);
    printf("\nAbigeato: %d", d->abigeato);
    printf("\nFurto de veiculo: %d", d->furto_veiculo);
    printf("\nRoubo: %d", d->roubo);
    printf("\nRoubo de veiculo: %d", d->roubo_veiculo);
    printf("\nEstelionato: %d", d->estelionato);
    printf("\nDelito relacionado a arma e municao: %d", d->delito_relacionado_arma_municao);
    printf("\nPosse de entorpecentes: %d", d->entorpecente_posse);
    printf("\nTrafico de entorpecentes: %d", d->entorpecente_trafico);
    printf("\nVitimas de latrocinio: %d", d->vitima_latrocinio);
    printf("\nVitimas de lesao corporal seguido de morte: %d", d->vitima_lesao_corp_seg_morte);
    printf("\nTotal de vitimas CVLI: %d", d->total_vitimas_cvli);

}


void printaVetor() {
    printf("\n=-=-=-=-=-=ARRAY BSEARCH=-=-=-=-=-=");
    printf("\nTamanho do array: %d", TAMTOTAL);
    printf("\nQtd de bytes do array: %llu bytes", sizeof(Dados)*TAMTOTAL);
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

void printaTabela() {
	size_t tamanho = (sizeof(No) * TAMTOTAL)+(sizeof(Lista) * TAMTOTAL);
    printf("\n=-=-=-=-=-=TABELA HASH=-=-=-=-=-=");
    printf("\nTamanho da tabela: %d", TAMTOTAL);
    printf("\nQtd de bytes da tabela: %llu bytes", tamanho);
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//=-=-=-=-=-=-=CHAVES HASH=-=-=-=-=-=-=-=-=-=

int funcaoHash(char *str, int mes)
{
    int i, valor=7;
    int tam = strlen(str);
    for(i=0; i<tam; i++)
        valor = 31*valor+(int)str[i];

    valor = valor*mes;

    return (valor&0X7FFFFFFF)%TAMTOTAL;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//=-=-=-=-=-=-=HASH=-=-=-=-=-=-=-=-=-=

Lista tabela[TAMTOTAL];


void iniciaLista(Lista *l){
    l->inicio = NULL;
    l->tam = 0;
}

void iniciaTabela(Lista t[]){
    int i;
    for(i = 0; i < TAMTOTAL; i++)
        iniciaLista(&t[i]);
}


void inserir_na_lista(Lista *l, Dados *d){
    No *novo = malloc(sizeof(No));

	if(novo == NULL){
		perror("\nErro");
		exit(1);
	}

    novo->dado = d;
    novo->proximo = l->inicio;
    l->inicio = novo;
    l->tam++;

}

void inserir(Lista t[], Dados *d){
    int id = funcaoHash(d->cidade, d->mes);
    inserir_na_lista(&t[id], d);
}


No* buscar_na_lista(Lista *l, Dados *d){

    No *aux = l->inicio;
    while(aux != NULL && (strcmp(aux->dado->cidade, d->cidade) != 0 && aux->dado->mes != d->mes)){
    	aux = aux->proximo;
        totComparacoes++;
	}

    if(aux == NULL){
    	return NULL;
	}
    totComparacoes++;
	return aux;
}

void busca(Lista t[], Dados *d){

    int id = funcaoHash(d->cidade, d->mes);

    No *retorno = buscar_na_lista(&t[id], d);

    if(retorno != NULL){
        printaDados(retorno->dado);
    	printf("\n");
    	printf("\nTotal de comparacoes: %d", totComparacoes);
	}
	else
		printf("\nValor nao encontrado");
}

void buscaGeral(Lista t[], Dados *d){

    int id = funcaoHash(d->cidade, d->mes);

    No *retorno = buscar_na_lista(&t[id], d);
}

void liberaHash(Lista t[]){

	for (int i = 0; i < TAMTOTAL; i++) {

	    No *atual = t[i].inicio;

	    while (atual != NULL) {
	        No *temp = atual;
	        atual = atual->proximo;
	        free(temp->dado);
	        free(temp);
	    }
	}

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//=-=-=-=-=-=-=DADOS=-=-=-=-=-=-=-=-=-=

Dados* database = NULL;

int comparacao(const void *obj1, const void *obj2) {

    int resp;
    resp = strcmp (((Dados*)obj1)->cidade, ((Dados*)obj2)->cidade);
    if(resp == 0){
        int pri = ((Dados*)obj1)->mes;
        int seg = ((Dados*)obj2)->mes;
        totComparacoes++;
        return (pri-seg);
    }
    else{
        totComparacoes++;
        return resp;
    }
}

void iniciaVetor(){
	database = (Dados*)malloc(sizeof(Dados)*TAMTOTAL);

    if(database == NULL){
        printf("Erro na alocacao");
        exit(1);
    }
}

void salvaDadosStruct() {

    char nome_city[50];
    int i = 0;

    Dados dados;

    FILE *fp = fopen("dados.csv", "r");

    if (fp == NULL) {
        perror("\nerro");
    }

    while (fscanf(fp, " %[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
          nome_city,
          &dados.mes,
          &dados.homicidio_doloso,
          &dados.total_vitimas_homicidio_doloso,
          &dados.latrocinio,
          &dados.furto,
          &dados.abigeato,
          &dados.furto_veiculo,
          &dados.roubo,
          &dados.roubo_veiculo,
          &dados.estelionato,
          &dados.delito_relacionado_arma_municao,
          &dados.entorpecente_posse,
          &dados.entorpecente_trafico,
          &dados.vitima_latrocinio,
          &dados.vitima_lesao_corp_seg_morte,
          &dados.total_vitimas_cvli) != EOF) {

        strcpy(dados.cidade, nome_city);

        //para array Bsort
        database[i] = dados;

        //tabela hash
        Dados *dHash = (Dados *)malloc(sizeof(Dados));

        strcpy(dHash->cidade, nome_city);
        dHash->mes = dados.mes;
        dHash->homicidio_doloso = dados.homicidio_doloso;
        dHash->total_vitimas_homicidio_doloso = dados.total_vitimas_homicidio_doloso;
        dHash->latrocinio = dados.latrocinio;
        dHash->furto = dados.furto;
        dHash->abigeato = dados.abigeato;
        dHash->furto_veiculo = dados.furto_veiculo;
        dHash->roubo = dados.roubo;
        dHash->roubo_veiculo = dados.roubo_veiculo;
        dHash->estelionato = dados.estelionato;
        dHash->delito_relacionado_arma_municao = dados.delito_relacionado_arma_municao;
        dHash->entorpecente_posse = dados.entorpecente_posse;
        dHash->entorpecente_trafico = dados.entorpecente_trafico;
        dHash->vitima_latrocinio = dados.vitima_latrocinio;
        dHash->vitima_lesao_corp_seg_morte = dados.vitima_lesao_corp_seg_morte;
        dHash->total_vitimas_cvli = dados.total_vitimas_cvli;

        inserir(tabela, dHash);

        i++; // Incrementa o contador de linhas lidas

        if (i >= TAMTOTAL) {
            break;
        }
    }

    fclose(fp);
    qsort(database, TAMTOTAL, sizeof(Dados), comparacao);
}

void liberaVetor() {
    free(database);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//=-=-=-=-=-=-=PESQUISAS=-=-=-=-=-=-=-=-=-=

void capturaDadosUsuarioBSearch() {

    fflush(stdin);

    totComparacoes = 0;
    Dados *pesquisaUsuario = (Dados*)malloc(sizeof(Dados));

    printf("\nInforme a cidade: ");
    gets(pesquisaUsuario->cidade);

    printf("\nInforme o mes: ");
    scanf("%d", &pesquisaUsuario->mes);

    strupr(pesquisaUsuario->cidade);

    Dados *resultBSearch = (Dados*)malloc(sizeof(Dados));
    resultBSearch = bsearch(pesquisaUsuario, database, TAMTOTAL, sizeof(Dados), comparacao);

    if(resultBSearch != NULL)
        printaDados(resultBSearch);
    else
        printf("\nCidade nao encontrada!");

    printf("\n");
    printf("\nTotal de comparacoes: %d", totComparacoes);
}

void pesquisaTodosBSearch() {

    int i;
    int maiorComparacao=0, posMaiorComp=0;
    totComparacoes = 0;

    Dados *dadosPesquisa = (Dados*)malloc(sizeof(Dados));

    for(i=0; i<TAMTOTAL; i++) {

        dadosPesquisa = &database[i];

        bsearch(dadosPesquisa, database, TAMTOTAL, sizeof(Dados), comparacao);

        printf("\n=-=-=-=-=-=-=-=-=-=-=");
        printf("\nMunicipio: %s | Mes: %d | Total de comparacoes: %d", dadosPesquisa->cidade, dadosPesquisa->mes, totComparacoes);
        printf("\n=-=-=-=-=-=-=-=-=-=-=");

        if(maiorComparacao < totComparacoes) {
            maiorComparacao = totComparacoes;
            posMaiorComp = i;
        }
        totComparacoes = 0;
    }

    printf("\n=-=-=-=-=-MAIOR COMPARACAO=-=-=-=-=-=");
    printf("\nMunicipio: %s | Mes: %d | Total de comparacoes: %d", database[posMaiorComp].cidade, database[posMaiorComp].mes, maiorComparacao);
    printf("\n=-=-=-=-=-=-=-=-=-=-=");
}

void pesquisaTodosTabelaHash() {

    int i;
    int maiorComparacao=0, posMaiorComp=0;
    totComparacoes = 0;

    Dados *dadosPesquisa = (Dados*)malloc(sizeof(Dados));

    for(i=0; i<TAMTOTAL; i++) {

        dadosPesquisa = &database[i];

        buscaGeral(tabela, dadosPesquisa);

        printf("\n=-=-=-=-=-=-=-=-=-=-=");
        printf("\nMunicipio: %s | Mes: %d | Total de comparacoes: %d", dadosPesquisa->cidade, dadosPesquisa->mes, totComparacoes);
        printf("\n=-=-=-=-=-=-=-=-=-=-=");

        if(maiorComparacao < totComparacoes) {
            maiorComparacao = totComparacoes;
            posMaiorComp = i;
        }
        totComparacoes = 0;
    }

    printf("\n=-=-=-=-=-MAIOR COMPARACAO=-=-=-=-=-=");
    printf("\nMunicipio: %s | Mes: %d | Total de comparacoes: %d", database[posMaiorComp].cidade, database[posMaiorComp].mes, maiorComparacao);
    printf("\n=-=-=-=-=-=-=-=-=-=-=");
}

void capturaDadosUsuarioHash() {

    fflush(stdin);
    Dados dPesquisa;

    printf("\nInforme o municipio: ");
    gets(dPesquisa.cidade);

    printf("\nInforme o mes: ");
    scanf("%d", &dPesquisa.mes);
    strupr(dPesquisa.cidade);
	busca(tabela, &dPesquisa);

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int menu(){

    int esc;
    printf("\n");
    printf("\n------ MENU ------");
    printf("\n0 - SAIR");
    printf("\n1 - BUSCA TUDO COM BSEARCH");
    printf("\n2 - BUSCA TUDO COM TABELA HASH");
    printf("\n3 - PROCURAR UM COM BSEARCH");
    printf("\n4 - PROCURAR UM COM TABELA HASH");
    printf("\n5 - DADOS DA MEMORIA");
    printf("\n: ");
    scanf("%d", &esc);
	return esc;
}


int main() {

	bool flag = true;

    iniciaVetor();
    iniciaTabela(tabela);

    salvaDadosStruct();

    while(flag != false){

		switch(menu()){
            case 0:
                printf("\nsaindo...");
                liberaVetor();
                liberaHash(tabela);
                system("\npause");
                flag = false;
                break;

            case 1:
                pesquisaTodosBSearch();
                break;

            case 2:
                pesquisaTodosTabelaHash();
                break;

            case 3:
                capturaDadosUsuarioBSearch();
                break;

            case 4:
				capturaDadosUsuarioHash();
                break;

            case 5:
                printaVetor();
                printf("\n");
                printaTabela();
                break;
        }
	}

    return 0;
}

