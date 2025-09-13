#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[20];
    int quantidadeTropas;
} Territorio;

// Função para simular ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->quantidadeTropas <= 1) {
        printf("O território %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;  // dado de 1 a 6
    int dadoDefesa = (rand() % 6) + 1;

    printf("%s (Atacante) rolou: %d\n", atacante->nome, dadoAtaque);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->quantidadeTropas--;
        printf("Defensor perdeu 1 tropa!\n");

        if (defensor->quantidadeTropas <= 0) {
            printf(">>> %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            defensor->quantidadeTropas = 1; // ocupa com pelo menos 1 tropa
            atacante->quantidadeTropas--;   // transfere tropa
            strcpy(defensor->corExercito, atacante->corExercito);
        }
    } else {
        atacante->quantidadeTropas--;
        printf("Atacante perdeu 1 tropa!\n");
    }

    printf("\n");
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int n = 5;
    Territorio *territorios = (Territorio *) calloc(n, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("Cadastro do território %d\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].quantidadeTropas);
        getchar(); // limpar buffer
        printf("\n");
    }

    int opcao;
    do {
        printf("=== Fase de Ataque ===\n");
        for (int i = 0; i < n; i++) {
            printf("%d - %s (%s) - Tropas: %d\n",
                   i, territorios[i].nome,
                   territorios[i].corExercito,
                   territorios[i].quantidadeTropas);
        }

        int idxAtacante, idxDefensor;
        printf("Escolha o índice do território atacante (-1 para sair): ");
        scanf("%d", &idxAtacante);

        if (idxAtacante == -1) break;

        printf("Escolha o índice do território defensor: ");
        scanf("%d", &idxDefensor);

        if (idxAtacante >= 0 && idxAtacante < n &&
            idxDefensor >= 0 && idxDefensor < n &&
            idxAtacante != idxDefensor) {
            atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
        } else {
            printf("Escolha inválida!\n\n");
        }

    } while (1);

    free(territorios); // libera memória
    return 0;
}
