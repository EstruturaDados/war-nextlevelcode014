#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =====================
// Definições
// =====================
typedef struct {
    char nome[50];
    char corExercito[20];
    int quantidadeTropas;
} Territorio;

typedef struct {
    char nome[50];
    char cor[20];
    Territorio *territorios; // ponteiro para territórios que controla
    int qtdTerritorios;
    char *missao; // missão estratégica
} Jogador;

// =====================
// Função: Sorteio de missão
// =====================
char *sortearMissao(char *missoes[], int qtd) {
    int idx = rand() % qtd;
    return missoes[idx];
}

// =====================
// Função: Cadastro de jogadores
// =====================
void cadastrarJogadores(Jogador *jogadores, int qtdJogadores, char *missoes[], int qtdMissoes) {
    for (int i = 0; i < qtdJogadores; i++) {
        printf("Cadastro do Jogador %d\n", i + 1);

        printf("Nome do jogador: ");
        fgets(jogadores[i].nome, sizeof(jogadores[i].nome), stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(jogadores[i].cor, sizeof(jogadores[i].cor), stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';

        // Inicialmente sem territórios
        jogadores[i].territorios = NULL;
        jogadores[i].qtdTerritorios = 0;

        // Sorteio de missão
        jogadores[i].missao = sortearMissao(missoes, qtdMissoes);
        printf("Missão secreta atribuída: %s\n\n", jogadores[i].missao);
    }
}

// =====================
// Função: Verificação de vitória
// =====================
int verificarMissao(Jogador *jogador) {
    // Exemplo de checagem: missão depende do texto
    if (strstr(jogador->missao, "conquistar") != NULL) {
        if (jogador->qtdTerritorios >= 3) {
            return 1;
        }
    }
    if (strstr(jogador->missao, "eliminar") != NULL) {
        // Exemplo fictício: se tiver mais de 10 tropas no total
        int tropas = 0;
        for (int i = 0; i < jogador->qtdTerritorios; i++) {
            tropas += jogador->territorios[i].quantidadeTropas;
        }
        if (tropas > 10) {
            return 1;
        }
    }
    return 0;
}

// =====================
// Função principal
// =====================
int main() {
    srand(time(NULL));

    // Missões pré-definidas
    char *missoes[] = {
        "Conquistar 3 territórios",
        "Eliminar um jogador adversário",
        "Acumular mais de 10 tropas",
        "Conquistar dois territórios da mesma cor",
        "Defender todos os seus territórios por 3 rodadas"
    };
    int qtdMissoes = sizeof(missoes) / sizeof(missoes[0]);

    int qtdJogadores = 2;
    Jogador *jogadores = (Jogador *) calloc(qtdJogadores, sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para jogadores.\n");
        return 1;
    }

    // Cadastro dos jogadores e atribuição de missão
    cadastrarJogadores(jogadores, qtdJogadores, missoes, qtdMissoes);

    // Simulação fictícia: atribuindo territórios manualmente
    jogadores[0].qtdTerritorios = 2;
    jogadores[1].qtdTerritorios = 4;

    // Checagem de vitória
    for (int i = 0; i < qtdJogadores; i++) {
        printf("Verificando vitória para %s...\n", jogadores[i].nome);
        if (verificarMissao(&jogadores[i])) {
            printf(">>> Jogador %s COMPLETOU sua missão: %s\n", jogadores[i].nome, jogadores[i].missao);
        } else {
            printf("Missão ainda não concluída.\n");
        }
    }

    free(jogadores);
    return 0;
}
