#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAMTOTAL 5964

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



Dados* database = NULL;


void iniciaVetor()
{
	
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

    FILE *fp;
    
    fp = fopen("dados.csv", "r");
    
    if (fp == NULL) {
        printf("Erro na abertura do arquivo!");
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
        
        database[i] = dados;
        
        i++; // Incrementa o contador de linhas lidas
        
        if (i >= TAMTOTAL) {
            break; 
        }
    }

    fclose(fp);
}


void menu(){
	
	bool flag = true;
	int esc;
	
	while(flag != false){
		
		printf("\n--- MENU ---");
		printf("\n0 - SAIR");
		printf("\n1 - BUSCA TUDO COM BSEARCH");
		printf("\n2 - BUSCA TUDO COM TABELA HASH");
		printf("\n3 - PROCURAR UM COM BSEARCH");
		printf("\n4 - PROCURAR UM COM TABELA HASH");
		printf("\n5 - DADOS DA MEMORIA");
		printf("\n: ");
		scanf("%d", &esc);
		
		switch(esc){
			
			case 0:
				printf("\nsaindo...");
				system("\npause");
				exit(1);
			
			case 1:
				printf("\n1° escolha");
				break;
		}
	}
	
}

int main(int argc, char *argv[]) {
	
	int i;
 	
 	iniciaVetor();
    salvaDadosStruct();
    
    menu();
    
    for(i=0; i<TAMTOTAL; i++)
    {
    	printf("\nCidade: %s | Mes: %d | Homicidio Doloso: %d", database[i].cidade, database[i].mes, database[i].homicidio_doloso);
    	if(i%10==9){
    		system("pause");
		}
	}
    
    return 0;
}
