#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "EstruturaVetores.h" 


#define TAM 10
typedef struct {
    int *elementos;
    int quantidade_ocupada;
    int tamanho_alocado;
} EstruturaAuxiliar;


EstruturaAuxiliar *vetorPrincipal[TAM];

static int comparar(const void *a, const void *b);
static int getQtdNumerosTotais(); // Não recebe parâmetro, pois acessa o global vetorPrincipal

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa
*/
void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->elementos); // Libera o array de inteiros
            free(vetorPrincipal[i]);           // Libera a própria EstruturaAuxiliar
            vetorPrincipal[i] = NULL;          // Define o ponteiro como NULL para evitar dangling pointer
        }
    }
}

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
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    // Validação de posição
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1; // Ajusta para índice base 0

    // Verifica se já existe uma estrutura auxiliar na posição
    if (vetorPrincipal[indice] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    // Validação de tamanho
    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    // Aloca memória para a estrutura auxiliar
    EstruturaAuxiliar *novaEstrutura = (EstruturaAuxiliar *) malloc(sizeof(EstruturaAuxiliar));
    if (novaEstrutura == NULL) {
        return SEM_ESPACO_DE_MEMORIA; // Erro na alocação da estrutura
    }

    // Aloca memória para o array de elementos dentro da estrutura
    novaEstrutura->elementos = (int *) malloc(tamanho * sizeof(int));
    if (novaEstrutura->elementos == NULL) {
        free(novaEstrutura); // Se a alocação dos elementos falhar, libera a própria estrutura
        return SEM_ESPACO_DE_MEMORIA; // Erro na alocação dos elementos
    }

    // Inicializa os campos da nova estrutura
    novaEstrutura->quantidade_ocupada = 0;
    novaEstrutura->tamanho_alocado = tamanho;

    // Atribui a nova estrutura à posição no vetor principal
    vetorPrincipal[indice] = novaEstrutura;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    // Verifica se a estrutura auxiliar existe na posição
    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    // Verifica se há espaço disponível na estrutura auxiliar
    if (aux->quantidade_ocupada < aux->tamanho_alocado) {
        aux->elementos[aux->quantidade_ocupada] = valor; // Insere o valor
        aux->quantidade_ocupada++;                       // Incrementa a quantidade de elementos
        return SUCESSO;
    } else {
        return SEM_ESPACO; // Não há espaço
    }
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
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    // Verifica se a estrutura auxiliar existe
    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    // Verifica se a estrutura auxiliar está vazia
    if (aux->quantidade_ocupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    aux->quantidade_ocupada--; // Exclusão lógica: apenas decrementa a quantidade ocupada

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
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux->quantidade_ocupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    int i;
    int encontrado_idx = -1; // Usar -1 para indicar que não foi encontrado
    for (i = 0; i < aux->quantidade_ocupada; i++) {
        if (aux->elementos[i] == valor) {
            encontrado_idx = i; // Armazena o índice do valor encontrado
            break;
        }
    }

    if (encontrado_idx == -1) { // Se o valor não foi encontrado
        return NUMERO_INEXISTENTE;
    }

    // Desloca os elementos para a esquerda, sobrescrevendo o elemento excluído
    for (int j = encontrado_idx; j < aux->quantidade_ocupada - 1; j++) {
        aux->elementos[j] = aux->elementos[j+1];
    }

    aux->quantidade_ocupada--; // Decrementa a contagem de elementos

    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];
    // Copia os elementos para o vetor auxiliar fornecido
    for (int i = 0; i < aux->quantidade_ocupada; i++) {
        vetorAux[i] = aux->elementos[i];
    }

    return SUCESSO;
}

