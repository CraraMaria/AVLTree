#ifndef TADAVL_H
#define TADAVL_H

typedef struct avltree AVLTree;
int balancingFactor(AVLTree *);
unsigned int height(AVLTree *avltree);
AVLTree *rotateLeft(AVLTree *avltree);
AVLTree *rotateRight(AVLTree *avltree);
AVLTree *insertNode(AVLTree *avltree, int dado);
AVLTree *deleteNode(AVLTree *avltree, int dado);
// exibir
void preOrder(AVLTree *avltree);
void inOrder(AVLTree *avltree);
void posOrder(AVLTree *avltree);

#endif

