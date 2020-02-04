#include <stdio.h>
int main(void){
    int num,i = 3,count,a;
    printf("How many prime numbers do you want to print?");
    scanf("%d",&num);

    if (num >= 1)
    {
      printf("The first %d primes are:\n",num);
      printf("2\n");

    }
    
    for(count = 2; count <= num;){
      for(a=2; a<=i-1; a++){
        if(i%a==0) break;
      }
      if(a==i){
        printf("%d\n",i);
        count++;
      }
      i++;
    }
  
    return 0;
}

