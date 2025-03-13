#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Função para verificar se o navio pode ser posicionado no tabuleiro
bool podePosicionarNavio(int tabuleiro[10][10], int tamanho, int linha, int coluna, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        if (direcao == 'H') { // Horizontal
            if (coluna + i >= 10 || tabuleiro[linha][coluna + i] != 0) {
                return false;
            }
        } else if (direcao == 'V') { // Vertical
            if (linha + i >= 10 || tabuleiro[linha + i][coluna] != 0) {
                return false;
            }
        } else if (direcao == 'D') { // Diagonal crescente
            if (linha + i >= 10 || coluna + i >= 10 || tabuleiro[linha + i][coluna + i] != 0) {
                return false;
            }
        } else if (direcao == 'd') { // Diagonal decrescente
            if (linha + i >= 10 || coluna - i < 0 || tabuleiro[linha + i][coluna - i] != 0) {
                return false;
            }
        }
    }
    return true;
}

// Função para posicionar navios no tabuleiro
void posicionarNavio(int tabuleiro[10][10], int navio[], int tamanho, int linha, int coluna, char direcao) {
    if (podePosicionarNavio(tabuleiro, tamanho, linha, coluna, direcao)) {
        for (int i = 0; i < tamanho; i++) {
            if (direcao == 'H') { // Horizontal
                tabuleiro[linha][coluna + i] = navio[i];
            } else if (direcao == 'V') { // Vertical
                tabuleiro[linha + i][coluna] = navio[i];
            } else if (direcao == 'D') { // Diagonal crescente
                tabuleiro[linha + i][coluna + i] = navio[i];
            } else if (direcao == 'd') { // Diagonal decrescente
                tabuleiro[linha + i][coluna - i] = navio[i];
            }
        }
    } else {
        printf("Não é possível posicionar o navio nas coordenadas (%d, %d) na direção %c\n", linha, coluna, direcao);
    }
}

// Função para criar a matriz de habilidade em forma de cone
void criarHabilidadeCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de octaedro
void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[10][10], int habilidade[5][5], int origemLinha, int origemColuna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origemLinha + i - 2;
            int coluna = origemColuna + j - 2;
            if (linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10 && habilidade[i][j] == 1) {
                tabuleiro[linha][coluna] = 5;
            }
        }
    }
}

int main() {
    int tabuleiro[10][10] = {0}; // Inicializa o tabuleiro com 0 (água)
    
    // Coordenadas iniciais dos navios
    int navioHorizontal[3] = {3, 3, 3}; // Navio horizontal de tamanho 3
    int navioVertical[3] = {3, 3, 3};   // Navio vertical de tamanho 3
    int navioDiagonalCrescente[3] = {3, 3, 3}; // Navio diagonal crescente de tamanho 3
    int navioDiagonalDecrescente[3] = {3, 3, 3}; // Navio diagonal decrescente de tamanho 3

    // Posiciona o navio horizontal na linha 2, começando na coluna 1
    posicionarNavio(tabuleiro, navioHorizontal, 3, 2, 1, 'H');

    // Posiciona o navio vertical na coluna 5, começando na linha 4
    posicionarNavio(tabuleiro, navioVertical, 3, 4, 5, 'V');

    // Posiciona o navio diagonal crescente na linha 0, começando na coluna 0
    posicionarNavio(tabuleiro, navioDiagonalCrescente, 3, 0, 0, 'D');

    // Posiciona o navio diagonal decrescente na linha 0, começando na coluna 9
    posicionarNavio(tabuleiro, navioDiagonalDecrescente, 3, 0, 9, 'd');

    // Matrizes de habilidades
    int habilidadeCone[5][5];
    int habilidadeCruz[5][5];
    int habilidadeOctaedro[5][5];

    // Cria as habilidades
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // Aplica as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 4, 4); // Exemplo de aplicação da habilidade Cone
    aplicarHabilidade(tabuleiro, habilidadeCruz, 6, 6); // Exemplo de aplicação da habilidade Cruz
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 8, 8); // Exemplo de aplicação da habilidade Octaedro

    // Exibe o tabuleiro no console
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("* "); // Área afetada pela habilidade
            }
        }
        printf("\n");
    }

    return 0;
}
