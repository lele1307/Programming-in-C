#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
void test();
int pwdok(char *s);
void passwp(char *a, char*b);
int main()
{
    test();
    return 0;
}
void test(){    
    char b[100];
    passwp("oasl", b);
    assert(pwdok("Ab1")==1);
    assert(pwdok("Ab#")==1);
    assert(pwdok("Ab")==0);
    assert(pwdok("#dafdafad2345")==0);
    assert(strcmp(b,"0@5l"));
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

void passwp(char *a, char*b){
    int i,len;
    len = strlen(a);

    for ( i = 0; i < len; i++)
    {
        switch (a[i])
        {
        case 'a':
            b[i]='@';
            break;
        case 'o':
            b[i]='0';
            break;
        case 's':
            b[i]='5';
            break;
        default:
            b[i]=a[i];
            break;
        }
    }

/*     printf("%s",b); */
}
