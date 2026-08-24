// Inclui as bibliotecas necessárias:
// stdio.h → funções de entrada e saída (printf, scanf)
// string.h → funções para manipulação de textos
#include <stdio.h>
#include <string.h>

// Definição da estrutura composta:
// Agrupa dados relacionados a um território em um único tipo
struct Territorio {
    char nome[30];    // Nome do território (até 29 caracteres)
    char cor[10];     // Cor do exército (ex: Vermelho, Azul...)
    int tropas;      // Quantidade de tropas inteira
};

int main() {
    // Cria um VETOR de estruturas: armazena 5 territórios
    struct Territorio territorios[5];
    int i; // Variável auxiliar para os laços de repetição

    // ==================== ETAPA DE CADASTRO ====================
    printf("===== CADASTRO DE TERRITÓRIOS =====\n");
    printf("Informe os dados dos 5 territórios abaixo:\n\n");

    // Laço de repetição: repete o preenchimento 5 vezes
    for (i = 0; i < 5; i++) {
        printf("--- Território %d ---\n", i + 1);

        // Lê o nome do território
        printf("Nome: ");
        scanf(" %[^\n]s", territorios[i].nome);

        // Lê a cor do exército
        printf("Cor do exército: ");
        scanf(" %s", territorios[i].cor);

        // Lê a quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Linha em branco para organizar
    }

    // ==================== ETAPA DE EXIBIÇÃO ====================
    printf("===== LISTA DE TERRITÓRIOS CADASTRADOS =====\n\n");

    // Percorre o vetor e mostra todos os dados armazenados
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exército: %s\n", territorios[i].cor);
        printf("  Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("------------------------------------\n");
    }

    return 0; // Indica que o programa finalizou com sucesso
}
