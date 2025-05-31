#ifndef redblack_H
#define redblack_H

#include<stdbool.h>

typedef struct no {
    int key;
    struct no *left,*right,*p;
    char color[10];
}TNo;

typedef struct redblack{
    TNo *root;
    TNo *nill;
}redblack;


redblack *create(TNo*,int);

void *rotate_left(redblack*,TNo*);

void *rotate_right(redblack*,TNo*);

bool black_insert_fix_Up(redblack*,TNo*);

void rb_insert(redblack*,int);

#endif