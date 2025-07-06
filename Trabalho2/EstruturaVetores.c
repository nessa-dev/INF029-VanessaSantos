#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

EstrutraAux *vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{

    int retorno = 0;
    // se posição é um valor válido {entre 1 e 10}
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    if (tamanho > 10)
        return SEM_ESPACO_DE_MEMORIA;
    // o tamanho nao pode ser menor que 1
    if (tamanho < 1)
        return TAMANHO_INVALIDO;
    // deu tudo certo, crie
    vetorPrincipal[posicao - 1] = malloc(sizeof(EstrutraAux));
    vetorPrincipal[posicao - 1]->tam = tamanho;
    vetorPrincipal[posicao - 1]->posUltimoValor = 0;
    vetorPrincipal[posicao - 1]->array = malloc(sizeof(int) * tamanho);
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    // testar se existe a estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL)
    {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao - 1]->posUltimoValor == vetorPrincipal[posicao - 1]->tam)
    {
        return SEM_ESPACO;
    }

    vetorPrincipal[posicao - 1]->array[vetorPrincipal[posicao - 1]->posUltimoValor] = valor;
    vetorPrincipal[posicao - 1]->posUltimoValor++;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > 10)
    {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1] == NULL)
    {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao - 1]->posUltimoValor == 0)
    {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    vetorPrincipal[posicao - 1]->posUltimoValor--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int posicaoValor;
    int aux;
    int iCont;

    if (posicao < 1 || posicao > 10)
    {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1] == NULL)
    {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao - 1]->posUltimoValor == 0)
    {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    posicaoValor = buscarValorEmVetorAuxiliar(valor, *vetorPrincipal[posicao - 1]);

    if (posicaoValor == -1)
    {
        return NUMERO_INEXISTENTE;
    }

    aux = vetorPrincipal[posicao - 1]->array[posicaoValor];
    for (iCont = posicaoValor + 1; iCont <= vetorPrincipal[posicao - 1]->posUltimoValor; iCont++)
    {
        vetorPrincipal[posicao - 1]->array[iCont - 1] = vetorPrincipal[posicao - 1]->array[iCont];
    }

    vetorPrincipal[posicao - 1]->array[vetorPrincipal[posicao - 1]->posUltimoValor] = aux;
    vetorPrincipal[posicao - 1]->posUltimoValor--;

    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int iCont;

    if (posicao < 1 || posicao > 10)
    {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1] == NULL)
    {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (iCont = 0; iCont < vetorPrincipal[posicao - 1]->posUltimoValor; iCont++)
    {
        vetorAux[iCont] = vetorPrincipal[posicao - 1]->array[iCont];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno == SEM_ESTRUTURA_AUXILIAR || retorno == POSICAO_INVALIDA)
    {
        return retorno;
    }

    insertionSort(vetorAux, vetorPrincipal[posicao - 1]->posUltimoValor);

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int iCont, jCont, kCont;

    for (iCont = 1; iCont < TAM; iCont++)
    {
        if (vetorPrincipal[iCont] != NULL)
        {
            if (vetorPrincipal[iCont]->posUltimoValor != 0)
            {
                break;
            }
        }
    }

    if (iCont == TAM)
    {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    kCont = 0;
    for (iCont = 0; iCont < TAM; iCont++)
    {
        if (vetorPrincipal[iCont] != NULL)
        {
            for (jCont = 0; jCont < vetorPrincipal[iCont]->posUltimoValor; jCont++)
            {
                vetorAux[kCont] = vetorPrincipal[iCont]->array[jCont];
                kCont++;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int iCont, tamTotal;
    int retorno;

    retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS)
    {
        return retorno;
    }

    tamTotal = getQtdNumerosTotais();

    insertionSort(vetorAux, tamTotal);
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int novoTamanhoTotal = vetorPrincipal[posicao - 1]->tam + novoTamanho;

    if (novoTamanhoTotal <= 0) {
        return NOVO_TAMANHO_INVALIDO;
    }

    if (vetorPrincipal[posicao - 1]->posUltimoValor > novoTamanhoTotal) {
        vetorPrincipal[posicao - 1]->posUltimoValor = novoTamanhoTotal;
    }

    vetorPrincipal[posicao - 1]->tam = novoTamanhoTotal;

    int *novoArray = realloc(vetorPrincipal[posicao - 1]->array, novoTamanhoTotal * sizeof(int));

    if (novoArray == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao - 1]->array = novoArray;

    return SUCESSO;
}


/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){

    if(posicao < 1 || posicao > 10){
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao - 1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(vetorPrincipal[posicao - 1]->posUltimoValor == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    return vetorPrincipal[posicao - 1]->posUltimoValor;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int iCont, tamTotal;

    tamTotal = getQtdNumerosTotais();
    if(tamTotal == 0){
        return NULL;
    }

    No *cabecote = malloc(sizeof(No));
    No *aux = malloc(sizeof(No));
    cabecote->prox = aux;

    int *vetAux = malloc(sizeof(int) * tamTotal);
    getDadosDeTodasEstruturasAuxiliares(vetAux);

    for(iCont = 0;iCont < tamTotal; iCont ++){
        aux->conteudo = vetAux[iCont];
        if(iCont == tamTotal - 1){
            aux->prox == NULL;
        }
        else{
            No *proximoConteudo = malloc(sizeof(No));
            aux->prox = proximoConteudo;
            aux = proximoConteudo;
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if(inicio  == NULL){
        return;
    }

    No *aux = inicio->prox;
    int iCont = 0;

    while(aux != NULL){
        vetorAux[iCont] = aux->conteudo;
        aux = aux->prox;
        iCont++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    free(*inicio);
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar()
{
    int iCont;

    for (iCont = 0; iCont < 10; iCont++)
    {
        vetorPrincipal[iCont] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
    int iCont;

    for(iCont = 0; iCont < TAM; iCont++){
        if(vetorPrincipal[iCont] != NULL){
            free(vetorPrincipal[iCont]);
            vetorPrincipal[iCont] = NULL;
        }
    }
}

int buscarValorEmVetorAuxiliar(int valor, EstrutraAux estruturaAuxiliar)
{
    int iCont;

    for (iCont = 0; iCont < estruturaAuxiliar.posUltimoValor; iCont++)
    {
        if (estruturaAuxiliar.array[iCont] == valor)
        {
            return iCont;
        }
    }

    return -1;
}

void insertionSort(int array[], int size)
{
    int iCont, jCont, key;

    for (iCont = 1; iCont < size; iCont++)
    {
        key = array[iCont];
        jCont = iCont - 1;

        while (jCont >= 0 && array[jCont] > key)
        {
            array[jCont + 1] = array[jCont];
            jCont--;
        }

        array[jCont + 1] = key;
    }
}

int getQtdNumerosTotais(){
    int iCont, tamTotal = 0;

    for (iCont = 0; iCont < TAM; iCont++)
    {
        if (vetorPrincipal[iCont] != NULL)
        {
            tamTotal += vetorPrincipal[iCont]->posUltimoValor;
        }
    }

    return tamTotal;
}   
