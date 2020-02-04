#include <stdio.h>
#include <ctype.h>
#define CAPS ('A'-'a')
int main(void){
    char c;
    int i,letter[26];
    for ( i = 0; i < 26; i++)
    {
        letter[i]=0;
    }
    while (((c = getchar())!=EOF))
    {
        if(islower(c))
        {
            ++letter[c-'a'];
        }
    }
    for ( i = 0; i < 26; ++i)
    {
        if (i%5==0)
        {
            printf("\n");
        }
        printf("%c:%4d ",'a'+i,letter[i]);
    }
    printf("\n");
    return 0;
}
