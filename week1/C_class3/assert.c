#include <stdio.h>
#include <assert.h>

int min(int a,int b);

int main(void){

    int j,k,m;
    
    printf("Input two integers:  ");
    scanf("%d%d",&j,&k);
    m = min(j,k);
    printf("\nOf the two values %d and %d, the minimum is %d.\n",j,k,m);

    return 0;

}

int min(int a,int b){
    if(a>b)
      return b;
    else
      return a;
}
