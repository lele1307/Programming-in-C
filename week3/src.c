#include <stdio.h>
#include <string.h>
#include <assert.h> 
int romanToArabic( char *roman );
void test(void);
int main(int argc, char **argv)
{
    if( argc==2 ){
		if (romanToArabic(argv[1]) == 0){
			printf("ERROR: Incorrect usage, try e.g. %s XXI <- correct roman number!!\n", argv[0]);
		}else{
			printf("The roman numeral %s is equal to %d\n", argv[1], romanToArabic(argv[1]));
		}
    }
    else{
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
	test();

return 0;
}

void test(void){
	assert(romanToArabic("I")==1);
	assert(romanToArabic("V")==5);
	assert(romanToArabic("X")==10);
	assert(romanToArabic("L")==50);
	assert(romanToArabic("C")==100);
	assert(romanToArabic("D")==500);
	assert(romanToArabic("M")==1000);
	assert(romanToArabic("CM")==900);
	assert(romanToArabic("CD")==400);
	assert(romanToArabic("XC")==90);
	assert(romanToArabic("XL")==40);
	assert(romanToArabic("IX")==9);
	assert(romanToArabic("IV")==4);

} 

int romanToArabic(char *roman){
    int num = 0;
    int i ;
    int len = strlen(roman);

    for (i = len-1; i >= 0; i--)
		{
			switch (*(roman+i)){
			case 'M':
				num += 1000;
				break;

			case 'D':
				num += 500;
				break;

			case 'C':
				if ((i+1<len && *(roman + i + 1) == 'D') || (*(roman + i + 1) == 'M')){
					num -= 100;
				}
				else{
					num += 100;
				}
				break;

			case 'L':
				num += 50;
				break;

			case 'X':
				if ((i+1<len && *(roman + i + 1) == 'L' ) || (*(roman + i + 1) == 'C')){
					num -= 10;
				}
				else{
					num += 10;
				}
				break;

			case 'V':
				num += 5;
				break;

			case 'I':
				if ((i+1<len && *(roman + i + 1) == 'V')||(*(roman + i + 1) == 'X')){
					num -= 1;
				}
				else{
					num += 1;
				}
				break;
			
			default: num = 0;
			}
			
		}
        return num;

}
