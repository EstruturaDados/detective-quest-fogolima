#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------
// Estrutura da Sala (nó da árvore binária)
// ------------------------------
typedef struct Sala {
    char nome[50];            // Nome do cômodo
    struct Sala *esquerda;    // Caminho à esquerda
    struct Sala *direita;     // Caminho à direita
} Sala;

// ------------------------------
// Função: criarSala
// Cria dinamicamente uma sala (nó da árvore) com o nome informado
// ------------------------------
Sala* criarSala(char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ------------------------------
// Função: explorarSalas
// Permite ao jogador explorar a mansão interativamente
// Começa no "Hall de Entrada" e segue pelos caminhos escolhidos
// ------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    printf("\n🏠 Você está no(a): %s\n", atual->nome);

    // Enquanto houver caminhos possíveis
    while (1) {
        // Caso a sala não tenha saídas, o jogador chegou ao fim
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n🔍 Você chegou ao fim do caminho! Não há mais portas nesta sala.\n");
            break;
        }

        printf("\nEscolha seu caminho:\n");
        if (atual->esquerda != NULL)
            printf(" (e) Ir para a esquerda → %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf(" (d) Ir para a direita → %s\n", atual->direita->nome);
        printf(" (s) Sair da exploração\n");
        printf("Sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
            printf("\n➡️  Você entrou em: %s\n", atual->nome);
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
            printf("\n➡️  Você entrou em: %s\n", atual->nome);
        } else if (escolha == 's') {
            printf("\n👋 Exploração encerrada.\n");
            break;
        } else {
            printf("\n⚠️  Caminho inválido! Escolha novamente.\n");
        }
    }
}

// ------------------------------
// Função: liberarArvore
// Libera toda a memória alocada da árvore
// ------------------------------
void liberarArvore(Sala *raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// ------------------------------
// Função principal (main)
// Cria o mapa da mansão e inicia a exploração
// ------------------------------
int main() {
    // Montagem do mapa (árvore binária)
    Sala *hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Jardim Interno");

    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Garagem");

    // Início da exploração
    printf("============================================\n");
    printf("🔎 BEM-VINDO AO DETECTIVE QUEST: MANSÃO ENIGMA\n");
    printf("============================================\n");
    printf("\nExplore a mansão e descubra o caminho até o fim!\n");

    explorarSalas(hall);

    // Libera memória antes de encerrar
    liberarArvore(hall);

    printf("\n💾 Memória liberada. Fim do jogo.\n");
    return 0;
}
