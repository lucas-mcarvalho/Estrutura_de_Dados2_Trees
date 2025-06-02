#ifndef redblack_H
#define redblack_H

#include<stdbool.h>


typedef enum { 
    red, black 
} Color;



typedef struct no {
    int key;
    struct no *left,*right,*p;
    Color color;
}TNo;

typedef struct redblack{
    TNo *root;
    TNo *nill;
}redblack;


redblack *create();

void *rotate_left(redblack*,TNo*);

void *rotate_right(redblack*,TNo*);

bool black_insert_fix_Up(redblack*,TNo*);

bool rb_insert(redblack*,int);

#endif