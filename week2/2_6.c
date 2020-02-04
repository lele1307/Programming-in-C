#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){
    
    int i,n,c=0;
    double x,y,pi;
    srand(time(0));
    printf("How many times you want to input into the square? ");
    scanf("%d",&n);


    for ( i = 0; i <= n; ++i)
    {
        x = 2.0*rand()/RAND_MAX-1.0;
        y = 2.0*rand()/RAND_MAX-1.0;

        if (x*x + y*y<1.0)
        {
            c++;
        }
        
    }

    pi = 4.0*c/n;
    printf("pi value: %f\n",pi);
    
    return 0;
}
