# AVL
Implementação de uma AVL, que é uma árvore binária de busca balanceada, ou seja, uma árvore balanceada (árvore completa). A implementação seguiu o livro (versão inglês) de Thomas H. Cormen.

IMPLEMENTAÇÕES
- Foi implementado as funções inserir e remover para a AVL.
- Foi implementado uma função que verifica se a árvore é AVL, fazendo o cálculo das alturas das subárvores de cada nó e verificando se o 'bal' de cada nó está realmente correto.
- Foi implementado uma função que conta a quantidade de nós de uma AVL.

TESTES
- Foram criadas 1.000 AVL's.
- Em cada AVL foi inserido aleatóriamente 10.000 nós com chave entre 0 e 100.000. Após as inserções, é verificado se a árvore é AVL pelo algoritmo de verificação.
- Em cada AVL foi removido 1.000 nós e verificado se haviam 9.000 nós. Após as remoções, é verificado se a árvore é AVL pelo algoritmo de verificação.

REFERÊNCIA DO LIVRO
- RIVEST, Ronald L.; LEISERSON, Charles E.; CORMEN, Thomas H.. Introduction to Algorithms. 3ª. Edição, 2009.
