#ifndef DIPLOMAS_H
#define DIPLOMAS_H

typedef struct diploma {
    int id;
    char nome[100];
    char curso[50];
    char data_conclusao[12];
    int prazo_limite_dias;
    struct diploma *prox;
} Diploma;

typedef struct fila {
    Diploma *topo;
    Diploma *base;
} Fila;

typedef struct pilha {
    Diploma *topo;
} Pilha;

Diploma *criar(int id);
void enfileirar(Diploma *diploma, Fila *fila);
Diploma *desenfileirar(Fila *fila);
void listar_fila(Fila *fila);
void empilhar(Pilha *pilha, Diploma *diploma);
Diploma *desempilhar(Pilha *pilha);
void listar_pilha(Pilha *pilha);

void listar_por_curso_fila(Fila *fila, const char *curso);
void listar_por_curso_pilha(Pilha *pilha, const char *curso);
void buscar_por_nome_fila(Fila *fila, const char *nome);
void buscar_por_nome_pilha(Pilha *pilha, const char *nome);
void listar_urgencia_fila(Fila *fila);
void listar_urgencia_pilha(Pilha *pilha);

int calcular_dias_restantes(const char *data_conclusao, int prazo_limite_dias);

#endif