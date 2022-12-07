
#include <stdio.h>
#include <string.h>

struct sessao
{
    char nome[100];
    int poltronas[4][5];
};

void
inicia_sessao(struct sessao *atual, char *nome)
{
    int linhas, colunas;
    
    strcpy(atual->nome, nome);
    
    for (linhas = 0; linhas < 4; linhas++) {
        for (colunas = 0; colunas < 5; colunas++) {
            atual->poltronas[linhas][colunas] = 0;
        }
    }
}

void
mostra_sessao(struct sessao *atual)
{
    int linhas, colunas;
    printf("\tNome da sessao:%s\n", atual->nome);
    
    printf("  |");
    for (colunas = 0; colunas < 5; colunas++)
    {
        printf("%i", colunas+1);
        if (colunas < 5-1) {
            printf(" |");
        }
    }
    printf("\n");
    
    for (linhas = 0; linhas < 4; linhas++) {
        printf("%i |", linhas+1);
        for (colunas = 0; colunas < 5; colunas++) {
            switch (atual->poltronas[linhas][colunas]) {
                case 0:
                    printf("V");
                    break;
                
                case 1:
                    printf("O");
                    break;
            }
            if (colunas < 5-1) {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf("V = Vazio\nO = Ocupado\n");
}

int main(void)
{
    FILE *file;
    file = fopen("database.csv", "a");
    char texto[30];
    
    struct sessao filme;
    char buffer[250];
    inicia_sessao(&filme, "Avatar 2");
    do {
        int linha, coluna;
        mostra_sessao(&filme);
        printf("Digite a linha da poltrona desejada:");
        fgets(buffer, 250, stdin);
        sscanf(buffer, "%i", &linha);
        printf("Digite a coluna da poltrona desejada:");
        fgets(buffer, 250, stdin);
        sscanf(buffer, "%i", &coluna);
        if (linha-1 >= 0 && linha-1 < 4 &&
            coluna-1 >= 0 && coluna-1 < 5) {
            if (filme.poltronas[linha-1][coluna-1] == 0) {
                filme.poltronas[linha-1][coluna-1] = 1;
                printf("A poltrona foi ocupada!\n");
                fprintf(file, "\n%s - Linha %d - Coluna %d", &filme, coluna, linha);
                fclose(file);
            } else {
                printf("A poltrona ja esta ocupada!\n");
            }
        } else {
            printf("poltrona invalida!\n");
        }
        printf("Digite S para sair ou C para continuar\n");
        fgets(buffer, 250, stdin);
    } while (buffer[0] == 'C' || buffer[0] == 'c');
    return(0);
}
