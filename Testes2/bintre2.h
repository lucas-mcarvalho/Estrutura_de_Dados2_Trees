#ifndef bintre2_H
#define bintre2_H
#include<stdbool.h>

typedef struct _no{
    int key;
    struct _no *left,*right,*p;
}TNo;

typedef struct {
    TNo *root;
}BinTree;

BinTree *bin_create();

bool insert(BinTree*,int);

bool pre_order(TNo*);

bool in_order(TNo*);

bool pos_order(TNo*);

TNo* search(TNo*,int);

TNo* search_r(TNo*,int);

TNo* tree_minimun(TNo*);

TNo* tree_max(TNo*);

void transplant(BinTree*,TNo*,TNo*);

bool bin_remove(BinTree*,int);

#endif