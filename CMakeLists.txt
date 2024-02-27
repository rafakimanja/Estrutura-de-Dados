cmake_minimum_required(VERSION 3.26)
project(Estrutura_de_Dados C)

set(CMAKE_C_STANDARD 11)

include_directories(Pilhas/Exercicios)

add_executable(Estrutura_de_Dados
        Pilhas/Exercicios/exe1.c
        Pilhas/Exercicios/pilha.c
        Pilhas/Exercicios/pilha.h)
