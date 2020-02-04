#include <stdio.h>
    int fact(int num);
    int main(void){
    
    /* int i = 0; */
    int innum;
    printf("\nWhich number you want to start? ");
    scanf("%d",&innum);
    /* printf("How many numbers do you wish to look? ");
    scanf("%d",&num); */
    printf("Here is list.");
    printf("\n%d",innum);

    do
    {
      if(innum % 2 == 0 ){
          innum = innum/2;
          printf("\n%d",innum);
        }else{
          innum = 3*innum+1;
          printf("\n%d",innum);
        }
    } while (innum == 1);
    
    return 0;
    }

