#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct funcionario
{
int matricula;
char nome[128];
int idade;
char sexo;
}funcionario;

typedef struct lista {
funcionario info;
	struct lista* prox;
} Lista;

void LimparBuffer()
{
	while (getchar() != '\n');
}

void Pause()
{
	printf("\nTecle <ENTER> para continuar...");
	getchar();
}

Lista* InicializarLista()
{
	return NULL;
}

int VerificarListaVazia(Lista*pLista)
{
	return (pLista == NULL);
}

void LiberarLista(Lista* pLista){
	Lista* noRemovido = pLista;
	while (noRemovido != NULL) {
	/* guarda referência para o próximo elemento*/
Lista* noAux = noRemovido->prox;
	free(noRemovido); /* libera a memória apontada por noRemovido
	*/
	noRemovido = noAux; /* faz noRemovido apontar para o próximo */
	}
}

Lista* BuscarElementoPorMatricula(Lista* pLista, int idMatricula)
{
	Lista* noProcurado;
	for (noProcurado = pLista; noProcurado != NULL; noProcurado = noProcurado->prox)
	if (noProcurado->info.matricula == idMatricula)
		return noProcurado;

	return NULL;
}

Lista* BuscarPorNomeOuMatricula(Lista* pLista, int idMatricula, char *nome)
{
	Lista* noProcurado;
	for (noProcurado = pLista; noProcurado != NULL; noProcurado = noProcurado->prox)
	{
		if (noProcurado->info.matricula == idMatricula || !strcmp(noProcurado->info.nome, nome))
			return noProcurado;
	}

	return NULL;
}

void ImprimirFuncionario(funcionario funcionario)
{
	printf("\n");
	printf("\nMatricula...: %d", funcionario.matricula);
	printf("\nNome........: %s", funcionario.nome);
	printf("\nIdade.......: %d", funcionario.idade);
	printf("\nSexo........: %c", funcionario.sexo);
	printf("\n");
}

void ImprimirLista(Lista* pLista)
{
	Lista* noTemp;
	if (pLista)
	{
		for (noTemp = pLista; noTemp != NULL; noTemp = noTemp->prox)
			ImprimirFuncionario(noTemp->info);
	}
	else
		printf("\nLISTA VAZIA...\n");
}

void Consultar(Lista *pLista, int matricula, char *nome)
{
	Lista *pFuncionarioPesquisado = BuscarPorNomeOuMatricula(pLista, matricula, nome);

	if (!pFuncionarioPesquisado)
		printf("\nO FUNCIONARIO CONSULTADO NAO FOI ENCONTRADO... \n");
	else
		ImprimirFuncionario(pFuncionarioPesquisado->info);
}

Lista* Inserir(Lista* pLista, funcionario info)
{
	Lista *pTemMatricula = BuscarElementoPorMatricula(pLista, info.matricula);

	if (pTemMatricula)
		return pLista;
	else
	{
		Lista* novoElemento = (Lista*)malloc(sizeof(Lista));
		novoElemento->info = info;
		novoElemento->prox = pLista;

		return novoElemento;
	}
}

Lista* Retirar(Lista* pLista, int matricula)
{
	Lista* noAnterior = NULL;
	Lista* noRemovido = pLista;

	while (noRemovido != NULL && noRemovido->info.matricula != matricula)
	{
		noAnterior = noRemovido;
		noRemovido = noRemovido->prox;
	}

	/* verifica se achou elemento */
	if (noRemovido == NULL)
		return pLista; /* não achou: retorna Lista original */

	/* retira elemento */

	if (noAnterior == NULL) {
		/* retira elemento do inicio */
		pLista = noRemovido->prox;
	}
	else {
		/* retira elemento do meio da LISTA */
		noAnterior->prox = noRemovido->prox;
	}

	free(noRemovido);
	return pLista;
}

int Atualizar(Lista* pLista, int matricula, funcionario info)
{
	Lista *pfuncionarioAtualizar = BuscarElementoPorMatricula(pLista, matricula);

	// VERFICA SE EXISTE FUNCIONARIO CADASTRADO
	if (!pfuncionarioAtualizar)
		return 0;
	else
	{
		pfuncionarioAtualizar->info = info;

		return info.matricula;
	}
}