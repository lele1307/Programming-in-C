#include <stdio.h>
#include <stdlib.h>

#define Num 50000
int getHailstone(int p);
int maxHailstone(int p);
int main()
{
    int i, n,num,Max_num,max=0,imax,inum; 
    for ( i = 1; i < Num; i++)
    {
        n=getHailstone(i);
        if (max<n)
        {
            max=n;
            imax=i;
        }

        num=maxHailstone(i);
        if (Max_num<num)
        {
            Max_num=num;
            inum = i;
        }
    }
    printf("The longest Hailstone lenth is %d and the number is %d.\n",max,imax);
    printf("%d %d",Max_num,inum);
    return 0;
}

int getHailstone(int p){
    int l = 1;
    while (p!=1){
        if (p%2==0)
        {
            p=p/2;
        }
        else
        {
            p=3*p+1;
        }
    }
    return l;
}

int maxHailstone(int p)
{
	int max=1;
	while(p!=1)
	{
		if (p%2==0)
		{
			p=p/2;
		}
		else
		{
			p=3*p+1;
		}
		if(p>max)
		{
			max=p;
		}
	
	}
	return max;
}