#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 21
#define HIGHT 21

void Inputfile(char *txtname, char maze[HIGHT][WIDTH], int size[3]);
void Solve(char maze2[HIGHT][WIDTH],char maze[HIGHT][WIDTH],int w, int h);
int step(int x,int y,char maze2[HIGHT][WIDTH],int w,int h);

int main(int argc,char **argv){
    char maze[HIGHT][WIDTH];
    char maze2[HIGHT][WIDTH];
    int i,j;
    int w,h;
    int size[3];
    if(argc==2) {
        printf("\nYour file name is '%s' \n",argv[1]);

        Inputfile(argv[1],maze,size);
        w = size[0]; /*width*/
        h = size[1]; /*hight*/
        if (w>20||h>20){
            printf("This file can't be used!!");
        }else{
            for(i=0;i<h;i++){
                for(j=0;j<w;j++){
                    printf("%c",maze[i][j]);
                }
            }
            printf("\nEntrance: %d is 'X' location is maze[1][1].",maze[1][1]);
            printf("\nEntrance: %d is 'O' location is maze[8][18].",maze[8][18]);
            printf("\n--------------------------------------\n");

            Solve(maze2,maze,w,h);
            for(i=0; i<h; i++){
                for(j=0; j<w; j++){
                    printf("%c",maze2[i][j]);
                }
            }
            printf("\n--------------------------------------\n");

        }
    }else{
        printf("ERROR: Incorrect usage, try e.g. %s maze.txt\n", argv[0]);
    }
    return 0;
}

void Inputfile(char *txtname, char maze[HIGHT][WIDTH], int size[3]){
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
        printf("\nThe maze's width is %d .\n",w);
        printf("The maze's hight is %d .\n",h);

    /* Add to array */    
    for(i=0;i<h+1;i++){
        for(j=0;j<w+1;j++){
            fscanf(fpRead,"%c",&maze[i][j]);
        }
    }
    /* Set entrance as "X" and end as "O" */
    maze[1][1] = 'X';
    maze[h-2][w-1] = 'O';

    fclose(fpRead);
}

int step(int x,int y,char maze2[HIGHT][WIDTH],int w,int h){
    int result;
    result = maze2[y][x];
    if (maze2[y][x]==51)
    {
        result = 0; /* success */
        
    }else if(maze2[y][x]==50){
        result = 2;
    }

    if(y<(h - 1) && maze2[y][x+1]== 0){
        step(y,x+1,maze2, w, h);
    }
    if(x > 0 && maze2[y][x-1]== 0){
        step(y,x-1,maze2, w, h);
    }
    if(x < (w - 1) && maze2[y+1][x] == 0){
        step(y+1,x,maze2, w, h);
    }
    if( y > 0 && maze2[y-1][x] == 0){
        step(y-1,x,maze2, w, h);
    }

    return result;

}

void Solve(char maze2[HIGHT][WIDTH],char maze[HIGHT][WIDTH],int w, int h){
    int i,j;
    /* initial maze, fill the array with spaces*/
    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            maze2[i][j] = ' ';
        }
    }
    /* Solve the way */
    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            switch (maze[i][j]){
                case 'X':
                    maze2[i][j] = '0';
                    break;
                case 'O':
                    maze2[i][j] = '3';
                    break;
                case '#':
                    maze2[i][j] = '2';
                    break;
                case '\n':
                    maze2[i][j] = '\n';
                    break;
                case ' ':
                    maze2[i][j] = '0';
                    break;
            }
        }
    } 

    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            step(j,i,maze2,w,h);
            printf("%d",step(j,i,maze2,w,h));
        }
        printf("\n");
    }
    
}




