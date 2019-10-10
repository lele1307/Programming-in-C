
#include<stdio.h>
int main() {
	char string[20];
	int i;
	scanf("%s", string);
	printf("\nKEY:\n");
	puts(string);
	for (i = 0; i < 20; i++) {
		if (string[i] >= 'a' && string[i] <= 'z')
			string[i] = 27-(string[i]-96)+96;
		if (string[i] >= 'A' && string[i] <= 'Z')
			string[i] = 27-(string[i]-64)+64;
	}
	printf("\nTXT:\n");
	puts(string);
	return 0;

}
