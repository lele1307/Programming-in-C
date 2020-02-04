#include <stdio.h>

int main(){
    int i,j;
    char str[3][4]={"abc","cde","fff"};
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%c\n",*(*(str+i)+j));
        }
    
    }
    return 0;
}
