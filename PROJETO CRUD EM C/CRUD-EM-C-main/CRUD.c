#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>

typedef struct Produto{
	char nome[15],descricao[30],uniMedida[10];
	int id, qtds;
}Produto;


Produto p;

 
void inclusao();
void alteracao();
void consulta();
void exclusao();


int idProduto(int idBuscar){

	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int test;

	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		
		if(idBuscar==p.id){
				return 1;
			}
		}
		fclose(arquivoProduto);
		return 0;
}


void inclusao(){
	
	char op;
	Produto p;
	int id, test=0;
	do{
		system("cls");
		printf("codigo do tenis:");
		scanf("%d",&id);
		setbuf(stdin, NULL);
		test=idProduto(id);
		if(test==1){
			printf("\n\ttenis ja cadastrado\n\n");
			system("pause");
		}
	}while(test==1);
	p.id=id;
	
	printf("Quantidade de tenis: ");
	scanf("%d",&p.qtds);
	setbuf(stdin, NULL);
	
	printf("Nome do tenis:");
	fgets(p.nome,15,stdin);
	setbuf(stdin, NULL);
	
	
	
	FILE* arquivoProduto;
	
	arquivoProduto = fopen("./ex.dat","ab");
	
	if(arquivoProduto == NULL){
		printf("erro\n");
		exit(1);
	}
	
	fwrite(&p, sizeof(Produto), 1, arquivoProduto);
	
	fclose(arquivoProduto);
	printf("pressione enter");
	getchar();
	system("cls");
}

void consultaTodos(){
	
	system("cls");
	
	FILE* arquivoProduto = fopen("./ex.dat","rb"); 
	
	if(arquivoProduto==NULL){
		printf("\nNao ha nenhum produto cadastrado!\n");
	}
	
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		printf("\n");
				printf("\nO codigo do produto:%d",p.id);
				printf("\nQuatidade de tenis:%d",p.qtds);
				printf("\nNome do tenis:%s",p.nome);
				printf("\n");
				printf("\n");
	}
	system("pause");
	fclose(arquivoProduto);
	printf("\n\n\nPressione qualquer tecla para voltar\n");
	getchar();
	system("cls");
}



void alteracao(){
	
	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int idBuscar;
	
	printf("Codigo do produto que deseja alterar: \n");
	scanf("%d",&idBuscar);
	setbuf(stdin, NULL);
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		if(idBuscar==p.id){
			encontrou = TRUE;
			break;
		}
	}
	
	setbuf(stdin, NULL);

	
	if(!encontrou){
		printf("nao encontrou\n");
		getchar();
		system("cls");
		return;
	}
	
	
	printf("Novos dados\n");
	
	printf("INFORME O CODIGO DO TENIS: ");
	scanf("%d",&p.id);
	setbuf(stdin, NULL);

	printf("INFORME A QUANTIDADE DE TENIS: ");
	scanf("%d",&p.qtds);
	setbuf(stdin, NULL);
	
	printf("INFORME O NOME DO TENIS");
	fgets(p.nome,15,stdin);
	setbuf(stdin, NULL);
	
	FILE* arqAux = fopen("./exAux.dat","ab");
	rewind(arquivoProduto);
	
	if(arquivoProduto == NULL || arqAux == NULL){
		printf("erro\n");
	}
	else{
		fwrite(&p,sizeof(Produto),1,arqAux);
		while(fread(&p,sizeof(Produto),1,arquivoProduto)){
			if(idBuscar!=p.id){
				fwrite(&p,sizeof(Produto),1,arqAux);
			}
		}
	}
	
	fclose(arquivoProduto);
	fclose(arqAux);
	
	remove("./ex.dat");
	rename("./exAux.dat","./ex.dat");
	
	printf("pressione enter");
	getchar();
	system("cls");
}

void excluir(){
	
	system("cls");
	
	Produto leituram;
	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int idBuscar;
	
	printf("Codigo do produto que deseja excluir: \n");
	scanf("%d",&idBuscar);
	setbuf(stdin, NULL);

	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		if(idBuscar==p.id){
			fclose(arquivoProduto);
				excluirProduto(leituram);
			}
		}
		fclose(arquivoProduto);
	
	printf("Codigo do produto incorreto!\n");
	system("pause");
	system("cls");

}

void excluirProduto(Produto antigo){
	system("cls");
	FILE *arquivoProduto, *aux; Produto passar;
	
	arquivoProduto = fopen("./ex.dat","rb");
	aux = fopen("./exAux.dat","wb");
	
	while(fread(&passar,sizeof(Produto),1,arquivoProduto)){
		if(antigo.id!=passar.id){
			fwrite(&passar,sizeof(Produto),1,aux);
		}
	}fclose(arquivoProduto);
	fclose(aux);
	
	arquivoProduto = fopen("./ex.dat","wb");
	aux = fopen("./exAux.dat","rb");
	
	while(fread(&passar,sizeof(Produto),1,arquivoProduto)){
		fwrite(&passar,sizeof(Produto),1,arquivoProduto);
	}
	
	fclose(arquivoProduto);
	fclose(aux);
	
	printf("Dados apagados com sucesso!");
	getch();
	system("cls");
	main();
}
int main(){
	system("cls");
	SetConsoleTitle("Controle de Estoque");
	
	int opcao;
		
	do{
		printf( " \t\t\t\t\t\t CRUD ESTOQUE DE TENIS \t\t\n");
		printf("[1] Cadastrar tenis:\n");
		printf("[2] Buscar todos os produtos\n");
		printf("[3] Alterar dados do produto por codigo:\n");
		printf("[4] Excluir dados do produto por codigo:\n");
		printf("[5] SAIR:\n");
		scanf("%d",&opcao);
		setbuf(stdin, NULL);
		
		system("cls");
		
		switch(opcao){
			
		case 1:
			system("cls");
			inclusao();
			break;
		case 2:
			system("cls");
			consultaTodos();
			break;
		case 3:
			system("cls");
			alteracao();
			break;	
		case 4:
			system("cls");
			excluir(idProduto);
			break;
		}
	}while(opcao != 5);
}
