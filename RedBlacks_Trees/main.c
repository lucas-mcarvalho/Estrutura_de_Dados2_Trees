#include"redblack.h"
#include<stdio.h>


int main(){

redblack *rb = create();

rb_insert(rb,41);
rb_insert(rb,38);
rb_insert(rb,12);
rb_insert(rb,19);
rb_insert(rb,8);


print_rbtree(rb->root,rb->nill);

TNo *remove = rb_search(rb->root,rb->nill,8);

if(remove!= rb->nill){
    rb_remove(rb,remove);
}else{
    printf("Chave nao encontrada pra remocao!");
}
printf("\n");
print_rbtree(rb->root,rb->nill);
    return 0;
}