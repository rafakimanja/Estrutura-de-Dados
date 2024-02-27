#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int topo;
    int vetor[10];
}pilha;

pilha criaPilha(){
    pilha *p = (pilha*) malloc(sizeof (pilha));
    p->topo = -1;
    return *p;
}

void push(pilha *p, int num){
    (p->topo)++;
    p->vetor[p->topo] = num;
}

int pop(pilha *p){
   int valor = p->vetor[p->topo];
    (p->topo)--;

    return valor;
}

int empty(pilha pilha1){
    return 0;
}

int full(pilha pilha1){
    return 0;
}

void checaPilha(pilha *p){
    for (int i = 0; i <= p->topo; i++)
        printf("\nPosicao: %d | Valor: %d", i, p->vetor[i]);
}