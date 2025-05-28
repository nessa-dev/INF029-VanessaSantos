#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <string.h> 
#include <ctype.h>  

#define TAMANHO_TABULEIRO 10 // Tabuleiro 10x10 (Requisito c)
#define NUM_NAVIOS_PADRAO 5  // Número mínimo de barcos (Requisito b)

typedef struct {
    int tamanho;
    int acertos; 
    int posicoes[4][2]; 
    char orientacao;    
    int id;             
} Navio;

typedef struct {
    char nome[50];
    char tabuleiroMapa[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]; 
    char tabuleiroTiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]; 
    Navio navios[NUM_NAVIOS_PADRAO]; 
    int naviosRestantes; 
} Jogador;

void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void configurarNavios(Jogador *jogador);
int posicionarNavio(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio *navio, int linha, int coluna, char orientacao);
int validarPosicaoNavio(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int tamanho, int linha, int coluna, char orientacao);
void mostrarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int visibilidade); 
int obterCoordenada(char *linha_char, char *coluna_char);
void atirar(Jogador *atacante, Jogador *defensor); 
int verificarVitoria(Jogador *jogador); 

int main() {
    srand(time(NULL));

    Jogador jogador1, jogador2;

    strcpy(jogador1.nome, "Jogador 1");
    jogador1.naviosRestantes = NUM_NAVIOS_PADRAO;
    inicializarTabuleiro(jogador1.tabuleiroMapa);
    inicializarTabuleiro(jogador1.tabuleiroTiro);

    strcpy(jogador2.nome, "Jogador 2");
    jogador2.naviosRestantes = NUM_NAVIOS_PADRAO;
    inicializarTabuleiro(jogador2.tabuleiroMapa);
    inicializarTabuleiro(jogador2.tabuleiroTiro);

    printf("===== Posicionamento dos Navios para %s =====\n", jogador1.nome);
    configurarNavios(&jogador1);

    system("cls || clear"); 

    printf("===== Posicionamento dos Navios para %s =====\n", jogador2.nome);
    configurarNavios(&jogador2);

    system("cls || clear"); 

    int turno = 1;
    Jogador *jogadorAtual, *oponente;

    printf("Iniciando a Batalha Naval!\n");

    while (jogador1.naviosRestantes > 0 && jogador2.naviosRestantes > 0) {
        printf("\n--- TURNO %d ---\n", turno);

        if (turno % 2 != 0) { 
            jogadorAtual = &jogador1;
            oponente = &jogador2;
        } else { 
            jogadorAtual = &jogador2;
            oponente = &jogador1;
        }

        printf("\nÉ a vez de %s\n", jogadorAtual->nome);

        printf("\nSeu Mapa (%s):\n", jogadorAtual->nome);
        mostrarTabuleiro(jogadorAtual->tabuleiroMapa, 0); 

        printf("\nMapa do Oponente (Tiros de %s):\n", jogadorAtual->nome);
        mostrarTabuleiro(jogadorAtual->tabuleiroTiro, 1); 

        atirar(jogadorAtual, oponente);

        if (verificarVitoria(oponente)) { 
            printf("\n============================================\n");
            printf("PARABÉNS, %s GANHOU A BATALHA NAVAL!\n", jogadorAtual->nome);
            printf("============================================\n");
            break; 
        }

        printf("\nPressione Enter para continuar...\n");
        getchar(); 
        getchar(); 

        system("cls || clear"); 

        turno++;
    }

    printf("\n--- FIM DE JOGO ---\n");
    printf("\nMapa final de %s:\n", jogador1.nome);
    mostrarTabuleiro(jogador1.tabuleiroMapa, 0);
    printf("\nMapa final de %s:\n", jogador2.nome);
    mostrarTabuleiro(jogador2.tabuleiroMapa, 0);

    return 0;
}

void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = ' '; 
        }
    }
}


void mostrarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int visibilidade) {
    printf("   A B C D E F G H I J\n"); 
    printf("  ---------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d|", i + 1); 
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (visibilidade == 1) { 
                if (tabuleiro[i][j] == 'N') { 
                    printf("  ");
                } else {
                    printf(" %c", tabuleiro[i][j]); 
                }
            } else {
                printf(" %c", tabuleiro[i][j]); 
            }
        }
        printf(" |\n");
    }
    printf("  ---------------------\n");
}

