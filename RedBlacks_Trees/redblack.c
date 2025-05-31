#include<stdio.h>
#include<stdbool.h>
#include"redblack.h"
#include<stdlib.h>

//ALOCANDO A MEMORIA PRA CRIAR UM NO
redblack *create(TNo *no, int key){
    TNo *novo = malloc(sizeof(TNo));
    redblack *tree = malloc(sizeof(redblack));
    if(tree && novo){
        novo->color = "red";
        novo->key = key;
        novo->p = tree->nill;
        novo->left = tree->nill;
        novo->right = tree->nill;
        tree->root = tree->nill;
       
    }
    return tree;
}
void *rotate_left(redblack *tree,TNo *no){
    //CRIANDO UMA VARIAVEL AXILIAR
    TNo *y = no->right;
    
    //APONTAMOS PARA A ESQUERDA DE Y
    no->right = y->left;
    //SE NAO FOR UMA FOLHA
    if(y->left != tree->nill){
        //ATUALIZAMOS O PAI PARA O NOVO NO
        y->left->p = no;
    }
    //O PAI DE Y AGORA SERA O PAI DE X  
    y->p = no->p;
   
   //SE FOR A RAIZ DA ARVORE ,ENTAO SO ATUALIZAMOS PRA NOVA RAIZ 
    if(no->p == tree->nill){
        no->p = tree;
    }
    //SE FOR O FILHO ESQUERDO  DO PAI ATUALIZAMOS A ESQUERDA  
    else if(no == no->p->left){
            no->p = y;     
    }
    //SE FOR O FILHO DA DIREITA ATUALIZAMOS A DIREITA
    else{
        no->right = y;
    }
    //X VAI PRA ESQUERDA ,E ATUALIZAMOS O NO
    y->left = no;
    //AGORA ATUALIZAMOS O PAI
    no->p = y;
    
}


//MESMA ROTAÇÃO ,SO MUDA O SENTIDO ,AGORA É PRA DIREITA
void *rotate_right(redblack *tree,TNo* no){
   TNo *y = no->left;
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

bool black_insert_fix_Up(redblack *tree,TNo *z){
          while (z->p->color == red) {
        if (z->p == z->p->p->left) {  // pai de z é filho à esquerda
            TNo *tio = z->p->p->right;
            if (tio->color == red) {
                // Caso 1: tio é vermelho
                z->p->color = black;
                tio->color = black;
                z->p->p->color = red;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    // Caso 2: z é filho à direita -> rotaciona para alinhar
                    z = z->p;
                    rotate_left(tree, z);
                }
                // Caso 3: z é filho à esquerda -> rotação para corrigir
                z->p->color = black;
                z->p->p->color = red;
                rotate_right(tree, z->p->p);
            }
        } else {
            // espelho: pai de z é filho à direita
            TNo *tio = z->p->p->left;
            if (tio->color == red) {
                // Caso 1 (espelho)
                z->p->color = black;
                tio->color = black;
                z->p->p->color = red;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    // Caso 2 (espelho)
                    z = z->p;
                    rotate_right(tree, z);
                }
                // Caso 3 (espelho)
                z->p->color = black;
                z->p->p->color = red;
                rotate_left(tree, z->p->p);
            }
        }
    }

    tree->root->color = black;
}


//INSERÇÃO É IGUAL A ÁRVORE BINÁRIA DE BUSCA .
bool rb_insert(redblack *no,int key){
    TNo *novo = create(novo,key)
    if(novo == NULL) return false;
    TNo *x = no->root ,*y = NULL;
    while(x!= no->nill){
        y = x;
        if(key < x->key){
            x = x->left;
        }else{
             x = x->right;
        }
    }
    novo->p = y->p;
    if(key < y->key){
        y->left = novo;
    }else{
        y->right = novo;
    }

    black_insert_fix_Up(no,key);
    return true;
    
}