#include <stdio.h>
int main(void){

  int i, num;
  float data, max;

  printf("How many numbers do you wish to enter?");
  scanf("%d",&num);
  printf("Enter %d real numbers: \n",num);
  /*user input*/
  for(i = 0; i < num ; i++){
    printf("input number: ");
    scanf("%f", &data);
    max = data;
    if( data > max ) max = data;
  }

  printf("The max number is %f", max);
  return 0;

}
