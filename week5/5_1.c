#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HIGHT 370122
#define WIDTH 20 

void Inputfile(char file[HIGHT][WIDTH]);
void Search(char file[HIGHT],char *SearchWord);

int main(int argc, char **argv){
    char file[HIGHT][WIDTH];
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
    int i,j;
    char fileg[HIGHT];
    FILE *fpRead;
    /* Read file name IN */
    if((fpRead=fopen("eng_370k_shuffle.txt","r"))==NULL){
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }

    /* Add to array */
        while(fgets(fileg,HIGHT,fpRead)!=NULL){
                /* printf("%s",file); */
            strcpy(file,fileg);
            fputs(fileg,stdout);
        } 

/*     for(i=0;i<HIGHT;i++){
        for(j=0;j<WIDTH;j++){
            printf("%c",file[i][j]);
        }
    } */

    

    fclose(fpRead);
}

void Search(char file[HIGHT],char *SearchWord){
    int i;
    printf("\nInput word: %s\n",SearchWord);
    
        printf("%s",file[0]); 
    
}