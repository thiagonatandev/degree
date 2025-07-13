#ifndef DIPLOMAS_H
#define DIPLOMAS_H

typedef struct diploma{
    int id;
    char nome[100];
    char curso[50];
    char data_conclusao[12];
    char prazo[12];
    struct diploma *prox;
}Diploma;

typedef struct fila{
    Diploma *topo;
    Diploma *base;
}Fila;

typedef struct pilha{
    Diploma *topo;
}Pilha;

Diploma *criar(int id);
void enfileirar(Diploma *diploma, Fila *fila);
Diploma *desenfileirar(Fila *fila);
void listar_fila(Fila *fila);
void empilhar(Pilha *pilha, Diploma *diploma);
Diploma *desempilhar(Pilha *pilha);
void listar_pilha(Pilha *pilha);

#endif