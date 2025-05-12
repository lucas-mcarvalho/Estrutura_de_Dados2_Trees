#ifndef avl_H
#define avl_H

typedef struct no{
    int key;
    int height;
    struct no *left,*right,*p;
}TNo;

typedef struct {
    TNo *root;
}Bintree;

Bintree *bin_create();

bool bin_insert(Bintree*,int);

int height(TNo *);

int max(int a,int b);

void updateHeight(TNo*);

int getBalance(TNo*);

TNo *rotateRight(TNo*);

TNo *rotateLeft(TNo*);

TNo *avl_insert_rec(TNo*,int,TNo*,bool *);

bool avl_insert(Bintree*,int);

#endif