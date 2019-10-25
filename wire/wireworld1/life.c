#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define WIDTH 40 //x j
#define HIGHT 40 //y i

char map[HIGHT][WIDTH]; //map[i][j] map[y][x]
int loop;
void init_map();
int count_cell(int x,int y);
void update_map();
void print_map();


int main(){
    init_map();
    while (1)
    {
        /* print map */
        print_map();
        /* calculate map */
        update_map();
        //getchar();
    }
    
    return 0;
}

void init_map(){
    int i,j;
    srand((unsigned)time(NULL));
    for ( i = 0; i < HIGHT; i++)
    {
        for ( j = 0; j < WIDTH; j++)
        {
            map[i][j] = rand()%2;
        }
    }
}
int count_cell(int x,int y){
    int cell = 0;
    if (x==0){
        cell+=map[y][x+1];
        if (y>0) cell+=map[y-1][x] + map[y-1][x+1];
        if (y<HIGHT-1) cell+=map[y+1][x] + map[y+1][x+1];
    }else if (x==WIDTH-1){
        cell+=map[y][x-1];
        if (y>0) cell+=map[y-1][x] + map[y-1][x-1];
        if (y<HIGHT-1) cell+=map[y+1][x] + map[y+1][x-1];

    }else{
        cell+=map[y][x-1];
        cell+=map[y][x+1];
        if (y>0) cell+=map[y-1][x] + map[y-1][x+1]+ map[y-1][x-1];
        if (y<HIGHT-1) cell+=map[y+1][x] + map[y+1][x+1]+ map[y+1][x-1];
    }
    
    return cell;
}
void update_map(){
    int i,j,cell;
    char map2[HIGHT][WIDTH];
    for ( i = 0; i < HIGHT; i++)
    {
        for ( j = 0; j < WIDTH; j++)
        {
            cell = count_cell(j,i);
            map2[i][j] = cell == 1 || (cell == 2 && map[i][j]);
        }
    }
    memcpy(map,map2,HIGHT * WIDTH * sizeof(char));
}

void print_map(){
    int i,j;
    for ( i = 0; i < HIGHT; i++)
    {
        for ( j = 0; j < WIDTH; j++)
        {
            if (map[i][j]==1)printf("c");
            else printf(" "); 
        }
        puts("");
    }
    printf("loop:%d\n",loop++);
}

