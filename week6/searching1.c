#include <stdio.h>
#include <string.h>
#define NUMPEOPLE 6

struct key
{
    char *name;
    int age;
};

typedef struct key Key;

int Findage(char *name,Key *l,int n);

int main(){
    int i,j;
    Key a[NUMPEOPLE] = {
        {"Amy",21},
        {"Bob",25},
        {"Cici",23},
        {"Davide",22},
        {"Eggson",20},
        {"Fasial",40}
    };
    i=Findage("Eggson",a,NUMPEOPLE);
    j=Findage("Cala",a,NUMPEOPLE);
    printf("%d %d\n",i,j);
    return 0;
}
/*Sequential search*/
/* int Findage(char *name,Key *l,int n){
    int j;

    for ( j = 0; j < n; j++)
    {
        if (strcmp(name,l[j].name)==0)
        {
            return l[j].age;
        }
        
    }
    return -1;
} */

/*Ordered sequential search*/
int Findage(char *name,Key *l,int n){
    int j,m;
    for ( j = 0; j < n; j++)
    {
        m = strcmp(name,l[j].name);
        if (m == 0)
            return l[j].age;
        if (m < 0)
        {
            return -1;
        }
    }
    return -1;
}
