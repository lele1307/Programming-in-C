#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SpecialChar            1
#define MaxStringLength        80
#define CodecLength            4

int main(void){
    char *ptr,Soundex[CodecLength];
    int i,j=0;

    ptr=(char *)malloc(sizeof(char)*MaxStringLength);
    if(NULL==ptr){
        printf("Out of resource!\n");
        return 1;
        }
    /* memset(ptr,0,MaxStringLength); */

    printf("Please input a string(max length is %d):",MaxStringLength);
    /* get string */
    scanf("%s",ptr);
    ptr[MaxStringLength-1]='\0';

    /* 1.to upper cap */
    for(i=0;ptr[i]!='\0';i++)
        ptr[i]=toupper(ptr[i]);

    /* 2.Get first letter */
    Soundex[0]=ptr[0];

    /* 3.filter special and double letters */
    for(i=0;ptr[i]!='\0';i++){
        if(SpecialChar==ptr[i]||ptr[j]<'A'||ptr[j]>'Z') continue; /*invalid letter? */
        if(i!=0&&('A'==ptr[i]||'E'==ptr[i]||'I'==ptr[i]||'O'==ptr[i]||'U'==ptr[i]||'H'==ptr[i]||'W'==ptr[i]||'Y'==ptr[i])){/* special letters:A, E, I, O, U, H, W, Y */
            ptr[i]=SpecialChar;
            continue;
            }
        if(ptr[i]==ptr[i+1]) /* double letters? */
            ptr[i+1]=SpecialChar;
    }

    /* 4.get first 4 valid letters or fill pad */
    for(i=1;ptr[i]!='\0';i++){
        if(ptr[i]!=SpecialChar) Soundex[++j]=ptr[i];
        if((CodecLength-1)==j) break;
        }
    while(j<CodecLength-1)
        Soundex[++j]='0';

    /* 5.convert to numberic except the first */
    for(i=1;i<CodecLength;i++){
        switch(Soundex[i]){
            case 'B':
            case 'P':
            case 'F':
            case 'V':
                Soundex[i]='1';
                break;
            case 'C':
            case 'S':
            case 'K':
            case 'G':
            case 'J':
            case 'Q':
            case 'X':
            case 'Z':
                Soundex[i]='2';
                break;
            case 'D':
            case 'T':
                Soundex[i]='3';
                break;
            case 'L':
                Soundex[i]='4';
                break;
            case 'M':
            case 'N':
                Soundex[i]='5';
                break;
            case 'R':
                Soundex[i]='6';
                break;
            default:
                break;
            }
        }

    /* output result */
    for(i=0;i<CodecLength;i++)
        printf("%c",Soundex[i]);
    free(ptr);
    return 0;
    
    }
