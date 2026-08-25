#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    int i;
    printf("===== CADASTRO DE TERRITORIOS =====\n");
    printf("Informe os dados dos territorios:\n");

    for (i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

void exibirTerritorios(Territorio* mapa, int quantidade) {
    int i;
    printf("===== LISTA DE TERRITORIOS CADASTRADOS =====\n");

    for (i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do exercito: %s\n", mapa[i].cor);
        printf("  Quantidade de tropas: %d\n", mapa[i].tropas);
        printf("------------------------------------\n");
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    int tropasTransferidas;

    printf("\nBATALHA: %s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante VENCEU! Territorio conquistado!\n");

        strcpy(defensor->cor, atacante->cor);

        tropasTransferidas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas - tropasTransferidas;
        defensor->tropas = tropasTransferidas;
    }
    else {
        printf("O defensor VENCEU! O atacante perdeu 1 tropa.\n");
        atacante->tropas = atacante->tropas - 1;
    }
}

// Função que LIBERA A MEMÓRIA MANUALMENTE quando digitar 0
void liberarMemoria(Territorio* mapa) {
    free(mapa);  // ← COMANDO FREE executado aqui! ✅
    printf("\nMemoria liberada com sucesso!\n");
}

int main() {
    Territorio* mapa;
    int totalTerritorios;
    int atacante, defensor;

    srand(time(NULL));

    printf("========== JOGO WAR - SISTEMA DE ATAQUES ==========\n");
    printf("Informe quantos territorios deseja cadastrar: ");
    scanf("%d", &totalTerritorios);

    mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, totalTerritorios);

    exibirTerritorios(mapa, totalTerritorios);

    printf("\n\n===== SISTEMA DE ATAQUE =====\n");
    printf("Digite 0 (zero) a qualquer momento para ENCERRAR e liberar memoria.\n");

    do {
        printf("\nNumero do territorio ATACANTE (ou 0 para encerrar): ");
        scanf("%d", &atacante);

        // ✅ SE DIGITAR 0 → ENCERRA E LIBERA A MEMÓRIA MANUALMENTE!
        if (atacante == 0) {
            liberarMemoria(mapa);  // ← CHAMA O FREE MANUALMENTE! ✅
            printf("Programa encerrado com sucesso!\n");
            return 0;
        }

        printf("Numero do territorio DEFENSOR: ");
        scanf("%d", &defensor);

        atacante = atacante - 1;
        defensor = defensor - 1;

        if (atacante < 0 || atacante >= totalTerritorios ||
            defensor < 0 || defensor >= totalTerritorios) {
            printf("Territorio invalido! Tente novamente.\n");
            continue;
        }

        if (atacante == defensor) {
            printf("Nao e possivel atacar o proprio territorio!\n");
            continue;
        }

        if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Nao e possivel atacar territorio da MESMA COR!\n");
            continue;
        }

        atacar(&mapa[atacante], &mapa[defensor]);

        exibirTerritorios(mapa, totalTerritorios);

    } while (1);  // Repete infinitamente até digitar 0
}
