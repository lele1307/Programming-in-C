#include <stdio.h>
#include <stdlib.h>
void randomFirstlist(int *a);
void randomNextlist(int *b,int *a);
int main(void)
{
    int a[33],b[33];
    int i;

    for ( i = 0; i < 33; i++)
    {
        a[i] = (i+1)%2;
    }
    randomFirstlist(a);
    printf("The first arrary is: \n");
    for ( i = 0; i < 33; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\nthis is next array: \n");
    randomNextlist(b,a);
    return 0;

}

void randomFirstlist(int *a){
    int i=0,j=0,k=0;
    for (i = 0; i < 33; i++)
    {
        j = rand()%(33-i)+i;
        k = a[i];
        a[i] = a[j];
        a[j] = k;
    }
}

void randomNextlist(int *b,int *a){
    int x,y,z;
    b[0]=0;
    b[33]=0;
    for ( x = 1; x < 32; x++)
    {
        if (a[x-1]==1 && a[x]==1 && a[x+1]==1)
        {
            b[x]=0;
        }
        else if(a[x-1]==1 && a[x]==0 && a[x+1]==0)
        {
            b[x]=0;
        }
        else if(a[x-1]==0 && a[x]==0 && a[x+1]==0)
        {
            b[x]=0;
        }else
        {
            b[x]=1;
        }
        
    }
            printf("%d ",b[x]);

}