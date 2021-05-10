#include <stdio.h>
#include "list.h"
#include <stdlib.h>
//单链表创建
//单链表
int main( ){
    struct node *p=(struct node *)malloc(1*sizeof(struct node));
    struct node listA;
    if(p){
        printf("success\n");
    }else{
        printf("failure\n");
    }
    int dd[]={1,2,3,4,5};
    listA.next = p;
    for(int i=0;i<5;i++){
        struct node *q=(struct node *)malloc(1*sizeof(struct node));
        p->data=dd[i];
        p->next=q;
        p=q;
    }
    p=listA.next;
    for(int i=0;i<5;i++){
       
       printf("%d\n",p->data);
       p=p->next;
       
    }
   
    return 0;

}