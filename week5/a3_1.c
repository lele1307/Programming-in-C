#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 20

void setRboard(int board[N][N]);
void sortH(int board[N][N]);
void sortV(int board[N][N]);
void sortR(int board[N][N]);


int main(){
    int board[N][N];
    int i,j;
    srand((unsigned)time(0));
    setRboard(board);
/*  sortH(board);
    sortV(board); */
    sortR(board);
    return 0;
}

void setRboard(int board[N][N]){
    int i,j;
    
    for ( i = 0; i < N; i++){
        for ( j = 0; j < N; j++){
            board[i][j] = rand()%10;
        }
    }
    for ( i = 0; i < N; i++){
        for ( j = 0; j < N; j++){
            printf("%2d",board[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

void sortH(int board[N][N]){
    int i,j,k;
    int tmp;
    for ( i = 0; i < N; i++){
        for ( j = 0; j < N-1; j++){
            for (k = j+1; k < N; k++){
                if(board[i][j]>board[i][k]){
                    tmp = board[i][j];
                    board[i][j] = board[i][k];
                    board[i][k] = tmp;
                }
            }
        }
    }

}

void sortV(int board[N][N]){
    int i,j,k;
    int tmp;
    for ( i = 0; i < N-1; i++){
        for ( j = 0; j < N; j++){
            for (k = i+1; k < N; k++){
                if(board[i][j]>board[k][j]){
                    tmp = board[i][j];
                    board[i][j] = board[k][j];
                    board[k][j] = tmp;
                }
            }
        }
    }
}

void sortR(int board[N][N]){
    int i,j,p,q;
    int n;
    int tmp;
    int m1,n1,m2,n2;
    

    for (n = 0; n < N*N*N*N; n++){
        i=rand()%N;  /*i,j*/
        j=rand()%N;  /*p,q*/
        p=rand()%N;
        q=rand()%N;

        m1=(i-10)*(i-10);
        m2=(j-10)*(j-10);
        n1=(p-10)*(p-10);
        n2=(q-10)*(p-10);


        if(board[i][j] > board[p][q] && (m1+m2) < (n1+n2) ){
            tmp = board[i][j];
            board[i][j] = board[p][q];
            board[p][q] = tmp;
        }
        /*if(board[i][j]<board[p][q]&&(m1+m2)>(n1+n2)){
            tmp = board[i][j];
            board[i][j] = board[p][q];
            board[p][q] = tmp;
        }*/
    }

    for ( i = 0; i < N; i++){
        for ( j = 0; j < N; j++){
            printf("%2d",board[i][j]);
        }
        printf("\n");
    }
    

}

