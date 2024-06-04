#include <stdio.h>
#include <stdlib.h>

#include "../includes/TADAVL.h"

struct avltree {
  AVLTree *esq;
  AVLTree *dir;
  int dado;
  void (*show)(AVLTree *avltree);
};

void exibir(AVLTree *avltree) {
  if (avltree)
    printf("(%d)", avltree->dado);
}

AVLTree *novaArvore(int dado) {
  AVLTree *raiz = malloc(sizeof(AVLTree));
  if (raiz) {
    raiz->dir = NULL;
    raiz->esq = NULL;
    raiz->dado = dado;
    raiz->show = exibir;
  }
  return raiz;
}

// a serem implementados
unsigned int height(AVLTree *avltree) {
  if (avltree == NULL)
    return 0;
  return height(avltree->dir) - height(avltree->esq);
}
int balancingFactor(AVLTree *avltree) {
  if (avltree == NULL)
    return 0;
  return height(avltree->dir) - height(avltree->esq);
}

AVLTree *rotateLeft(AVLTree *avltree) {
  AVLTree *aux = avltree->dir;
  avltree->esq = aux->dir;
  aux->dir = avltree;
  return aux;
}
//    AVLTree                   //
//       (1)
//      /   \
 //   (a)    (2)
//          / \
 //       (b)   (3)
// AVLTree *aux = avltree->dir; //
//       (1)
//      /
//   (a)
//   aux :  (2)
//          / \
 //       (b)   (3)
// avltree->dir = aux->esq;     //
//       (1)
//      /   \
 //   (a)    (b)
//   aux :  (2)
//            \
 //            (3)
//   aux->esq = avltree;        //
//          (2)
//         /   \
 //       (1)   (3)
//      /   \
 //   (a)    (b)

AVLTree *rotateRight(AVLTree *avltree) {
  AVLTree *aux = avltree->esq;
  avltree->esq = aux->esq;
  aux->esq = avltree;
  return aux;
}
//    AVLTree                   //
//       (1)
//      /   \
 //   (2)    (b)
//   /  \
 // (a)   (3)
// AVLTree *aux = avltree->esq; //
// AVLtree: (1)
//             \
 //             (b)
//  aux : (2)
//       /  \
 //     (a)   (3)
// avltree->esq = aux->esq;     //
// AVLtree: (1)
//          /  \
 //        (a)  (b)
//  aux : (2)
//          \
 //           (3)
//   aux->esq = avltree;        //
//  aux : (2)
//        / \
 //      (1)  (3)
//      / \
 //    (a) (b)

AVLTree *insertNode(AVLTree *avltree, int dado) {
  if (!avltree)
    return novaArvore(dado);
  // Se a árvore (avltree) é nula, cria-se uma nova árvore com o dado fornecido
  if (dado < avltree->dado)
    avltree->dir = insertNode(avltree->dir, dado);
  // Se o dado maior que o dado da raiz, insere-se o nó na subárvore à direita:
  else
    avltree->esq = insertNode(avltree->esq, dado);
  // Caso contrário, insere-se na subárvore à esquerda
  // O fator de balanceamento é calculado:
  int fb = balancingFactor(avltree);
  if (fb < 2 && fb > -2)
    return avltree;
  // Se o fator de balanceamento estiver dentro do intervalo [-2, 2], não é
  // necessário balancear Balanceamento: Se o fator de balanceamento for maior
  // ou igual a 2 (desequilíbrio à esquerda)
  if (fb >= 2) {
    if (avltree->esq->esq) {
      avltree = rotateRight(avltree);
      // Se a subárvore esquerda tem um filho à esquerda (avltree->esq->esq),
      // realiza uma rotação simples à direita
    } else {
      avltree->esq = rotateLeft(avltree->esq);
      avltree = rotateRight(avltree);
      // Caso contrário, realiza uma rotação dupla: primeiro à esquerda no filho
      // esquerdo, depois à direita no nó atual
    }
  } else { // fb <= -2
    // Se o fator de balanceamento for menor ou igual a -2 (desequilíbrio à
    // direita)
    if (avltree->dir->dir) {
      avltree = rotateLeft(avltree);
      // Se a subárvore direita tem um filho à direita (avltree->dir->dir),
      // realiza uma rotação simples à esquerda
    } else {
      avltree->dir = rotateRight(avltree->dir);
      avltree = rotateLeft(avltree);
      // Caso contrário, realiza uma rotação dupla: primeiro à direita no filho
      // direito, depois à esquerda no nó atual
    }
  }
  return avltree;
  // Após a inserção e balanceamento, a função retorna a árvore AVL
}

