#include <stdio.h>
#include <string.h>
#include <assert.h>

/*Roman numerals are calculated from the highest digit.*/
int romanToArabic( char *roman );
/*test some special numbers*/
void test(void);

int main(int argc, char **argv)
{
    if( argc==2 ){
		if (romanToArabic(argv[1]) == 0){
			printf("ERROR: Incorrect usage, try e.g. %s XXI <- Please unsing correct roman number!!\n", argv[0]);
		}else{
			test();
			printf("The roman numeral %s is equal to %d.\n", argv[1], romanToArabic(argv[1]));
		}
    }
    else{
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
	

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
	assert(romanToArabic("MDCCXXXII")==1732);
	assert(romanToArabic("123")==0);
	assert(romanToArabic("abc")==0);

}

int romanToArabic(char *roman){
    int num = 0;
    int i ;
    int len = strlen(roman);
    /*There are 3 special letter "C","X","I",discussing the two close digit respectively*/
    for (i = 0; i < len; i++)
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

