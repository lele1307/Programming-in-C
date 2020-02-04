#include <stdio.h>
int main(void){

  int i, num;
  int data, max;
  printf("How many odd integers do you wish to enter?");
  scanf("%d",&num);
  printf("Enter %d odd integers: \n",num);

  for(i = 0; i < num ; i++){
    printf("\ninput number: ");
    scanf("%d", &data);

    if(data%2 == 0){
      max = data;
      if( data > max ) max = data;
    }else{
      i = i++;
      printf("%d is not an odd integer!!",data);
      fact();
    }
  }

  printf("The max number is %d", max);
  return 0;

}
