#include <stdio.h>
#include <math.h>
#define PI 3.1415

int main(){
      int x;
      double y,r;
      double s,c;
      printf("Please input X(a number):");
      scanf("%d", &x);
      printf("%.3f\n",PI);
      y = x*PI;
      s = sin(y);
      c = cos(y);

    
    
    printf("sin = %f, cos = %f\n",s,c);

     r = s*s+c*c;
    
    if(r == 1)
       printf("True!!\n");
    else
       printf("False!!\n");
   
    return 0;
}
