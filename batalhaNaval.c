#include <stdio.h>
#include <stdbool.h>

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
            }
        }
    } else {
        printf("Não é possível posicionar o navio nas coordenadas (%d, %d) na direção %c\n", linha, coluna, direcao);
    }
}

int main() {
    int tabuleiro[10][10] = {0}; // Inicializa o tabuleiro com 0 (água)
    
    // Coordenadas iniciais dos navios
    int navioHorizontal[3] = {3, 3, 3}; // Navio horizontal de tamanho 3
    int navioVertical[3] = {3, 3, 3};   // Navio vertical de tamanho 3

    // Posiciona o navio horizontal na linha 2, começando na coluna 1
    posicionarNavio(tabuleiro, navioHorizontal, 3, 2, 1, 'H');

    // Posiciona o navio vertical na coluna 5, começando na linha 4
    posicionarNavio(tabuleiro, navioVertical, 3, 4, 5, 'V');

    // Exibe o tabuleiro no console
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
