#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void randomFirstlist(int *a);
void randomNextlist(int *b,int *a);
int main(void)
{
    int a[33],b[33];
    int i,t,r;
    int *p_1;
    printf("Please input 1 if you want begin with randomised first line \nor input 2 with a single on in the central location ");
    scanf("%d",&t);
    
        switch (t)
        {
        case 1:
            for ( i = 0; i < 33; i++){
                a[i] = (i+1)%2;
            }
            randomFirstlist(a);

            printf("The first arrary is: \n");
            for ( i = 0; i < 33; i++){
                printf("%d ",a[i]);
            }
            printf("\nthis is next array: \n");
            p_1 = a;
            for ( i = 0; i < 31; i++)
            {
                randomNextlist(b,p_1);
                p_1 = b;
            }
            
            /* randomNextlist(b,a); */

            break;

        case 2:
            srand((unsigned)(time(NULL)));
            r=rand()%33;
            printf("%d",r);
            for ( i = 0; i < 33; i++)
            {
                a[i] = 0;
                a[r] = 1;
            }
            printf("The first arrary is: \n");
            for ( i = 0; i < 33; i++)
            {
                printf("%d ",a[i]);
            }
            printf("\nthis is next array: \n");
            p_1 = a;
            for ( i = 0; i < 31; i++)
            {
                randomNextlist(b,p_1);
                p_1 = b;
            }
            
           /*  randomNextlist(b,a); */
            break;
        
        default:
            printf("YOU INPUT WRONG CHARACTER!!");
            break;   
        }
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
    int x;
    b[0]=0;
    b[32]=0;
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
    for ( x = 0; x < 33; x++)
    {
        printf("%d ",b[x]);
    }
    printf("\n");

}

