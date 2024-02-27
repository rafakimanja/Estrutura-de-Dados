#include "pilha.h"
#include "stdio.h"
int main(){

    pilha minhaPilha = criaPilha();

    push(&minhaPilha, 23);
    push(&minhaPilha, 81);
    checaPilha(&minhaPilha);
    printf("\nValor %d removido",pop(&minhaPilha));
    checaPilha(&minhaPilha);

    return 0;
}