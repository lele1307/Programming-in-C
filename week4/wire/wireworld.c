#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 41 /* x j */
#define HIGHT 41 /* y i */
#define LOOPS 1000

void Inputfile(char *txtname,char map[HIGHT][WIDTH]);
void PrintInit(char map[HIGHT][WIDTH]);
int count_n(int x,int y,char map[HIGHT][WIDTH]);
void updateC(char map[HIGHT][WIDTH],char map2[HIGHT][WIDTH]);
void test();

int main(int argc, char **argv){
    int i,j,k;
    char map[HIGHT][WIDTH]; /* map[i][j] map[y][x] */
    char map2[HIGHT][WIDTH];
    
    if( argc==2 ){
            /* test();  */
			printf("Your file name is %s ", argv[1]);
            Inputfile(argv[1],map);
            /* Display the board for 1000 generations */
            for (k=0; k<LOOPS; k++){
                updateC(map,map2);
            }
            printf("This is loop: %d\n",k);  
            for (i=0; i<HIGHT-1; i++){
                for ( j=0; j<WIDTH-1; j++){
                    printf("%c",*(*(map2+i)+j));
                }   
                printf("\n");
            }  
            printf("*****************************************\n");
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
            printf("%3d",*(*(map+i)+j));
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
    /* Read file name */
    printf("\nInput file: %s",txtname);
    printf("\n****************************************\n");
    
    if((fpRead=fopen(txtname,"r"))==NULL){
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }
    /* Add to array */
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
            case '\n':
                map2[i][j] = '\n';
                break;
            /* Concise detect illegal character in file */
            default:
                printf("Your file have invalid character!!\n");
                exit(1);
            }
        }
    }
    memcpy(map,map2, HIGHT*WIDTH *sizeof(char));
} 
