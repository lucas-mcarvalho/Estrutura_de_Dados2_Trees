#include <stdio.h>

#define TAM 10   // Tamanho total da tabela
#define HASH_SIZE 5  // Tamanho lógico da tabela (área principal)

typedef struct {
    int valor;
    int prox; // índice do próximo elemento encadeado
} HashItem;

void inicializar(HashItem tabela[]) {
    for (int i = 0; i < TAM; i++) {
        tabela[i].valor = -1;
        tabela[i].prox = -1;
    }
}

int buscarEspacoLivre(HashItem tabela[]) {
    for (int i = HASH_SIZE; i < TAM; i++) {
        if (tabela[i].valor == -1) {
            return i;
        }
    }
    return -1; // sem espaço
}

void inserir(HashItem tabela[], int x) {
    int h = x % HASH_SIZE;

    if (tabela[h].valor == -1) {
        tabela[h].valor = x;
    } else {
        // colisão: busca espaço livre na área extra
        int livre = buscarEspacoLivre(tabela);
        if (livre == -1) {
            printf("Tabela cheia! Não foi possível inserir %d.\n", x);
            return;
        }

        // percorre até o último da corrente
        int atual = h;
        while (tabela[atual].prox != -1) {
            atual = tabela[atual].prox;
        }

        tabela[livre].valor = x;
        tabela[atual].prox = livre;
    }
}

void imprimir(HashItem tabela[]) {
    printf("Índice | Valor | Próximo\n");
    printf("-------------------------\n");
    for (int i = 0; i < TAM; i++) {
        printf("  %2d   |  %3d  |  %2d\n", i, tabela[i].valor, tabela[i].prox);
    }
}

int main() {
    HashItem tabela[TAM];
    inicializar(tabela);

    int valores[] = {12, 7, 17, 22, 32}; // Todos vão gerar colisão em h(x) = x % 5
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        inserir(tabela, valores[i]);
    }

    imprimir(tabela);

    return 0;
}
