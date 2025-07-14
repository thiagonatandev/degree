#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diplomas.h"

int menu() {
    int opcao;
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar diploma (enfileirar)\n");
    printf("2. Mostrar fila de diplomas\n");
    printf("3. Separar diploma para entrega (desenfileirar e empilhar)\n");
    printf("4. Mostrar pilha de diplomas separados\n");
    printf("5. Entregar diploma ao aluno (desempilhar)\n");
    printf("6. Listar diplomas de um curso (fila e pilha)\n");
    printf("7. Buscar diploma por nome (fila e pilha)\n");
    printf("8. Ver diplomas por urgência (fila e pilha)\n");
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
            case 6: {
                char curso[50];
                printf("Digite o curso: ");
                fgets(curso, 50, stdin);
                curso[strcspn(curso, "\n")] = 0;
                listar_por_curso_fila(&fila_diplomas, curso);
                listar_por_curso_pilha(&pilha_diplomas, curso);
                break;
            }
            case 7: {
                char nome[100];
                printf("Digite o nome ou parte: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;
                buscar_por_nome_fila(&fila_diplomas, nome);
                buscar_por_nome_pilha(&pilha_diplomas, nome);
                break;
            }
            case 8:
                listar_urgencia_fila(&fila_diplomas);
                listar_urgencia_pilha(&pilha_diplomas);
                break;
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