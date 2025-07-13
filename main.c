#include <stdio.h>
#include <stdlib.h>
#include "diplomas.h"

int menu() {
    int opcao;
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar diploma (enfileirar)\n");
    printf("2. Mostrar fila de diplomas\n");
    printf("3. Separar diploma para entrega (desenfileirar e empilhar)\n");
    printf("4. Mostrar pilha de diplomas separados\n");
    printf("5. Entregar diploma ao aluno (desempilhar)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

int main() {
    Fila fila_diplomas = {NULL, NULL};
    Pilha pilha_diplomas = {NULL};

    int opcao;
    int id = 0;
    do { 
        opcao = menu();

        switch(opcao) {
            case 0:
                printf("Saindo....\n");
                break;
            case 1:
                id++;
                Diploma *novo = criar(id);
                enfileirar(novo, &fila_diplomas);
                break;
            case 2:
                listar_fila(&fila_diplomas);
                break;
            case 3:{
                Diploma *pronto = desenfileirar(&fila_diplomas);
                if (pronto != NULL) {
                    empilhar(&pilha_diplomas, pronto);
                    printf("Diploma separado para entrega (movido para a pilha na mesa).\n");
                }
                break;
            }    
            case 4:
                listar_pilha(&pilha_diplomas);
                break;
            case 5:{
                Diploma *entregue = desempilhar(&pilha_diplomas);
                if (entregue != NULL) {
                    printf("Diploma entregue ao aluno: %s\n", entregue->nome);
                    free(entregue);
                }
                break;
            }
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    while(fila_diplomas.topo != NULL) {
        Diploma *temp = desenfileirar(&fila_diplomas);
        free(temp);
    }
    while(pilha_diplomas.topo != NULL) {
        Diploma *temp = desempilhar(&pilha_diplomas);
        free(temp);
    }

    return 0;
}