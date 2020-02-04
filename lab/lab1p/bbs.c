#include <stdio.h>
#include <string.h>

void bbs(int a[],int s);
void bbsc(char *s,int len);
int main(){
    int a[]={3,4,1,2,9,0};
    char s[]={"hello"};
    int len;
    len = strlen(s);
    printf("%d\n",len);
    /* bbs(a,6); */
    bbsc(s,len);
    return 0;

}

/* void bbs(int a[],int s){
    int i,tmp;
    int change;
    for (change=0;change < 6; change++)
    {
        for ( i = 0; i < s-1; i++)
        {
            if (a[i]>a[i+1])
            {
                tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            }
        }
    } 

    do
    {
        change = 0;
        for ( i = 0; i < s-1; i++)
        {
            if (a[i]>a[i+1])
            {
                tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
                change++;
            }
        }
    } while (change);
    
    

    for ( i = 0; i < s; i++)
    {
        printf("%2d",a[i]);
    }
    
    

} */


void bbsc(char *s,int len){
    int i,tmp;
    for ( i = 0; i < len-1; i++)
    {
        if (s[i]>s[i+1])
        {
            tmp = s[i];
            s[i] = s[i+1];
            s[i+1] = tmp;
        }
    }
    for ( i = 0; i < len; i++)
    {
        printf("%c ",s[i]);
    }
    
}