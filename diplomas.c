#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diplomas.h"

Diploma *criar(int id){
    Diploma *diploma = (Diploma *)malloc(sizeof(Diploma));
    diploma->prox = NULL;
    diploma->id = id;

    printf("Insira os dados para a criação:\n");

    printf("Nome do aluno: ");
    fgets(diploma->nome, 100, stdin);
    diploma->nome[strcspn(diploma->nome, "\n")] = 0;

    printf("Curso: ");
    fgets(diploma->curso, 50, stdin);
    diploma->curso[strcspn(diploma->curso, "\n")] = 0;

    printf("Data de conclusão (DD/MM/AAAA): ");
    fgets(diploma->data_conclusao, 11, stdin);
    diploma->data_conclusao[strcspn(diploma->data_conclusao, "\n")] = 0;

    printf("Prazo limite para retirada (DD/MM/AAAA): ");
    fgets(diploma->prazo, 11, stdin);
    diploma->prazo[strcspn(diploma->prazo, "\n")] = 0;

    printf("Diploma adicionado à fila!\n");
    return diploma;
}

void enfileirar(Diploma *diploma, Fila *fila){
    if(fila->base == NULL){
        fila->base = diploma;
        fila->topo = diploma;
    }
    else{
        fila->base->prox = diploma;
        fila->base = diploma;
    }
}

Diploma* desenfileirar(Fila* fila) {
    if (fila->topo == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }
    Diploma *temp = fila->topo;
    fila->topo = fila->topo->prox;

    if (fila->topo == NULL) {
        fila->base = NULL;
    }
    temp->prox = NULL;
    return temp;
}

void listar_fila(Fila *fila){
    if(fila->base == NULL){
        printf("Não há diplomas a serem exibidos.");
        return;
    }

    Diploma *aux = fila->topo;
    printf("=== Diplomas na Fila (Prontos para retirada) ===\n");
    while(aux != NULL){
        printf("ID:%d | Nome: %s | Curso: %s | Data de conclusão: %s | Prazo para retirada: %s", aux->id, aux->nome, aux->curso, aux->data_conclusao, aux->prazo);
        aux = aux->prox;
    }
}

void empilhar(Pilha *pilha, Diploma *diploma) {
    diploma->prox = pilha->topo;
    pilha->topo = diploma;
}

Diploma *desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    Diploma *temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    temp->prox = NULL;
    return temp;
}

void listar_pilha(Pilha *pilha) {
    Diploma* aux = pilha->topo;
    printf("=== Diplomas na Pilha (Separados para entrega) ===\n");
    while(aux != NULL) {
       printf("ID: %d | Nome: %s | Curso: %s\n", aux->id, aux->nome, aux->curso);
       aux = aux->prox; 
    }
}