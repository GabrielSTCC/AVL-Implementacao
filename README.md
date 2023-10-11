# AVL-Implementacao
Implementação da AVL

# Árvore AVL em C

Este é um projeto de implementação de uma Árvore AVL em C. Uma Árvore AVL é uma árvore binária de busca balanceada que mantém seu fator de balanceamento em ±1, 
garantindo operações eficientes de inserção, exclusão e pesquisa.

## Conteúdo

1. [Visão Geral](#visão-geral)
2. [Requisitos](#requisitos)
3. [Compilação](#compilação)
4. [Execução](#execução)
5. [Exemplo de Uso](#exemplo-de-uso)
6. [Contribuições](#contribuições)
7. [Licença](#licença)

## Visão Geral

Este projeto consiste em uma implementação de uma Árvore AVL com operações de inserção e exclusão, 
juntamente com funções para verificar se a árvore permanece balanceada. 
O código foi projetado para permitir que você crie e teste árvores AVL com elementos inteiros.

## Requisitos

- Compilador C (por exemplo, GCC)
- Sistema operacional compatível com GCC

## Compilação

Você pode compilar o código utilizando o GCC ou outro compilador C compatível. No diretório onde você tem o arquivo `main.c`, execute o seguinte comando:

```shell
gcc main.c -o arvore_avl

Isso gerará um executável chamado arvore_avl.

Execução
Para executar o programa, basta digitar o seguinte comando:
./arvore_avl

Exemplo de Uso
O programa testa a funcionalidade da árvore AVL, criando várias árvores com números inteiros aleatórios
e verificando se elas permanecem balanceadas após operações de inserção e exclusão.

void testarAVL() {
    // Código para testar a funcionalidade da Árvore AVL
    // ...
}

int main() {
    testarAVL();
    return 0;
}


