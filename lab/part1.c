#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
void test();
int pwdok(char *s);
int main()
{
    test();
    return 0;
}
void test(){
    assert(pwdok("Ab1")==1);
    assert(pwdok("Ab#")==1);
    assert(pwdok("Ab")==0);
    assert(pwdok("#dafdafad2345")==0);
}
int pwdok(char *s){
    char a[50];
    int i,k=0,b=0,c=0;
    int len;
    len = strlen(s);
/*     printf("len:%d\n",len); */

    for ( i = 0; i < len; i++)
    {
        a[i]= ' ';
    }
    

    for ( i = 0; i < len; i++)
    {
        if (s[i]>='a'&& s[i]<='z')
        {
            a[i]='0';
        }
        else if (s[i]>='A'&& s[i]<='Z')
        {
            a[i]='1';
        }
        else if (!isalpha(s[i]))
        {
            a[i]='2';
        }
    } 

/*     for ( i = 0; i < len; i++)
    {
        printf("%c",a[i]);
    }
    printf("\n%s\n------------------\n",a); */

    for ( i = 0; i < len; i++)
    {
        switch (a[i])
        {
        case '0':
            k++;
            break;
        case '1':
            b++;
            break;
        case '2':
            c++;
            break;
        default:
            break;
        }
    }
/*     printf("fz:%d %d %d\n",k,b,c); */


    if (k!=0 && b!=0 && c!=0)
    {
        return 1;
    }
    return 0; 
    
}