void configurarNavios(Jogador *jogador) {
    int tamanhos_navios[NUM_NAVIOS_PADRAO] = {4, 3, 1, 1, 1}; 

    printf("\n%s, é hora de posicionar seus navios!\n", jogador->nome);
    printf("Você deve posicionar %d navios:\n", NUM_NAVIOS_PADRAO);
    printf("  - 1 Porta-aviões (tamanho 4)\n");
    printf("  - 1 Submarino (tamanho 3)\n");
    printf("  - 3 Patrulhas (tamanho 1)\n");

    for (int i = 0; i < NUM_NAVIOS_PADRAO; i++) {
        jogador->navios[i].id = i + 1; 
        jogador->navios[i].tamanho = tamanhos_navios[i];
        jogador->navios[i].acertos = 0;

        int linha, coluna;
        char linha_char, coluna_char;
        char orientacao_char;
        int posicaoValida = 0;

        while (!posicaoValida) {
            system("cls || clear"); 
            printf("--- Posicionando Navio %d (Tamanho %d) ---\n", i + 1, jogador->navios[i].tamanho);
            mostrarTabuleiro(jogador->tabuleiroMapa, 0);

            printf("Digite a coordenada inicial (ex: A1) e a orientação (H para Horizontal, V para Vertical) para o navio de tamanho %d: ", jogador->navios[i].tamanho);
            if (scanf(" %c%c %c", &linha_char, &coluna_char, &orientacao_char) != 3) {
                 printf("Entrada inválida. Use o formato: LetraNumero Orientacao (ex: A1 H)\n");
                 while (getchar() != '\n');
                 continue;
            }
            while (getchar() != '\n'); 

            linha_char = toupper(linha_char);
            orientacao_char = toupper(orientacao_char);

            linha = linha_char - 'A';
            coluna = coluna_char - '1';

            if (posicionarNavio(jogador->tabuleiroMapa, &jogador->navios[i], linha, coluna, orientacao_char)) {
                posicaoValida = 1;
                printf("Navio posicionado com sucesso!\n");
                printf("Pressione Enter para continuar...\n");
                getchar(); 
            } else {
                printf("Posição inválida para o navio! Tente novamente.\n");
                printf("Pressione Enter para continuar...\n");
                getchar(); 
            }
        }
    }
    printf("\nTodos os navios de %s foram posicionados!\n", jogador->nome);
    printf("Pressione Enter para iniciar o jogo...\n");
    getchar(); 
}

int validarPosicaoNavio(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int tamanho, int linha, int coluna, char orientacao) {
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return 0; 
    }

    for (int k = 0; k < tamanho; k++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += k;
        } else if (orientacao == 'V') {
            r += k;
        } else {
            return 0; 
        }

        if (r < 0 || r >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) {
            return 0;
        }
        if (tabuleiro[r][c] == 'N') {
            return 0; 
        }
    }
    return 1; 
}

int posicionarNavio(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio *navio, int linha, int coluna, char orientacao) {
    if (!validarPosicaoNavio(tabuleiro, navio->tamanho, linha, coluna, orientacao)) {
        return 0; 
    }

    navio->orientacao = orientacao; 
    for (int k = 0; k < navio->tamanho; k++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += k;
        } else { 
            r += k;
        }
        tabuleiro[r][c] = 'N'; 
        navio->posicoes[k][0] = r;
        navio->posicoes[k][1] = c;
    }
    return 1; 
}

void atirar(Jogador *atacante, Jogador *defensor) {
    int linha, coluna;
    char linha_char, coluna_char;
    int tiroValido = 0;

    printf("\n%s, é hora de atirar!\n", atacante->nome);

    while (!tiroValido) {
        printf("Informe a coordenada do tiro (ex: A1): ");
        if (obterCoordenada(&linha_char, &coluna_char) == 0) {
            printf("Entrada inválida. Use o formato: LetraNumero (ex: B3).\n");
            continue;
        }

        linha = toupper(linha_char) - 'A';
        coluna = coluna_char - '1';

        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            printf("Tiro fora dos limites do tabuleiro! Tente novamente.\n");
            continue;
        }

        if (atacante->tabuleiroTiro[linha][coluna] != ' ') {
            printf("Você já atirou nesta posição! Escolha outra.\n");
            continue;
        }
        tiroValido = 1;
    }

    printf("\nAtirando em %c%c...\n", toupper(linha_char), coluna_char);

    if (defensor->tabuleiroMapa[linha][coluna] == 'N') {
        printf("TIRO CERTEIRO! Um navio inimigo foi atingido!\n");
        defensor->tabuleiroMapa[linha][coluna] = '0'; 

        atacante->tabuleiroTiro[linha][coluna] = '0';

        int navio_afundado = 0;
        for (int i = 0; i < NUM_NAVIOS_PADRAO; i++) {
            for (int k = 0; k < defensor->navios[i].tamanho; k++) {
                if (defensor->navios[i].posicoes[k][0] == linha && defensor->navios[i].posicoes[k][1] == coluna) {
                    defensor->navios[i].acertos++;
                    if (defensor->navios[i].acertos == defensor->navios[i].tamanho) {
                        printf("Você AFUNDOU um navio inimigo de tamanho %d!\n", defensor->navios[i].tamanho);
                        defensor->naviosRestantes--; // Decrementa a contagem de navios restantes
                        navio_afundado = 1;
                    }
                    break;
                }
            }
            if (navio_afundado) break; 
        }

    } else {
        printf("TIRO NA ÁGUA! Você errou.\n");
        defensor->tabuleiroMapa[linha][coluna] = 'X'; 
        atacante->tabuleiroTiro[linha][coluna] = 'X';
    }
}


int obterCoordenada(char *linha_char_ptr, char *coluna_char_ptr) {
    char entrada[10];
    if (scanf("%s", entrada) != 1) {
        while (getchar() != '\n'); 
        return 0;
    }
    while (getchar() != '\n'); 

    if (strlen(entrada) != 2) {
        return 0; 
    }

    *linha_char_ptr = entrada[0];
    *coluna_char_ptr = entrada[1];

    
    if (!isalpha(*linha_char_ptr) || !isdigit(*coluna_char_ptr)) {
        return 0;
    }
    return 1;
}

int verificarVitoria(Jogador *jogador) {
    return (jogador->naviosRestantes == 0);
}
