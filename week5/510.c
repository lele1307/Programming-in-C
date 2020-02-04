#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 21
#define HIGHT 21
#define SIZE 3

void Inputfile(char *txtname, char maze[HIGHT][WIDTH], int size[SIZE]);
int step(int i, int j,int success,int size[SIZE],char maze[HIGHT][WIDTH]);
int main(int argc,char **argv){
    char maze[HIGHT][WIDTH];
    int i,j;
    int w,h;
    int size[SIZE];
    int success=0;
    int sx=1, sy=1;  /* Start location */             
    int ex,ey;       /* End location */       
    if(argc==2) {
        printf("\nYour file name is '%s' \n",argv[1]);
        Inputfile(argv[1],maze,size);
        w = size[0]; /*width*/
        h = size[1]; /*hight*/
        ex=h-2;
        ey=w-1;
        if (w>20||h>20){
            printf("This file can't be used!!");
        }else{
            for(i=0;i<h;i++){
                for(j=1;j<w;j++){
                    if(maze[i][j] == '2'){
                        printf("#");
                    }else if(maze[i][j] == '0'){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            printf("\nEntrance: location is maze[%d][%d].",sx,sy);
            printf("\nEntrance: location is maze[%d][%d].",ex,ey);
            printf("\n--------------------------------------\n");
            if(step(sx,sy,success,size,maze) == 0){
                printf("No way!\n");
            }else{
                printf("You are free!\n");
                for(i = 0; i < h; i++){
                    for(j = 1; j < w; j++){
                        if(maze[i][j] == '2'){
                            printf("#");
                        }else if(maze[i][j] == '1'){
                            printf(".");
                        }else{
                            printf(" ");
                        }
                    }
                    printf("\n");
                }
            }  
            /* printf("%d\n",step(1,1,success,size,maze)); */
            /* assert((step(8,18,size,maze) == 1)); */
        }
    }else{
        printf("ERROR: Incorrect usage, try e.g. %s maze.txt\n", argv[0]);
    }
    return 0;
}

void Inputfile(char *txtname, char maze[HIGHT][WIDTH], int size[SIZE]){
    int i,j,k;
    int w,h;
    FILE *fpRead;
    /* Read file name */
    printf("Input file: %s",txtname);
    printf("\n*************** START ****************\n");
    
    if((fpRead=fopen(txtname,"r"))==NULL){
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }
    /* Get size of the maze */
    for (k = 0; k < 2; k++){
        fscanf(fpRead,"%d",&size[k]);
    }
        w = size[0]; /*width*/
        h = size[1]; /*hight*/
        printf("\nThe maze's width is %d.\n",w);
        printf("The maze's hight is %d.\n",h);

    /* Add to array */    
    for(i=0;i<h+1;i++){
        for(j=0;j<w+1;j++){
            fscanf(fpRead,"%c",&maze[i][j]);
        }
    }

    fclose(fpRead);
}

int step(int i, int j,int success,int size[SIZE],char maze[HIGHT][WIDTH]){
    int w,h;            
    int ex,ey;       /* End location */   
    w = size[0]; /*width*/
    h = size[1]; /*hight*/
    ex=h-2;
    ey=w-1;
    maze[i][j] = '1';
    if(i == 8 && j == 18){
        success = 1;
        return 1;
    }
    if(success!=1 && j<(w-1) && maze[i][j+1] == '0'){
        if(step(i,j+1,success,size,maze)){
            return 1;
        }
    }
    if(success!=1 && i>0 && maze[i][j-1] == '0'){
        if(step(i,j-1,success,size,maze)){
            return 1;
        }
    }
    if(success!=1 && i<(h-1) && maze[i+1][j] == '0'){
        if(step(i+1,j,success,size,maze)){
            return 1;
        }
    }
    if(success!=1 && j>0 && maze[i-1][j] == '0'){
        if(step(i-1,j,success,size,maze)){
            return 1;
        }
    }
    if(success!=1){
        maze[i][j] = '0';
    } 

/*     for(i=0;i<h;i++){
        for(j=1;j<w;j++){
            printf("%c",maze[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");  */   

    return 0;
}

