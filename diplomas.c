#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    fgets(diploma->data_conclusao, 12, stdin);
    diploma->data_conclusao[strcspn(diploma->data_conclusao, "\n")] = 0;

    printf("Prazo limite para retirada em dias: ");
    scanf("%d", &diploma->prazo_limite_dias);
    getchar();

    printf("Diploma adicionado à fila!\n");
    return diploma;
}

void enfileirar(Diploma *diploma, Fila *fila){
    if(fila->base == NULL){
        fila->base = diploma;
        fila->topo = diploma;
    } else {
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
    if(fila->topo == NULL){
        printf("Não há diplomas a serem exibidos.\n");
        return;
    }

    Diploma *aux = fila->topo;
    printf("=== Diplomas na Fila (Prontos para retirada) ===\n");
    while(aux != NULL){
        printf("ID:%d | Nome: %s | Curso: %s | Data conclusão: %s | Prazo (dias): %d\n", 
               aux->id, aux->nome, aux->curso, aux->data_conclusao, aux->prazo_limite_dias);
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
       printf("ID: %d | Nome: %s | Curso: %s | Data conclusão: %s | Prazo (dias): %d\n", 
              aux->id, aux->nome, aux->curso, aux->data_conclusao, aux->prazo_limite_dias);
       aux = aux->prox; 
    }
}

void listar_por_curso_fila(Fila *fila, const char *curso) {
    Diploma *aux = fila->topo;
    int pos = 1, encontrado = 0;
    while(aux != NULL) {
        if (strcmp(aux->curso, curso) == 0) {
            printf("Fila - Posição %d: %s\n", pos, aux->nome);
            encontrado = 1;
        }
        aux = aux->prox;
        pos++;
    }
    if (!encontrado) printf("Nenhum diploma encontrado na fila para o curso %s.\n", curso);
}

void listar_por_curso_pilha(Pilha *pilha, const char *curso) {
    Diploma *aux = pilha->topo;
    int pos = 1, encontrado = 0;
    while(aux != NULL) {
        if (strcmp(aux->curso, curso) == 0) {
            printf("Pilha - Posição %d: %s\n", pos, aux->nome);
            encontrado = 1;
        }
        aux = aux->prox;
        pos++;
    }
    if (!encontrado) printf("Nenhum diploma encontrado na pilha para o curso %s.\n", curso);
}

void buscar_por_nome_fila(Fila *fila, const char *nome) {
    Diploma *aux = fila->topo;
    int pos = 1, encontrado = 0;
    while(aux != NULL) {
        if (strstr(aux->nome, nome) != NULL) {
            printf("Fila - Posição %d: %s\n", pos, aux->nome);
            encontrado = 1;
        }
        aux = aux->prox;
        pos++;
    }
    if (!encontrado) printf("Nenhum diploma com nome parecido encontrado na fila.\n");
}

void buscar_por_nome_pilha(Pilha *pilha, const char *nome) {
    Diploma *aux = pilha->topo;
    int pos = 1, encontrado = 0;
    while(aux != NULL) {
        if (strstr(aux->nome, nome) != NULL) {
            printf("Pilha - Posição %d: %s\n", pos, aux->nome);
            encontrado = 1;
        }
        aux = aux->prox;
        pos++;
    }
    if (!encontrado) printf("Nenhum diploma com nome parecido encontrado na pilha.\n");
}

int calcular_dias_restantes(const char *data_conclusao, int prazo_dias) {
    struct tm dt = {0};
    int dia, mes, ano;

    if (sscanf(data_conclusao, "%d/%d/%d", &dia, &mes, &ano) != 3) return -1;

    dt.tm_mday = dia;
    dt.tm_mon = mes - 1;
    dt.tm_year = ano - 1900;
    time_t t_conclusao = mktime(&dt);
    if (t_conclusao == -1) return -1;

    time_t t_limite = t_conclusao + (prazo_dias * 24 * 3600);
    time_t agora = time(NULL);

    int dias = (int)((t_limite - agora) / (24 * 3600));
    return dias;
}

void listar_urgencia_fila(Fila *fila) {
    int count = 0;
    Diploma *aux = fila->topo;

    while(aux != NULL) {
        count++;
        aux = aux->prox;
    }

    if(count == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Diploma **vetor = malloc(count * sizeof(Diploma *));
    aux = fila->topo;
    for(int i = 0; i < count; i++) {
        vetor[i] = aux;
        aux = aux->prox;
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            int dias_j = calcular_dias_restantes(vetor[j]->data_conclusao, vetor[j]->prazo_limite_dias);
            int dias_next = calcular_dias_restantes(vetor[j+1]->data_conclusao, vetor[j+1]->prazo_limite_dias);
            if(dias_j > dias_next) {
                Diploma *tmp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = tmp;
            }
        }
    }

    printf("=== Diplomas na Fila (ordenados por urgência) ===\n");
    for(int i = 0; i < count; i++) {
        int dias = calcular_dias_restantes(vetor[i]->data_conclusao, vetor[i]->prazo_limite_dias);
        printf("ID: %d | Nome: %s | Dias restantes: %d\n", vetor[i]->id, vetor[i]->nome, dias);
    }

    free(vetor);
}

void listar_urgencia_pilha(Pilha *pilha) {
    int count = 0;
    Diploma *aux = pilha->topo;

    while(aux != NULL) {
        count++;
        aux = aux->prox;
    }

    if(count == 0) {
        printf("Pilha vazia.\n");
        return;
    }

    Diploma **vetor = malloc(count * sizeof(Diploma *));
    aux = pilha->topo;
    for(int i = 0; i < count; i++) {
        vetor[i] = aux;
        aux = aux->prox;
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            int dias_j = calcular_dias_restantes(vetor[j]->data_conclusao, vetor[j]->prazo_limite_dias);
            int dias_next = calcular_dias_restantes(vetor[j+1]->data_conclusao, vetor[j+1]->prazo_limite_dias);
            if(dias_j > dias_next) {
                Diploma *tmp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = tmp;
            }
        }
    }

    printf("=== Diplomas na Pilha (ordenados por urgência) ===\n");
    for(int i = 0; i < count; i++) {
        int dias = calcular_dias_restantes(vetor[i]->data_conclusao, vetor[i]->prazo_limite_dias);
        printf("ID: %d | Nome: %s | Dias restantes: %d\n", vetor[i]->id, vetor[i]->nome, dias);
    }

    free(vetor);
}
