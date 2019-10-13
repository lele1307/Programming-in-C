#include <stdio.h>
#include <string.h>
int romanToArabi(char *roman,int len);
int main()
{
    char arr[100] = {0};
	printf("Please enter a Roman number (1-3999):");
	scanf("%s", &arr);
	int len = strlen(arr);
	int s = romanToArabi(arr,len);
	printf("%d\n", s);
	return 0;
}
int romanToArabi(char *roman,int len){
    int num = 0;
	int i;

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