AVLTree *deleteNode(AVLTree *avltree, int dado) {
  if (avltree == NULL)
    return avltree;
  // Verificação de NULL
  // encontrar o nó a ser removido:
  // Se o dado é menor que o valor do nó atual (avltree->dado), a função é
  // chamada recursivamente na subárvore esquerda. Se o dado é maior, a função é
  // chamada recursivamente na subárvore direita.
  if (dado < avltree->dado)
    avltree->esq = deleteNode(avltree->esq, dado);
  else if (dado > avltree->dado)
    avltree->dir = deleteNode(avltree->dir, dado);
  // remoção do nó a ser encontrado
  else {
    // Caso 1: O nó a ser removido tem um ou nenhum filho:
    if ((avltree->esq == NULL) || (avltree->dir == NULL)) {
      AVLTree *temp = avltree->esq ? avltree->esq : avltree->dir;
      if (temp == NULL) {
        temp = avltree;
        avltree = NULL;
      } else
        *avltree = *temp;
      free(temp);
    } else {
      // Caso 2: O nó a ser removido tem dois filhos:
      AVLTree *temp = avltree->dir;
      while (temp->esq != NULL)
        temp = temp->esq;
      avltree->dado = temp->dado;
      avltree->dir = deleteNode(avltree->dir, temp->dado);
    }
  }
  // Verificar se a Árvore é NULL após a Remoção:
  if (avltree == NULL)
    return avltree;
  // Calcular o Fator de Balanceamento e Realizar Rotações se Necessário
  int balance = balancingFactor(avltree);
  // Desequilíbrio à esquerda (fator de balanceamento > 1)
  if (balance > 1 && balancingFactor(avltree->esq) >= 0)
    return rotateRight(avltree);
  // Se a subárvore esquerda está balanceada ou com desequilíbrio à esquerda,
  // realiza uma rotação simples à direita.
  if (balance > 1 && balancingFactor(avltree->esq) < 0) {
    avltree->esq = rotateLeft(avltree->esq);
    return rotateRight(avltree);
    // Se a subárvore esquerda tem um desequilíbrio à direita, realiza uma
    // rotação dupla (esquerda-direita).
  }
  // Desequilíbrio à direita (fator de balanceamento < -1)
  if (balance < -1 && balancingFactor(avltree->dir) <= 0)
    return rotateLeft(avltree);
  // Se a subárvore direita está balanceada ou com desequilíbrio à direita,
  // realiza uma rotação simples à esquerda.
  if (balance < -1 && balancingFactor(avltree->dir) > 0) {
    avltree->dir = rotateRight(avltree->dir);
    return rotateLeft(avltree);
    }
    // Se a subárvore direita tem um desequilíbrio à esquerda, realiza uma
    // rotação dupla (direita-esquerda).
    return avltree;
    // Retorna a Raiz Atualizada da Árvore
  }


  // exibir
  void preOrder(AVLTree * avltree);
  void inOrder(AVLTree * avltree);
  void posOrder(AVLTree * avltree);

  int main() {
    AVLTree *raiz = novaArvore(5);
    raiz->esq = novaArvore(3);
    raiz->dir = novaArvore(7);
    raiz->show(raiz);
    raiz->esq->show(raiz->esq);
    raiz->dir->show(raiz->dir);

    return 0;
  }
