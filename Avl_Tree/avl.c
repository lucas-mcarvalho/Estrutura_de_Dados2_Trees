#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"avl.h"

TNo *createNfill(int key){
    TNo *novo = malloc(sizeof(TNo));
    if(novo){
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
        novo->height  = 0;
    }
    return novo;
}

Bintree *bin_create(){
    Bintree *bin = malloc(sizeof(Bintree));
    if(bin){
        bin->root =NULL;
    }
    return bin;
}

//RETORNA A ALTURA DE UM NO
int height(TNo *y){
    if(y == NULL) return -1;
    else{
        return y->height;
    }
}
//VERIFICA QUAL VALOR E MAIO ,PARA A FUNCAO DE ALTURA
int max(int a,int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

void updateHeight(TNo *y){
    if(y){
        /*
        FAZEMOS A CHAMADA DA FUNCAO HEIGHT PRA RETORNAR AS ALTURAS E DEPOIS SOMAMOS E COLOCAMOS
        NA FUNCAO MAX PARA RETORNAR A MAIOR ALTURA, QUE INDICA ALTURA DA ARVORE.
        */
        y->height = 1+(max(height(y->left),height(y->right)));
    }
}

//FUNCAO QUE VERIFICA O BALANCEAMENTO
int getBalance(TNo *no){
     if(no == NULL) return -1;
     //CRIAMOS DUAS VARIAVEIS PARA ARMAZENAR ALTURA ESQUERDA E DIREITA
     int heightRight = 0, leftHeight = 0;

     //SE EXISTIR NO ESQUERDO ,ENTAO COLOCAMOS O VALOR DA ALTURA NA VARIAVEL QUE CRIAMOS
     if(no->left !=NULL){
        leftHeight = no->left->height;
     }
     //SE EXISTIR NO DIREITO ,ENTAO COLOCAMOS O VALOR NA VARIAVEL QUE CRIAMOS
     if(no->right !=NULL){
        heightRight = no->right->height;
     }
     //AQUI CALCULAMOS O BALANCEAMENTO
   return leftHeight - heightRight;
}


//ROTACAO PARA A DIREITA
TNo *rotateRight(TNo *y){
    TNo *x = y->left;
    TNo *t2 = x->right;

    //ROTACAO
    x->right = y;
    y->left = t2;

    updateHeight(y);
    updateHeight(x);

    return x;
}
//ROTACAO PARA A ESQUERDA
TNo *rotateLeft(TNo *y){
    TNo *x = y->right;
    TNo *t2 = x->left;

    //Rotacioanando
    x->left = y;
    y->right = t2;

    updateHeight(x);
    updateHeight(y);
    
    return y;
}
//FUNCAO RECURSIVA DE INSERCAO
TNo *avl_insert_rec(TNo *raiz,int key,TNo *parent,bool *ok){
    //SE ELA NAO APONTAR PRA NADA ,FOR O PRIMEIRO ELEMENTO , ENTAO
    if(raiz == NULL){
        TNo *novo = createNfill(key);
        //ATUALIZAMOS O PAI
        novo->p = parent;
        *ok = true;
        return novo;
    }
    //SE A CHAVE FOR MENOR QUE O NO ENTAO CHAMAMOS A FUNCAO RECURSIVA PRA ESQUERDA
    if(key < raiz->key){
        raiz->left = avl_insert_rec(raiz->left,key,parent,ok);
    }
    //SENAO PRA DIREITA
    else if(key > raiz->key){
        raiz->right = avl_insert_rec(raiz->right,key,parent,ok);
    }
    //SE ELA NAO FOR MENOR OU IGUAL SIGNIFICA QUE ELA E IGUAL ,ENTAO NAO INSIRO ,PRA NAO SER DUPLICADO
    //DUPLICACAO
    else{
        *ok = false;
        return raiz;
    }


    //ATUALIZANDO SUA ALTURA
    updateHeight(raiz);

    //VERIFICANDO O FATOR DE BALANCEAMENTO
    int balance = getBalance(raiz);

    //SE O FATOR FOR >1 E A CHAVE FOR NA ESQUERDA ,ENTAO ROTACAO SIMPLES A ESQUERDA
    if(balance > 1 && key < raiz->left->key){
        return rotateRight(raiz);
    }
    //SE FOR MENOR QUE -1 ,ENTAO ROTACAO SIMPLES A DIREITA
    if(balance < -1 && key> raiz->right->key){
        return rotateLeft(raiz);
    }
    //SE FOR MAIOR QUE 1 E A CHAVE FOR INSERIDA NA ESQUERDA ,ROTACAO DUPLA A ESQUERDA 
    if(balance >1 && key> raiz->left->key){
        raiz->left = rotateLeft(raiz);
        return rotateRight(raiz);
    }
    //SENAO ROTACAO DUPLA A DIREITA
    if(balance < -1 && key  > raiz->right->key){
        raiz->right = rotateRight(raiz);
        return rotateLeft(raiz);
    }
    //SE ESTIVER BALANCEADA RETORNA A RAIZ
    return raiz;

}   

bool avl_insert(Bintree *bin,int key){
    if(bin == NULL) return false;
    bool ok = false;
    bin->root = avl_insert_rec(bin->root,key,NULL,&ok);
    return ok;   
}