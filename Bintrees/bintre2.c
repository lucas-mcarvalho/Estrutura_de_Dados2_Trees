#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"bintre2.h"

TNo *createNfill(int key){
    TNo *novo = malloc(sizeof(TNo));
    if(novo){
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
    }
    return novo;
}
BinTree *bin_create(){
    BinTree *bin = malloc(sizeof(bin));
    if(bin){
        bin->root = NULL;
    }
    return bin;
}

bool insert(BinTree *bin,int info){
    TNo *novo = createNfill(info);
    if(novo == NULL)return false;
    TNo *x = bin->root , *y = NULL;
    while(x!=NULL){
        y = x;
        if(info <x->key){
            x = x->left;
        }else {
            x = x->right;
        }
    }
    novo->p = y;
    if(y ==NULL){
        bin->root = novo;
    }else if(info < y->key){
        y->left = novo;
    }else{
        y->right = novo;
    }
    return true;
}

TNo *search(TNo *novo,int key){
    while(novo!=NULL && key !=novo->key){
        printf("Estou em [%d]-> ",novo->key);
        if(key < novo->key){
            novo = novo->left;
        }else{
            novo = novo->right;
        }
    }
    return novo;
}

TNo *search_r(TNo *novo,int key){
    if(novo!=NULL && novo->key !=key){
        printf("Estou em [%d] ",novo->key);
        if(key< novo->key  ){
            search_r(novo->left,key);
        }else{
            search_r(novo->right,key);
        }
    }
    return novo;
}

bool pre_order(TNo* elemento){
    if(elemento!=NULL){
        printf("Estou em [%d]-> ",elemento->key);
        pre_order(elemento->left);
        pre_order(elemento->right);
    }
    return true;
}

bool in_order(TNo *elemento){
    if(elemento!=NULL){
        in_order(elemento->left);
        printf("Elemento [%d] ",elemento->key);
        in_order(elemento->right);
    }
    return true;
}

bool pos_order(TNo *elemento){
    if(elemento !=NULL){
        pos_order(elemento->left);
        pos_order(elemento->right);
        printf("Estou em [%d] ",elemento->key);
    }
    return true;
}
TNo* tree_minimun(TNo *no){
    while(no->left!=NULL){
        no = no->left;
    }
    return no;
}

TNo* tree_max(TNo *no){
    while(no->right!=NULL){
        no = no->right;
    }
  
    return no;
}


void transplant(BinTree *T,TNo *u,TNo *v){
    //SE U FOR A RAIZ ,PRIMEIRO CASO
    if(u == NULL){
        T->root = v;
    }
    //SE U FOR O FILHO DA ESQUERDA ,SEGUNDO CASO
    else if(u == u->p->left){
        u->p->left = v;
    }
    //SE U FOR O FILHO DA DIREITA ,TERCEIRO CASO
    else{
        u->p->right = v;
    }
    //ATUALIZANDO O PAI DE V
    if(v!=NULL){
        v->p = u->p;
    }
}


bool bin_remove(BinTree *bin,int key){
    //FAZENDO A BUSCA NA ARVORE
    TNo *z = search(bin->root,key);
    if(z == NULL) return false;
    
    //SE NAO TIVER FILHOS A ESQUERDA
    if(z->left == NULL){
        transplant(bin,z,z->right);
    }
    //SE NAO TIVER FILHOS A DIREITA
    else if(z->right ==NULL){
        transplant(bin,z,z->left);
    }
    //SE ELA TIVER DOIS FILHOS
    else {
        /*BUSCANDO O SUCESSOR DA VALOR A SER RETIRADO
        ,BUSCAMOS O SUCESSOR NA DIREITA,ELE E O MENOR VALOR DA DIREITA*/
        TNo *y = tree_minimun(bin->root);
        //ENCONTRANDO O SUCESSOR ,FAZEMOS O TRANSPLANT
        //COMO ELE E O MENOR VALOR DA ARVORE DIREITA ELE NAO TEM ESQUERDA
        //AQUI VERIFICAMOS SE ELE E O PRIMEIRO FILHO DIREITO
        if(z->p->right != y){
            //TIRAMOS O SUCESSOR E COLOCAMOS O VALOR DA DIREITA NO LUGAR ,CONECTANDO A ARVORE
            transplant(bin,y,y->right);
            //TROCAMOS A NOVA DIREITA DO SUCESSOR PARA A DIREITA DA RAIZ DA MINHA SUBARVORE
            y->right = z->p;
            if(y->right!=NULL){
                //ATUALIZANDO O PAI
                y->p = z->p;
            }
        }
        transplant(bin,z,y);
        y->left = z->left;
        if(y->left !=NULL){
            y->left->p = y->p;
        }
    }
    free(z);
    return true;
}