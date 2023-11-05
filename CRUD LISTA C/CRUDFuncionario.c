#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionario.h"

void LimparTela() {
    system("cls");
}

char *NovaStr(char texto[], int vezes) {
    int i = 0;
    char *novoTexto = (char *)malloc(sizeof(char) * 128);
    strcpy(novoTexto, "");

    for (i = 0; i < vezes; i++)
        strcat(novoTexto, texto);

    return novoTexto;
}

void ImprmirTitulo(char titulo[]) {
    LimparTela();
    int vezes = 40 - 6 - strlen(titulo);
    printf("****************************************\n");
    printf("***%s%s%s***\n", NovaStr(" ", vezes / 2), titulo, NovaStr(" ", vezes - (vezes / 2)));
    printf("****************************************\n");
    }

void LeiaMatricula(int *matricula) {
    printf("\nDigite a matricula: ");
    scanf("%d", matricula);
    while (getchar() != '\n');
}

void LeiaNome(char nome[128]) {  // Alteração no parâmetro
    printf("\nDigite o nome do funcionario: ");
    scanf(" %127[^\n]", nome);  // Evitar estouro de buffer
    while (getchar() != '\n');
}

void LeiaFuncionario(funcionario *funcionario) {
    LeiaMatricula(&funcionario->matricula);
    LeiaNome(funcionario->nome);  // Passar o nome como um array, não um ponteiro

    printf("\nDigite a idade: ");
    scanf("%d", &funcionario->idade);
    while (getchar() != '\n');

    printf("\nSexo (M ou F)..: ");
    scanf(" %c", &funcionario->sexo);
    while (getchar() != '\n');
}

void Menu() {
    LimparTela();
    printf("****************************************\n");
    printf("***                MENU              ***\n");
    printf("****************************************\n");
    printf("* [1] - INSERIR                     *\n");
    printf("* [2] - ALTERAR                     *\n");
    printf("* [3] - EXCLUIR                     *\n");
    printf("* [4] - CONSULTAR                   *\n");
    printf("* [5] - LISTAR                      *\n");
    printf("* [6] - SAIR                        *\n");
    printf("****************************************\n");

    printf("\n\n OPCAO: ");
}

Lista *MantemInserir(Lista *pLista) {
    funcionario funcionario;
    int existeFuncionario;

    ImprmirTitulo("[1]. INSERIR FUNCIONARIO");
    LeiaFuncionario(&funcionario);
    existeFuncionario = BuscarElementoPorMatricula(pLista, funcionario.matricula);

    if (existeFuncionario) {
        printf("\nJA EXISTE UM FUNCIONARIO CADASTRADO COM A MATRICULA %d \n", funcionario.matricula);
        system("pause");
    } else
        pLista = Inserir(pLista, funcionario);

    return pLista;
}

Lista *MantemAlterar(Lista *pLista) {
    ImprmirTitulo("[2]. ALTERAR FUNCIONARIO");
    int matricula = 0;
    LeiaMatricula(&matricula);
    int existeMatricula = BuscarElementoPorMatricula(pLista, matricula);

    if (existeMatricula) {
        ImprmirTitulo("[2]. ALTERAR FUNCIONARIO");
        printf("\nENTRE COM OS DADOS DO FUNCIONARIO ATUALIZADOS \n");
        funcionario funcionario;
        LeiaFuncionario(&funcionario);
        Atualizar(pLista, matricula, funcionario);
    } else {
        printf("\n FUNCIONARIO NAO ENCONTRADO...\n");
        system("pause");
    }

    return pLista;
}

Lista *MantemExcluir(Lista *pLista) {
    ImprmirTitulo("[3]. EXCLUIR FUNCIONARIO");
    int matricula = 0;
    LeiaMatricula(&matricula);
    int existeMatricula = BuscarElementoPorMatricula(pLista, matricula);

    if (existeMatricula) {
        pLista = Retirar(pLista, matricula);
        printf("\n FUNCIONARIO REMOVIDO COM SUCESSO...\n");
        system("pause");
    } else {
        printf("\n FUNCIONARIO NAO ENCONTRADO...\n");
        system("pause");
    }

    return pLista;
}

void MantemConsultar(Lista *pLista) {
    ImprmirTitulo("[4]. CONSULTAR ");
    int matricula = 0, opcao = 0;
    char nome[128] = "";

    do {
        printf("\n CONSULTAR FUNCIONARIO POR: ");
        printf("\n [1]. MATRICULA");
        printf("\n [2]. NOME ");
        printf("\n\n OPCAO: ");
        scanf(" %d", &opcao);

        if (opcao == 2)
            LeiaNome(nome);
        else if (opcao == 1)
            LeiaMatricula(&matricula);
    } while (opcao != 1 && opcao != 2);

    Consultar(pLista, matricula, nome);
    system("pause");
}

void MantemListaFuncionarios(Lista *pLista) {
    ImprmirTitulo("[5]. LISTA DE FUNCIONARIOS");
    ImprimirLista(pLista);
    system("pause");
}

int main() {
    Lista *pLista;
    int opcao = 0;
    pLista = InicializarLista();

    do {
        Menu();
        scanf("%d", &opcao);
        while (getchar() != '\n');  // Limpar o buffer do teclado
        LimparTela();
        if (opcao == 1)
            pLista = MantemInserir(pLista);
        else if (opcao == 2)
            pLista = MantemAlterar(pLista);
        else if (opcao == 3)
            pLista = MantemExcluir(pLista);
        else if (opcao == 4)
            MantemConsultar(pLista);
        else if (opcao == 5)
            MantemListaFuncionarios(pLista);
    } while (opcao != 6);

    LiberarLista(pLista);
    return 0;
}