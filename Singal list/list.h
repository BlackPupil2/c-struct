#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node{
    int data;
    struct node * next;
};
//创建单链表
struct node Createlist(int n){
    struct node List;
    int t1=n%10;
    struct node *p=(struct node *)malloc(1*sizeof(struct node));
    if(!p){
        printf("error");
    }
    struct node *q=(struct node *)malloc(1*sizeof(struct node));
    List.next=p;
    p->data=t1;
    p->next=q;
    p=q;
    int t=n/10;
    while(t!=0){
            p->data=t%10;
            struct node *q=(struct node *)malloc(1*sizeof(struct node));
            p->next=q;
            p=q;
            t=t/10;
        }
       p->next=NULL;
        return List;

}
//求单链表长度
int list_size(struct node List){
    int num=0;
    struct node *p=(struct node *)malloc(1*sizeof(struct node));
    p=List.next;
    while((p->next)){
        num=num+1;
        p=p->next;
    }
    return num;
}
//打印单链表
void list_print(struct node List){
    struct node *header=(struct node *)malloc(1*sizeof(struct node));
    header=List.next;
    int sum=0;
    for(int i=0;i<list_size(List);i++){
        int s=pow(10,i);
        sum=sum+(header->data)*s;

        header=header->next;
    }
    printf("%d\n",sum);
    
}
//求和
struct node listSum(struct node ListA, struct node ListB){
    struct node *p=(struct node *)malloc(1*sizeof(struct node));
    struct node *q=(struct node *)malloc(1*sizeof(struct node));
    p=ListA.next;
    q=ListB.next;
    int t;

    if(list_size(ListA)>=list_size(ListB)){
        for(int i=0;i<list_size(ListA);i++){
            while(q->next){
                 t=p->data+q->data;
                if(t>10){
                    p->data=t-10;
                    p= p->next;
                    p->data=p->data+1;
                    q=q->next;
                }else{
                    p->data=t;
                    p=p->next;
                    q=q->next;
                }
            }
        }
        return ListA;
    }else{
        for(int i=0;i<list_size(ListB);i++){
                    while(p->next){
                 t=p->data+q->data;
                if(t>=10){
                    q->data=t-10;
                   q= q->next;
                    q->data=q->data+1;
                    p=p->next;
                }else{
                    q->data=t;
                    q=q->next;
                    p=p->next;
                }
            }
        }
        return ListB;
    }
    

}