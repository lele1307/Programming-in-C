#include <stdio.h>
int isin(int k,int *a,int n);
int RecBin(int k,int *a,int l, int r);
int main(){
    int a[]={4,7,19,25,36,37,50,100,101,205,220,271,301,321};
    if (/* isin(5,a,14)>0 */ RecBin(6,a,0,13)>0)
    {
        printf("Found it!\n");
    }
    else
    {
        printf("Not found it!\n");
    }
    return 0;
}
/*Binary searching*/
int isin(int k,int *a,int n){
    int l,r,m;
    l = 0;
    r = n-1;

    while (1<=r)
    {
        m = (l+r)/2;
        if (k==a[m])
        {
            return m;
        }
        else
        {
            if (k>a[m])
                l=m+1;
            else
                r=m-1;
        }
    }
    return -1;
}

/*Recursive binary searching*/
int RecBin(int k,int *a,int l, int r){
    int m;
    if (l > r) return -1;
    m = (l+r)/2;
    if (k == a[m])
    {
        return m;
    }
    else
    {
        if (k>a[m])
        {
            return RecBin(k,a,m+1,r);
        }
        else
        {
            return RecBin(k,a,l,m-1);
        }
    }
    
    
}
