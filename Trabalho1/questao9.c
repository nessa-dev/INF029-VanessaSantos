#include <stdio.h>   
#include <string.h>  
#include <ctype.h>   

// --- Constantes do Jogo ---
#define TAMANHO_TABULEIRO 3 

void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
int obterEValidarJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorAtual, char *linha_ptr, char *coluna_ptr);
void fazerJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char linha_char, char coluna_char, char marca);
int verificarVitoria(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char marca);
int verificarEmpate(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// --- Função Principal (main) ---
int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int jogadorAtual = 1; 
    char marca;
    char linha_digitada, coluna_digitada; 
    int jogoTerminado = 0; 

    inicializarTabuleiro(tabuleiro); 

    
    while (!jogoTerminado) {
        exibirTabuleiro(tabuleiro); 
        marca = (jogadorAtual == 1) ? 'X' : '0';

        while (!obterEValidarJogada(tabuleiro, jogadorAtual, &linha_digitada, &coluna_digitada)) {
            // A mensagem de erro já é exibida dentro de obterEValidarJogada
        }

        fazerJogada(tabuleiro, linha_digitada, coluna_digitada, marca);

        // Verifica condições de fim de jogo
        if (verificarVitoria(tabuleiro, marca)) {
            exibirTabuleiro(tabuleiro); // Mostra o tabuleiro final com a jogada vencedora
            printf("----------------------------------------\n");
            printf("PARABÉNS! Jogador %d (%c) GANHOU O JOGO!\n", jogadorAtual, marca); // (d) Informa o ganhador
            printf("----------------------------------------\n");
            jogoTerminado = 1; // Encerra o loop do jogo
        } else if (verificarEmpate(tabuleiro)) {
            exibirTabuleiro(tabuleiro); // Mostra o tabuleiro final
            printf("----------------------------------------\n");
            printf("EMPATE! O tabuleiro está cheio e ninguém ganhou.\n"); // (d) Informa que não houve ganhador
            printf("----------------------------------------\n");
            jogoTerminado = 1; // Encerra o loop do jogo
        } else {
            // Troca o jogador para a próxima rodada, se o jogo ainda não terminou
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    printf("\nFim do Jogo da Velha.\n");
    return 0; 
}

// Preenche o tabuleiro com espaços vazios no início do jogo.
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Exibe o estado atual do tabuleiro para o usuário.
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  1   2   3\n"); // Rótulos das colunas
    char linhas_rotulo[] = {'A', 'B', 'C'}; // Rótulos das linhas

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", linhas_rotulo[i]); // Exibe o rótulo da linha (A, B, C)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %c ", tabuleiro[i][j]); // Exibe o conteúdo da célula (' ', 'X' ou '0')
            if (j < TAMANHO_TABULEIRO - 1) {
                printf("|"); // Desenha o separador vertical entre as colunas
            }
        }
        printf("\n");
        if (i < TAMANHO_TABULEIRO - 1) {
            printf("  ---|---|---\n"); // Desenha o separador horizontal entre as linhas
        }
    }
    printf("\n");
}

int obterEValidarJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorAtual, char *linha_ptr, char *coluna_ptr) {
    char entrada[10]; // Buffer para ler a entrada do usuário (ex: "B3", "A1")

    // (a) Mostra qual jogador deve jogar e pede a jogada
    printf("Jogador %d, informe sua jogada (ex: A1, B3): ", jogadorAtual);
    scanf("%s", entrada); // Lê a entrada como uma string

    // (c) Verificar se é uma célula válida - Parte 1: Formato da entrada
    if (strlen(entrada) != 2) {
        printf("Erro: Formato de jogada inválido. Use 'LetraNumero' (ex: A1).\n");
        return 0; // Jogada inválida
    }

    *linha_ptr = toupper(entrada[0]); // Converte a letra para maiúscula (A, B, C)
    *coluna_ptr = entrada[1];       // Pega o número da coluna (1, 2, 3)

    // Converte os caracteres para índices numéricos do array (0, 1, 2)
    int linha_idx = *linha_ptr - 'A';
    int coluna_idx = *coluna_ptr - '1';

    // (c) Verificar se é uma célula válida - Parte 2: Limites do tabuleiro
    if (linha_idx < 0 || linha_idx >= TAMANHO_TABULEIRO ||
        coluna_idx < 0 || coluna_idx >= TAMANHO_TABULEIRO) {
        printf("Erro: Posição fora dos limites do tabuleiro (A-C, 1-3).\n");
        return 0; // Jogada inválida
    }

    // (c) Verificar se é uma célula válida - Parte 3: Posição já ocupada
    if (tabuleiro[linha_idx][coluna_idx] != ' ') {
        printf("Erro: Essa posição já está ocupada. Escolha outra.\n");
        return 0; // Jogada inválida
    }

    return 1; // Jogada é válida
}

// Coloca a marca do jogador na posição escolhida no tabuleiro.
void fazerJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char linha_char, char coluna_char, char marca) {
    // Converte os caracteres da jogada em índices para o array
    int linha_idx = toupper(linha_char) - 'A';
    int coluna_idx = coluna_char - '1';
    tabuleiro[linha_idx][coluna_idx] = marca;
}

int verificarVitoria(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char marca) {
    // Verificar linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (tabuleiro[i][0] == marca && tabuleiro[i][1] == marca && tabuleiro[i][2] == marca)
            return 1; // Vitória em linha
    }
    // Verificar colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        if (tabuleiro[0][j] == marca && tabuleiro[1][j] == marca && tabuleiro[2][j] == marca)
            return 1; // Vitória em coluna
    }
    // Verificar diagonais
    if (tabuleiro[0][0] == marca && tabuleiro[1][1] == marca && tabuleiro[2][2] == marca)
        return 1; // Vitória na diagonal principal
    if (tabuleiro[0][2] == marca && tabuleiro[1][1] == marca && tabuleiro[2][0] == marca)
        return 1; // Vitória na diagonal secundária

    return 0; // Nenhuma vitória
}

int verificarEmpate(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; // Ainda há espaços vazios, o jogo pode continuar
            }
        }
    }
    return 1;
}
