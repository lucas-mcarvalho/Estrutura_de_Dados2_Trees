#include<stdio.h>
#include<stdbool.h>
#include"redblack.h"
#include<stdlib.h>



TNo *createNfill(int info){
    TNo *novo = malloc(sizeof(TNo));
    if(novo){
        novo->color = black;
        novo->key = info;
    }
    return novo;
}

//ALOCANDO A MEMORIA PRA CRIAR UM NO
redblack *create(){
    redblack *tree = malloc(sizeof(redblack));
    if(tree){
        tree->nill = malloc(sizeof(TNo));
        tree->nill->color = black;
        tree->nill->left = tree->nill->right = tree->nill->p = NULL;
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
       tree->root = y;
    }
    //SE FOR O FILHO ESQUERDO  DO PAI ATUALIZAMOS A ESQUERDA  
    else if(no == no->p->left){
        no->p->left = y;     
    }
    //SE FOR O FILHO DA DIREITA ATUALIZAMOS A DIREITA
    else{
       no->p->right = y;
    }
    //X VAI PRA ESQUERDA ,E ATUALIZAMOS O NO
    y->left = no;
    //AGORA ATUALIZAMOS O PAI
    no->p = y;
    
}


//MESMA ROTAÇÃO ,SO MUDA O SENTIDO ,AGORA É PRA DIREITA
void *rotate_right(redblack *tree,TNo* no){
   TNo *y = no->left;
   no->left = y->right;

   if(y->right != tree->nill){
        y->right->p = no;
   }
   y->p = no->p;
   //SE FOR A RAIZ DA ARVORE 
   if(y->p == tree->nill){
    tree->root = y;
   }
  else if (no == no->p->right){
    no->p->right = y;
   }else{
    no->p->left = y;
   }
   y->right = no;
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
    TNo *novo = createNfill(key);
    
    novo->left = no->nill;
    novo->right = no->nill;
    novo->color = red;

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
    novo->p =y;
    if(y == no->nill){
        no->root = novo;
    }
    if(key < y->key){
        y->left = novo;
    }else{
        y->right = novo;
    }

    black_insert_fix_Up(no,novo);
    return true;
    
}