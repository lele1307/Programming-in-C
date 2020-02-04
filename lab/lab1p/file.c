#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main(void){
    char str[50];
    FILE *fileread;
    fileread = fopen("file.txt","r");

    if (fileread == NULL)
    {
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }
    
    fscanf(fileread,"%s",str);
    printf("%s\n",str);

    fclose(fileread);
    
    return 0;
}