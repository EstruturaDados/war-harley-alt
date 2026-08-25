// Inclui as bibliotecas necessarias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definicao da estrutura composta
estrutura Territorio{
    personagem nome[30];
    personagem cor[10];
    inteiro tropas;
};

// Funcao para cadastrar territorios
vazio cadastrarTerritorios(Territorio* mapa, inteiro quantidade) {
    inteiro eu;
    printf("===== CADASTRO DE TERRITORIOS =====\n");
    printf("Informe os dados dos territorios:\n");

    para(eu = 0; eu < quantidade; eu++) {
        printf("--- Territorio %d ---\n", eu + 1);

        printf("Nome: ");
        scanf(" %[^\n]s", mapa[eu].nome);

        printf("Cor do exercito: ");
        scanf(" %s", mapa[eu].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[eu].tropas);

        printf("\n");
    }
}

// Funcao para exibir territorios
vazio exibirTerritorios(Territorio* mapa, inteiro quantidade) {
    inteiro eu;
    printf("===== LISTA DE TERRITORIOS CADASTRADOS =====\n");

    para(eu = 0; eu < quantidade; eu++) {
        printf("Territorio %d:\n", eu + 1);
        printf("  Nome: %s\n", mapa[eu].nome);
        printf("  Cor do exercito: %s\n", mapa[eu].cor);
        printf("  Quantidade de tropas: %d\n", mapa[eu].tropas);
        printf("------------------------------------\n");
    }
}

// Funcao de ataque entre territorios
vazio atacar(Territorio* atacante, Territorio* defensor) {
    inteiro dadoAtacante, dadoDefensor;
    inteiro tropasTransferidas;

    printf("\nBATALHA: %s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    se (dadoAtacante > dadoDefensor) {
        printf("O atacante VENCEU! Territorio conquistado!\n");

        strcpy(defensor->cor, atacante->cor);

        tropasTransferidas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas - tropasTransferidas;
        defensor->tropas = tropasTransferidas;
    }
    senão {
        printf("O defensor VENCEU! O atacante perdeu 1 tropa.\n");
        atacante->tropas = atacante->tropas - 1;
    }
}

// Funcao para liberar memoria
vazio liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

// Programa principal
inteiro principal() {
    Territorio* mapa;
    inteiro totalTerritorios;
    inteiro atacante, defensor;
    personagem continuar;

    srand(time(NULL));

    printf("========== JOGO WAR - SISTEMA DE ATAQUES ==========\n");
    printf("Informe quantos territorios deseja cadastrar: ");
    scanf("%d", &totalTerritorios);

    mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    se (mapa == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        retornar 1;
    }

    cadastrarTerritorios(mapa, totalTerritorios);

    exibirTerritorios(mapa, totalTerritorios);

    printf("\n\n===== SISTEMA DE ATAQUE =====\n");
    printf("Escolha os territorios pelo numero da lista.\n");

    faça {
        printf("\nNumero do territorio ATACANTE: ");
        scanf("%d", &atacante);

        printf("Numero do territorio DEFENSOR: ");
        scanf("%d", &defensor);

        atacante = atacante - 1;
        defensor = defensor - 1;

        // Validacoes
        se (atacante < 0 || atacante >= totalTerritorios ||
            defensor < 0 || defensor >= totalTerritorios) {
            printf("Territorio invalido! Tente novamente.\n");
            continue;
        }

        se (atacante == defensor) {
            printf("Nao e possivel atacar o proprio territorio!\n");
            continue;
        }

        se (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Nao e possivel atacar territorio da MESMA COR!\n");
            continue;
        }

        // Realiza o ataque
        atacar(&mapa[atacante], &mapa[defensor]);

        // Exibe dados atualizados
        exibirTerritorios(mapa, totalTerritorios);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } enquanto (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);

    printf("\nPrograma encerrado com sucesso!\n");
    retornar 0;
}
