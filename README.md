# Sistema de Gerenciamento de Entrega de Diplomas (Fila e Pilha) — Projeto em C

## Descrição

Este projeto simula o gerenciamento de entrega de diplomas em uma instituição de ensino, utilizando as estruturas de dados **fila** e **pilha** em linguagem C.

O objetivo é gerenciar o fluxo de diplomas prontos para retirada, separar para o balcão e entregar ao aluno, modelando operações reais de forma didática.

---

## Motivação

Em universidades e faculdades, após a confecção, os diplomas ficam aguardando retirada pelos alunos. Porém, muitas vezes há confusão na ordem de retirada, atraso ou extravio.  

Com este sistema, é possível:

- Controlar **quais diplomas estão prontos**, em ordem de chegada (Fila — FIFO).
- Controlar **quais diplomas foram separados para entrega**, seguindo a lógica de empilhamento físico no balcão (Pilha — LIFO).
- Garantir organização e rastreabilidade de forma simples.

---

## Estruturas de dados utilizadas

### Fila

- Guarda todos os diplomas prontos aguardando retirada.
- Segue o princípio FIFO (First In, First Out).
- Operações: `enfileirar`, `desenfileirar`, `mostrar`.

### Pilha

- Guarda diplomas já separados para entrega imediata no balcão.
- Segue o princípio LIFO (Last In, First Out).
- Operações: `empilhar`, `desempilhar`, `mostrar`.

---

## Fluxo geral

1️⃣ **Cadastrar diploma**  
O diploma é inserido na **fila** de prontos para retirada.

2️⃣ **Separar para entrega**  
O diploma mais antigo (frente da fila) é removido e **empilhado** na pilha de entrega.

3️⃣ **Entregar diploma**  
O diploma do topo da pilha é entregue ao aluno e removido do sistema.

---

## Requisitos não funcionais (RNF)
**RNF01 — Implementação em linguagem C** 
O sistema deve ser desenvolvido em C, utilizando conceitos de alocação dinâmica (malloc/free), ponteiros e estruturas.

**RNF02 — Uso de estruturas de dados adequadas** 
- O sistema deve utilizar fila para armazenar diplomas prontos (FIFO).
- O sistema deve utilizar pilha para diplomas separados para entrega (LIFO).

**RNF03 — Simplicidade e eficiência** 
- O sistema deve ser leve, de fácil compilação, com execução rápida e consumo reduzido de memória.

**RNF04 — Interface textual** 
- O sistema deve oferecer uma interface de menu simples via terminal (console), sem interface gráfica.

**RNF05 — Modularidade** 
- O código deve ser organizado em funções separadas para cada operação (enfileirar, empilhar, mostrar, etc.), facilitando manutenção e entendimento.

**RNF06 — Segurança na alocação** 
- O sistema deve verificar sucesso de alocações dinâmicas (malloc) e informar erro caso não consiga.

---

## Requisitos funcionais (RF)

RF01 — Cadastrar diploma
**O sistema deve permitir cadastrar um diploma com: ID (automático), nome do aluno, curso, data de conclusão e prazo limite para retirada.**
- Ao cadastrar, o diploma deve ser adicionado à fila.

**RF02 — Visualizar fila de diplomas**
- O sistema deve listar todos os diplomas atualmente na fila, em ordem de chegada.

**RF03 — Separar diploma para entrega**
- O sistema deve permitir mover (desenfileirar) o diploma mais antigo da fila e empilhá-lo na pilha de separação para entrega.

**RF04 — Visualizar pilha de diplomas separados**
- O sistema deve exibir todos os diplomas atualmente na pilha, mostrando o topo como o próximo a ser entregue.

**RF05 — Entregar diploma**
- O sistema deve permitir entregar (desempilhar) o diploma no topo da pilha, removendo-o do sistema.
- Ao entregar, deve exibir informações do aluno.

---

## Funcionalidades implementadas

- Adicionar (enfileirar) diploma pronto para retirada.
- Visualizar diplomas na fila.
- Separar diploma para entrega (desenfileirar da fila e empilhar).
- Visualizar diplomas na pilha.
- Entregar diploma (desempilhar).
- Liberação de memória ao encerrar.

---

## Estrutura do código

### Arquivos

- `diplomas.h` — Código de cabeçalho que irá definir as estruturas e suas funções.
- `diplomas.c` — Código dos diplomas (implementa as structs, funções e menu).
- `main.c` — Código principal, onde serão chamadas as funções e menu.
- `README.md` — Documentação do projeto.

### Principais structs

```c
typedef struct Diploma {
    int id;
    char nome[100];
    char curso[100];
    char data_conclusao[11];
    char prazo_limite[11];
    struct Diploma* prox;
} Diploma;

typedef struct {
    Diploma* frente;
    Diploma* tras;
} Fila;

typedef struct {
    Diploma* topo;
} Pilha;


### Documentação utilizada
- [Como criar um arquivo de criação](https://embarcados.com.br/introducao-ao-makefile/)
- [Biblioteca time](https://petbcc.ufscar.br/time/)
- [Descobrir valor de dias entre duas datas](https://www.geeksforgeeks.org/dsa/find-number-of-days-between-two-given-dates/)
- [Calcular diferença entre duas datas](https://cboard.cprogramming.com/c-programming/167085-calculating-difference-between-two-dates.html)
- [Como realizar a validação do formato de uma string sem RegEx](https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm)