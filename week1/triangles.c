#include <stdio.h>
#include <math.h>
#define M 0.00001
int main(){
    float a, b, c;
    /*float s, area;*/
    printf("Please input triangles's sides:\n");
    scanf("%f,%f,%f",&a,&b,&c);

    if(a+b>c && b+c>a && c+a>b){
        /*s = (a+b+c)/2;
        area = (float)sqrt(s*(s-a)*(s-b)*(s-c));
        printf(": %f\n",area);*/
        if( abs(a-b)< M && abs(a-c)<M) 
           printf("equilateral\n");
        else if(abs(a-b)< M || abs(a-c)< M || abs(b-c)< M) 
           printf("isosceles\n");
        else if((a*a+b*b==c*c)||(b*b+c*c==a*a)||(a*a+c*c==b*b)) 
           printf("right angled triangle\n");
        else
           printf("common triangle\n");
    }else{
        printf("Not a triangle\n");
    }

    return 0;
}
