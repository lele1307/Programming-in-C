#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HIGHT 370122
#define WIDTH 32 

void Inputfile(char file[HIGHT][WIDTH]);
void Search(char file[HIGHT],char *SearchWord);

int main(int argc, char **argv){
    static char file[HIGHT][WIDTH];
    if( argc==2 ){
        printf("Your test word is %s \n", argv[1]);
        Inputfile(file);
/*         Search(file,argv[1]); */
    }else{
        printf("ERROR: Incorrect usage, try e.g. %s sternaig\n", argv[0]);
    }
    return 0;
}

void Inputfile(char file[HIGHT][WIDTH]){
    int i,j; /*WhichLine*/
    int CurrentIndex=0;  
    char fileg[32];
    FILE *fpRead;
    /* Read file name IN */
    if((fpRead=fopen("eng_370k_shuffle.txt","r"))==NULL){
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }

    /* Add to array */
    for (i=0; i<HIGHT-1; i++){
        if (CurrentIndex==i){
            fgets(fileg,32,fpRead);
            /* printf("%s", fileg); */
            stpcpy(file[i],fileg);
            CurrentIndex++;  
        }
    }
        printf("%s",file[0]); 

    fclose(fpRead);
}

/* void Search(char file[HIGHT],char *SearchWord){
    int i;
    printf("\nInput word: %s\n",SearchWord);
    
        printf("%s",file[0]); 
    
} */
