#include <stdio.h>

int main(){

    int hour1,min1,s1,ss1;
    int hour2,min2,s2,ss2;
    
    int hour,min,s;
    int mins;
    
    char op1,op2,op3,op4;
    
    printf("Please input first time point:"); 
    scanf("%d%c%d%c%d",&hour1,&op1,&min1,&op2,&s1);
    ss1 = s1+min1*60+hour1*3600;
    
    printf("Please input second time point:");
    scanf("%d%c%d%c%d",&hour2,&op3,&min2,&op4,&s2);
    ss2 = s2+min2*60+hour2*3600;
    
    if(ss1>ss2)
      mins = ss1-ss2;
    else
      mins = ss2-ss1;

      hour = mins/3600;
      min = (mins%3600)/60;
      s = mins - hour*3600 - min*60;
    
    printf("The two time points difference is %02d:%02d:%02d",hour,min,s);
    
    return 0;



}
