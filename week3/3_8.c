#include <stdio.h>

#include <string.h>
int romanToArabic( char *roman );

int main(int argc, char **argv)
{
    /* printf("\n%s\n", argv[1]);printf("%d\n\n", argc); */
    if( argc==2 )
    {
        printf("The roman numeral %s is equal to %d\n", argv[1], romanToArabic(argv[1]));
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }

return 0;
}

int romanToArabic(char *roman){
    int num = 0;
    int i ;
    int len = strlen(roman);

    for (i = 0; i < len; i++)
		{
			switch (*(roman+i))
			{
			case 'M':
				num += 1000;
				break;
			case 'D':
				num += 500;
				break;
			case 'C':
				if ((i + 1<len && *(roman + i + 1) == 'D') || (*(roman + i + 1) == 'M'))
				{
					num -= 100;
				}
				else
				{
					num += 100;
				}
				break;
			case 'L':
				num += 50;
				break;
			case 'X':
				if ((i + 1 < len&&*(roman + i + 1) == 'L' )|| (*(roman + i + 1) == 'C'))
				{
					num -= 10;
				}
				else
				{
					num += 10;
				}
				break;
			case 'V':
				num += 5;
				break;
			case 'I':
				if ((i + 1 < len&&*(roman + i + 1) == 'V')||(*(roman + i + 1) == 'X'))
				{
					num -= 1;
				}
				else
				{
					num += 1;
				}
				break;
			}
		}
        return num;

}