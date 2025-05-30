#include<stdio.h>
#include<stdbool.h>
#include"redblack.h"




redblack *create(TNo *no, int key){
    TNo *novo = malloc(sizeof(TNo));
    redblack *tree = malloc(sizeof(redblack));
    if(tree && novo){
        novo->color = red;
        novo->key = key;
        novo->p = tree->nill;
        novo->left = tree->nill;
        novo->right = tree->nill;
        tree->root = tree->nill;
       
    }
    return tree;
}
void *rotate_left(redblack *tree,TNo *no){

    TNo *y = no->right;
    no->right = y->left;
    if(y->left != tree->nill){
        y->left->p = no;
    }
    y->p = no->p;
   
    if(no->p == tree->nill){
        no->p = tree;
    }
    else if(no == no->p->left){
            no->p = y;     
    }
    else{
        no->right = y;
    }
    y->left = no;
    no->p = y;
    
}

void *rotate_right(redblack *tree,TNo* no){
   TNo *y = no->right;
   no->right = y->left;

   if(y->left != tree->nill){
        y->left->p = no;
   }
   y->p = no->p;
   //SE FOR A RAIZ DA ARVORE 
   if(y->p == tree->nill){
    no->p = tree;
   }
  else{
    no->right = y;
   }
   y->left = no;
   no->p = y;
}

bool black_insert_fix_Up(redblack*,int*);

void rb_insert(redblack*,int);