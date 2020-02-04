#include <stdio.h>
  int fact(int num);
  int main(void){
  
  int num,i;
  int fixnum = 77;
  printf("How many numbers do you wish to look?");
  scanf("%d",&num);
  printf("Here is list.");

  for(i = 0; i < num ; i++){
    if (fixnum % 2 == 0 ){
      fixnum = fixnum/2;
      printf("\n%d",fixnum);
    }else{
      fixnum = 3*fixnum+1;
      printf("\n%d",fixnum);
    }
  }

  return 0;
  }