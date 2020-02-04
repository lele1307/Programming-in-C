#include <stdio.h>
int main(){
    int stime,press,ctime0,ctime1,ctime2,ctime3,ctime4,ctime5;
    int a[] = {600,60,10};
    printf("Please input the time you required: ");
    scanf("%d",&stime);
    
        ctime0 = stime/a[0];
        ctime1 = stime%a[0];
        ctime2 = ctime1/a[1];
        ctime3 = ctime1%a[1];
        ctime4 = ctime3/a[2];
        ctime5 = ctime3%a[2];
        if (ctime5>0&&ctime5<=10)
        {
            ctime4=ctime4+1;
        }
        press = ctime0+ctime2+ctime4;
        printf("Number of button presses = %d\n",press);

}