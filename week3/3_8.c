#include <stdio.h>
int romanToArabic( char *roman );

int main(int argc, char **argv)
{
    
    if(argc==2)
    {
        printf("The roman numeral %s is equal to %d\n",argv[1], romanToArabic(argv[1]));
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
return 0;
}

int romanToArabic(char *roman){
    
}