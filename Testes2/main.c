#include"bintre2.h"
#include<stdio.h>

int main(){

   BinTree *tree = bin_create();

    insert(tree,10);
    insert(tree,1);
    insert(tree,2);
    insert(tree,3);
    insert(tree,11);
    
    TNo *min,*max;
  
   bin_remove(tree,11);
   bin_remove(tree,1);    

   max = tree_max(tree->root);
   printf("%d",max->key);

   printf("\n");
   min = tree_minimun(tree->root);
   printf("%d",min->key);
    return 0;
}