#include <stdio.h>   
#include <string.h>  
#include <ctype.h>   

#define TAMANHO_TABULEIRO 3 

void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
int obterEValidarJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorAtual, char *linha_ptr, char *coluna_ptr);
void fazerJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char linha_char, char coluna_char, char marca);
int verificarVitoria(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char marca);
int verificarEmpate(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

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
        }

        fazerJogada(tabuleiro, linha_digitada, coluna_digitada, marca);
        if (verificarVitoria(tabuleiro, marca)) {
            exibirTabuleiro(tabuleiro); 
            printf("----------------------------------------\n");
            printf("PARABÉNS! Jogador %d (%c) GANHOU O JOGO!\n", jogadorAtual, marca);
            printf("----------------------------------------\n");
            jogoTerminado = 1; 
        } else if (verificarEmpate(tabuleiro)) {
            exibirTabuleiro(tabuleiro); 
            printf("----------------------------------------\n");
            printf("EMPATE! O tabuleiro está cheio e ninguém ganhou.\n"); 
            printf("----------------------------------------\n");
            jogoTerminado = 1; 
        } else {
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    printf("\nFim do Jogo da Velha.\n");
    return 0; 
}
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  1   2   3\n"); 
    char linhas_rotulo[] = {'A', 'B', 'C'}; 

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", linhas_rotulo[i]); 
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %c ", tabuleiro[i][j]); 
            if (j < TAMANHO_TABULEIRO - 1) {
                printf("|"); 
            }
        }
        printf("\n");
        if (i < TAMANHO_TABULEIRO - 1) {
            printf("  ---|---|---\n"); 
        }
    }
    printf("\n");
}

int obterEValidarJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorAtual, char *linha_ptr, char *coluna_ptr) {
    char entrada[10]; 
    printf("Jogador %d, informe sua jogada (ex: A1, B3): ", jogadorAtual);
    scanf("%s", entrada); 
    if (strlen(entrada) != 2) {
        printf("Erro: Formato de jogada inválido. Use 'LetraNumero' (ex: A1).\n");
        return 0; 
    }

    *linha_ptr = toupper(entrada[0]);
    *coluna_ptr = entrada[1];       

    int linha_idx = *linha_ptr - 'A';
    int coluna_idx = *coluna_ptr - '1';

    if (linha_idx < 0 || linha_idx >= TAMANHO_TABULEIRO ||
        coluna_idx < 0 || coluna_idx >= TAMANHO_TABULEIRO) {
        printf("Erro: Posição fora dos limites do tabuleiro (A-C, 1-3).\n");
        return 0; 
    }
    if (tabuleiro[linha_idx][coluna_idx] != ' ') {
        printf("Erro: Essa posição já está ocupada. Escolha outra.\n");
        return 0; 
    }

    return 1; 
}
void fazerJogada(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char linha_char, char coluna_char, char marca) {
    int linha_idx = toupper(linha_char) - 'A';
    int coluna_idx = coluna_char - '1';
    tabuleiro[linha_idx][coluna_idx] = marca;
}

int verificarVitoria(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char marca) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (tabuleiro[i][0] == marca && tabuleiro[i][1] == marca && tabuleiro[i][2] == marca)
            return 1; 
    }
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        if (tabuleiro[0][j] == marca && tabuleiro[1][j] == marca && tabuleiro[2][j] == marca)
            return 1; 
    }
    if (tabuleiro[0][0] == marca && tabuleiro[1][1] == marca && tabuleiro[2][2] == marca)
        return 1; 
    if (tabuleiro[0][2] == marca && tabuleiro[1][1] == marca && tabuleiro[2][0] == marca)
        return 1; 

    return 0; 
}

int verificarEmpate(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; 
            }
        }
    }
    return 1;
}
