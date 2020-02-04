#include <stdio.h>
void swap(int *p,int *q);
int main(void){
    int a=3,b=7;
    swap(&a,&b);
    printf("%d %d\n",a,b);
    return 0;
}

void swap(int *p,int *q){
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}