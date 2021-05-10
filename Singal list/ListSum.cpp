#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
        int num1;
        int num2;
    scanf("%d",&num1);
    scanf("%d",&num2);
    struct node ListA=Createlist(num1);
    struct node ListB=Createlist(num2);
    list_print(ListA);
    list_print(ListB);
    struct node ListSum;
    ListSum=listSum(ListA,ListB);
    list_print(ListSum);
    return 0;
}
