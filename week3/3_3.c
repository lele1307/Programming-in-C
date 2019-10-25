#include <stdio.h>
#include <stdlib.h>

void randomlist(int *q, int num);
int exchangeArray(int *q, int num);
int main(){
    int num,*p,i;
    int *q;
    p=&num;
    printf("How many songs required ? ");
    scanf("%d",p);

    q = (int*)malloc(*p*sizeof(int));
    if(q == NULL){
        printf("Allocation Failed...\n");
        return(1);
    }
    else
    {
        printf("Memory Successfully allowed...\n");
        for ( i = 0; i < *p; i++)
        {
            q[i] = i+1;
        }
        randomlist(q,num);
        exchangeArray(q,num);
        printf("The elements of the arrary are: \n");
        for ( i = 0; i < *p; i++)
        {
            printf("%d ",q[i]);
        }
    
    }
    void free(void*q);
    return 0;
}

void randomlist(int *q,int num){
    int i=0,j=0,k=0;
    for (i = 0; i < num; i++)
    {
        j = rand()%(num-i)+i;
        k = q[i];
        q[i] = q[j];
        q[j] = k;
    }

}

int exchangeArray(int *q,int num){
    int i;
    for ( i = 0; i < num; i++)
    {
        
    }
    

}