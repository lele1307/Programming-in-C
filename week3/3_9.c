#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FinalCodeLen 4
#define MAXSL 20
#define SpecialCL 1

void test(void);
char upper(char *p1);
char SpecialC(char *p2);
char V4char(char *p3);
int main(void){
    char *pstring;
    pstring=(char *)malloc(sizeof(char)*MAXSL);
    if(NULL== pstring)
    {
        printf("Out of resource!\n");
        return 1;
    }
    printf("Please input a string(max length is %d):",MAXSL);

    /* get string */
    scanf("%s",pstring);
    pstring[MAXSL-1]='\0'; 
    /* string not array char */

    upper(pstring);
    SpecialC(pstring);
    V4char(pstring);
    
    free(pstring);

    return 0;

}

char upper(char *p1){
    int i;
    for(i=0;p1[i]!='\0';i++){
        p1[i]=toupper(p1[i]);
    }
    /*last character has some change problems but it is not impact on result*/
    return 0;
}
char SpecialC(char *p2){
    int i,j=0;
    for(i=0;p2[i]!='\0';i++){
        if(SpecialCL==p2[i]||p2[j]<'A'||p2[j]>'Z'){}/*invalid letter */
        if(i!=0 && ('A'==p2[i]||'E'==p2[i]||'I'==p2[i]||'O'==p2[i]||'U'==p2[i]||'H'==p2[i]||'W'==p2[i]||'Y'==p2[i])){/* special letters:A, E, I, O, U, H, W, Y */
            p2[i]=SpecialCL;
        }
        if(p2[i]==p2[i+1]) /* double letters? */
            p2[i+1]=SpecialCL;
    }
    return 0;
}
char V4char(char *p3){
    int i,j=0;
    char S[FinalCodeLen];
    S[0]=p3[0];

    for(i=1;p3[i]!='\0';i++){
        if(p3[i]!= SpecialCL) S[++j]=p3[i];
        if((FinalCodeLen-1)==j) break;
        }
    while(j<FinalCodeLen-1)
        S[++j]='0';

    for(i=1;i<FinalCodeLen;i++){
        switch(S[i]){
            case 'B':
            case 'P':
            case 'F':
            case 'V':
                S[i]='1';
                break;
            case 'C':
            case 'S':
            case 'K':
            case 'G':
            case 'J':
            case 'Q':
            case 'X':
            case 'Z':
                S[i]='2';
                break;
            case 'D':
            case 'T':
                S[i]='3';
                break;
            case 'L':
                S[i]='4';
                break;
            case 'M':
            case 'N':
                S[i]='5';
                break;
            case 'R':
                S[i]='6';
                break;
            }
    }
    for(i=0;i<FinalCodeLen;i++)
    {
        printf("%c",S[i]);
    }

    return 0;
}



