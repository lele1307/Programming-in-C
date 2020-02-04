#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UPPER 1000
#define lOWER 1
int main(){
    int rnum,cnum,*p,i;
    /*random num*/
    srand(time(0));
    rnum = (rand()%(UPPER-lOWER + 1)) + lOWER;
   /*  printf("random %d\n",rnum); */
    
    /*choose number*/
    for ( i = 0; i < 10; i++)
    {
        printf("Please choose a number from 1 to 1000: ");
        p=&cnum;
        scanf("%d",p);
        if(rnum==*p)
        {
            printf("You win!!The result is %d.\n",rnum);
            i=11;
        }
        else if (rnum > *p)
        {
            printf("Your number is %d. Lower!\n",*p);
        }
        else if(rnum < *p)
        {
            printf("Your number is %d. Higher!\n",*p);
        }
    }
    
    return 0;
}
