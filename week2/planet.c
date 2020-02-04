#include <stdio.h>
#include <assert.h>
enum letter { a=1,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
enum letter All_letter;
int getAllresult();
int getPrime(char C1,char C2,char C3, int T);
int getVowel(int PC1,int PC2,int PC3);
int main(){
    getAllresult();
    return 0;
}
int getAllresult(){
    char C1,C2,C3;
    int N1,N2,N3;
    int T;
    for (C1 ='a'; C1 <= 'z'; ++C1)
    {
        for (C2 = 'a'; C2 <= 'z'; ++C2)
        {
            for (C3 = 'a'; C3 <= 'z'; ++C3){
                if (C1==C3&&C1!=C2&&C3!=C2)
                {
                    N1 = C1-96;
                    N2 = C2-96;
                    N3 = C3-96;
                    T = N1+N2+N3;
                    /* printf("%c%c%c %d\n",C1,C2,C3,T);  */
                    getPrime(C1,C2,C3,T);
                }
                
            }
        }
        
    }
    return 0;
}

int getPrime(char C1,char C2,char C3, int T){
    int I, flag = 0;
    int PC1,PC2,PC3;
    for(I=2; I<=T/2; I++)
    {
        if(T%I==0)
        {
            flag=1;
            break;
        }
    }
    if (flag==0){
        PC1=C1;
        PC2=C2;
        PC3=C3;
       /*  printf("%c%c%c %d\n",PC1,PC2,PC3,T); */
        getVowel(PC1,PC2,PC3);
    }else{
        return 0;
    }
    return 0;
}

int getVowel(int PC1,int PC2,int PC3){
    if(PC1 == 'a'&& PC2!='e'&& PC2!='i'&& PC2!='o'&& PC2!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC2 == 'a'&& PC1!='e'&& PC1!='i'&& PC1!='o'&& PC1!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC1 == 'e'&& PC2!='a'&& PC2!='i'&& PC2!='o'&& PC2!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC2 == 'e'&& PC1!='a'&& PC1!='i'&& PC1!='o'&& PC1!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC1 == 'i'&& PC2!='a'&& PC2!='e'&& PC2!='o'&& PC2!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC2 == 'i'&& PC1!='a'&& PC1!='e'&& PC1!='o'&& PC1!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC1 == 'o'&& PC2!='a'&& PC2!='e'&& PC2!='i'&& PC2!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC2 == 'o'&& PC1!='a'&& PC1!='e'&& PC1!='i'&& PC1!='u')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC1 == 'u'&& PC2!='a'&& PC2!='e'&& PC2!='i'&& PC2!='o')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else if(PC2 == 'u'&& PC1!='a'&& PC1!='e'&& PC1!='i'&& PC1!='o')
    {
        printf("%c%c%c\n",PC1,PC2,PC3);
    }
    else
    {
        return 0;
    }
    return 0;
}