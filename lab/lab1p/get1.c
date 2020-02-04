#include <stdio.h>

int main( )
{
    int c;
    printf( "Enter a value :");
    while (((c = getchar())!=EOF)){
        putchar( c );
    }
    
    printf( "\n");
    return 0;
}
