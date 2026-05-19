// 01 - c
// 02 - b
// 03 - c
// 04 - c
// 05 - b
// 06 - a
// 07 - d
// 08 - a
// 09 - Uma árvore é uma estutura feita para organizar dados/arquivos de uma maneira que não seja necessário passar por todos os dados fazendo com que a complexidade seja O(n), a árvore reduz muito os elementos que são necessários a serem percorridos!
// 10 - Nó raiz, primeiro nó da árvore, não tem pai. Nó folha: Nó que não tem filhos. Nó interno: Está entre a raiz e as folhas, tem pai e filho.
// 11 - Ancestral(is) São aqueles que estão numa altura mais alta que o nó atual (pais) Descendente(s) são aqueles que vêm após o nó atual (filhos).
// 12 - A profundidade é a mesma coisa da altura do nó, é a quantidade de ligações do nó até a raiz.
// 13 - O grau de um nó é a quantidade específica de filhos daquele nó específico, o grau de uma árvore seria a quantidade máxima de filhos que um nó dessa árvore tem, ex: Se um nó dessa árvore tem 3 filho o grau dela é grau 3.
// 14 - A árvore é importantíssima principalmente em sistemas grandes pois a forma como ela é organizada reduz muito a complexidade e consequentemente o tempo para achar um elemnto específico pois ela descarta toda uma subárvore a cada comparação.
// 15 -  5
//      /  \ 
//      2   6
//     /\   /\ 
//    1 3   4 7
//             \ 
//              8
// folhas: uma(8) altura:3 grau: 2
// 16:

def struct No{
    int dado;
    struct No *direita;
    struct No *esquerda;
} No;