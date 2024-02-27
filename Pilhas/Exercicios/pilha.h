#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int topo;
    int vetor[10];
} pilha;

pilha criaPilha();
void push(pilha *p, int num);
int pop(pilha *p);
void checaPilha(pilha *p);
#endif // PILHA_H
