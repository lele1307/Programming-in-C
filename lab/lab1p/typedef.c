#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

enum bool{false,true};
typedef enum bool bool;

bool boolt(int a,int b);
int main(void){
    int a,b;
    a=1;
    b=2;
    assert(boolt(a,b)==false);
    return 0;
}
bool boolt(int a,int b){
    if (a>b)
    {
        return true;
    }
        return false;
}