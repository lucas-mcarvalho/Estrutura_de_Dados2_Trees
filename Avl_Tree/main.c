#include<stdio.h>
#include"avl.h"
int main(){

    Bintree *bin = bin_create();


    int vet[] = {1,2,3,4,5,6,7,8,9,10};

    for(int i=0;i<10;i++){

            avl_insert(bin,vet[i]);
    }
    return 0;
}