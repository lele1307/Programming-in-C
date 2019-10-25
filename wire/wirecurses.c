#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neillncurses.h"
#include <assert.h>

#define WIDTH 41 /* x j */
#define HIGHT 41 /* y i */

void Inputfile(char *txtname,char map[HIGHT][WIDTH]);
void PrintInit(char map[HIGHT][WIDTH]);
int count_n(int x,int y,char map[HIGHT][WIDTH]);
void updateC(char map[HIGHT][WIDTH],char map2[HIGHT][WIDTH]);
void test();

int main(int argc, char **argv){
    char map[HIGHT][WIDTH]; /*map[i][j] map[y][x]*/
    char map2[HIGHT][WIDTH];
    /* Here's where we hold all the information we need to display
    the array in the correct colours, and also event information */
    NCURS_Simplewin sw;
    if( argc==2 ){
            /* test(); */
			printf("Your file name is %s ", argv[1]);
            Inputfile(argv[1],map);
            Neill_NCURS_Init(&sw);
            Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK,COLOR_BLACK, A_NORMAL); 
            Neill_NCURS_CharStyle(&sw, "H", COLOR_BLUE,COLOR_BLACK, A_NORMAL);
            Neill_NCURS_CharStyle(&sw, "t", COLOR_RED,COLOR_BLACK, A_NORMAL);
            Neill_NCURS_CharStyle(&sw, "c", COLOR_YELLOW,COLOR_BLACK, A_NORMAL);
            Neill_NCURS_CharStyle(&sw, "\n", COLOR_BLACK,COLOR_BLACK, A_NORMAL);
            do{
                updateC(map,map2); 
                Neill_NCURS_PrintArray(&map2[0][0], WIDTH, HIGHT, &sw);
                /*  Delay in 1/1000s of a second */
                Neill_NCURS_Delay(1000.0);
                /* Test for mouse click, or ESC key */
                Neill_NCURS_Events(&sw);
            }while(!sw.finished);
            /* Call this function if we exit() anywhere in the code */
            atexit(Neill_NCURS_Done);
            exit(EXIT_SUCCESS);

    }
    else{
        printf("ERROR: Incorrect usage, try e.g. %s wirefile.txt\n", argv[0]);
    }
return 0;
}
/*This test initial file is using "wirewcircuit1.txt" as testing file,
please put this file in the same folder and you can use this function. */
void test(){
    char map[HIGHT][WIDTH];
    char map2[HIGHT][WIDTH];
    int i,j;
    /* Test wheather input file is right initially */
    Inputfile("wirewcircuit1.txt",map);
    for (i=0;i<HIGHT;i++){
        for (j=0;j<WIDTH-1;j++){
            printf("%c",*(*(map+i)+j));
        }
        printf("\n");
    }
    assert(map[4][3] == 'c');
    /* Test update cells */
    updateC(map,map2);
    assert(map2[4][4] == 'c');
    assert(map2[4][5] == 't');
    /* Test count "H" in the 8-surrounding cells */
    assert(count_n(1,0,map) == 0);
    map[0][1] = 'H'; 
    assert(count_n(1,0,map) == 0);
    map[0][2] = 'c'; 
    assert(count_n(2,0,map) == 1);
    map[39][0] = 'c';
    map[38][0] = 'H';
    map[39][1] = 'H';
    assert(count_n(0,39,map) == 2);

} 

/* Read file in project and put contents to 2D array map[][] */
void Inputfile(char *txtname,char map[HIGHT][WIDTH]){
    int i,j;
    FILE *fpRead;
    printf("\nInput file: %s",txtname);
    printf("\n******************************\n");
    
    if((fpRead=fopen(txtname,"r"))==NULL){
        printf("\nCannot open file, please check your filename!");
        exit(1);
    }
    for(i=0;i<HIGHT;i++){
        for(j=0;j<WIDTH;j++){
            fscanf(fpRead,"%[^/r]c",&map[i][j]);
        }
    }
    fclose(fpRead);
}

/* Count "H" in the 8-surrounding cells and care about edge */
int count_n(int x,int y,char map[HIGHT][WIDTH]){
    int n = 0;
    if (x==0){
        if(map[y][x+1]=='H')n++;
        if (y>0) {
            if(map[y-1][x]=='H')n++;
            if(map[y-1][x+1]=='H')n++;
        }
        if (y<HIGHT-1){
            if(map[y+1][x]=='H')n++;
            if(map[y+1][x+1]=='H')n++;
        } 
    }else if(x==WIDTH-1){
        if(map[y][x-1]=='H')n++;
        if (y>0) {
            if(map[y-1][x]=='H')n++;
            if(map[y-1][x-1]=='H')n++;
        }
        if (y<HIGHT-1){
            if(map[y+1][x]=='H')n++;
            if(map[y+1][x-1]=='H')n++;
        } 
    }else{
        if(map[y][x+1]=='H')n++;
        if(map[y][x-1]=='H')n++;
        if (y>0){
            if(map[y-1][x]=='H')n++;
            if(map[y-1][x+1]=='H')n++;
            if(map[y-1][x-1]=='H')n++;
        }
        if (y<HIGHT-1) {
            if(map[y+1][x]=='H')n++;
            if(map[y+1][x+1]=='H')n++;
            if(map[y+1][x-1]=='H')n++;
        }
    }
    return n;
}

/* Change character time by time and copy map2 to map */
void updateC(char map[HIGHT][WIDTH],char map2[HIGHT][WIDTH]){
    int i,j,n;
    /* fill the array with spaces */
    for(i=0; i<HIGHT; i++){
        for(j=0; j<WIDTH; j++){
            map2[i][j] = ' ';
        }
    }
    /* Update map to map2 */
    for (i=0;i<HIGHT-1;i++){
        for (j=0;j<WIDTH-1;j++){
            n = count_n(j,i,map);
            switch (map[i][j]){
            case ' ':
                map2[i][j] = ' ';
                break;
            case 'H':
                map2[i][j] = 't';
                break;
            case 't':
                map2[i][j] = 'c';
                break;
            case 'c':
                if(n==1||n==2){
                    map2[i][j] = 'H';
                }else{
                    map2[i][j] = 'c';
                }
                break;
            default:
                printf("Your file have invalid character!!\n");
                exit(1);
            }
        }
    }
    /* Update the initial map */
    memcpy(map,map2, HIGHT*WIDTH *sizeof(char));
} 