// Função de comparação para qsort (static para ser interna ao .c)
static int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;
    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];
    if (aux->quantidade_ocupada == 0) {
        // Retorna SUCESSO para uma estrutura vazia, pois "ordenar" 0 elementos é trivial.
        // Se o professor espera ESTRUTURA_AUXILIAR_VAZIA para esse caso, altere aqui.
        return ESTRUTURA_AUXILIAR_VAZIA; // Mudado para ESTRUTURA_AUXILIAR_VAZIA para ser mais explícito
    }

    // Copia os dados para o vetor auxiliar antes de ordenar
    memcpy(vetorAux, aux->elementos, aux->quantidade_ocupada * sizeof(int));
    qsort(vetorAux, aux->quantidade_ocupada, sizeof(int), comparar); // Ordena usando qsort

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0; // Índice para o vetorAux
    int algumaNaoVazia = 0; // Flag para verificar se alguma estrutura tem dados

    for (int i = 0; i < TAM; i++) {
        EstruturaAuxiliar *aux = vetorPrincipal[i];
        if (aux != NULL && aux->quantidade_ocupada > 0) {
            algumaNaoVazia = 1; // Encontrou dados
            for (int j = 0; j < aux->quantidade_ocupada; j++) {
                vetorAux[k++] = aux->elementos[j]; // Copia o elemento
            }
        }
    }

    // Retorna SUCESSO se houver dados, TODAS_ESTRUTURAS_AUXILIARES_VAZIAS caso contrário
    return algumaNaoVazia ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

// Função auxiliar para obter a quantidade total de números em todas as estruturas
static int getQtdNumerosTotais(){
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            total += vetorPrincipal[i]->quantidade_ocupada;
        }
    }
    return total;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int resultado = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (resultado == SUCESSO) {
        int total = getQtdNumerosTotais(); // Obtém a quantidade total de elementos
        qsort(vetorAux, total, sizeof(int), comparar); // Ordena todos os elementos
    }

    return resultado;
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
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;
    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int novoTamTotal = aux->tamanho_alocado + novoTamanho;

    if (novoTamTotal < 1) { // Verifica se o novo tamanho total é válido
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoArray = (int *) realloc(aux->elementos, novoTamTotal * sizeof(int));
    if (novoArray == NULL) {
        return SEM_ESPACO_DE_MEMORIA; // Erro na realocação de memória
    }

    aux->elementos = novoArray;       // Atualiza o ponteiro para o novo array
    aux->tamanho_alocado = novoTamTotal; // Atualiza o tamanho alocado

    // Se a quantidade de elementos ocupados excede o novo tamanho, ajusta
    if (aux->quantidade_ocupada > novoTamTotal) {
        aux->quantidade_ocupada = novoTamTotal;
    }

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
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;
    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (aux->quantidade_ocupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    return aux->quantidade_ocupada; // Retorna a quantidade de elementos ocupados
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
    No *cabecote = (No *) malloc(sizeof(No));
    if (cabecote == NULL) { // Verifica se a alocação do cabeçote falhou
        return NULL;
    }

    cabecote->prox = NULL;
    No *atual = cabecote; // Ponteiro para o último nó na lista (inicia no cabeçote)
    int temElementos = 0; // Flag para verificar se há algum elemento nas estruturas

    for (int i = 0; i < TAM; i++) {
        EstruturaAuxiliar *estrutura = vetorPrincipal[i];
        if (estrutura != NULL && estrutura->quantidade_ocupada > 0) {
            temElementos = 1; // Indica que há elementos em alguma estrutura
            for (int j = 0; j < estrutura->quantidade_ocupada; j++) {
                No *novoNo = (No *) malloc(sizeof(No));
                if (novoNo == NULL) { // Se a alocação de um novo nó falhar
                    // Libera todos os nós já criados na lista (incluindo o cabeçote)
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                novoNo->conteudo = estrutura->elementos[j];
                novoNo->prox = NULL;
                atual->prox = novoNo; // Conecta o novo nó ao final da lista
                atual = novoNo;       // Atualiza 'atual' para o novo nó
            }
        }
    }

    if (!temElementos) { // Se nenhuma estrutura auxiliar tinha elementos
        free(cabecote);   // Libera o cabeçote que foi alocado
        return NULL;      // Retorna NULL
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) { // Se o início da lista for NULL, não há o que fazer
        return;
    }

    No *atual = inicio->prox; // Começa do primeiro nó de dados (depois do cabeçote)
    int i = 0;
    while (atual != NULL) {
        vetorAux[i++] = atual->conteudo; // Copia o conteúdo
        atual = atual->prox;           // Move para o próximo nó
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
    No *atual = *inicio; // Começa do cabeçote
    while (atual != NULL) {
        No *prox = atual->prox; // Armazena o próximo nó antes de liberar o atual
        free(atual);            // Libera a memória do nó atual
        atual = prox;           // Move para o próximo nó
    }
    *inicio = NULL; // Define o ponteiro de início para NULL
}
