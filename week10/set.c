#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define ARRDEFSZ 32

set* set_init(void)
{
    set* l;
    l = (set*) calloc(1,sizeof(set));
    if(l == NULL){
        ON_ERROR("Creation of SET Failed\n");
    }
    l->ua = (arr*) calloc(ARRDEFSZ, sizeof(arr));
    if(l->ua== NULL){
        ON_ERROR("Creation of SET Failed\n");
    }
    l->sz = ARRDEFSZ;
    return l;
}
set* set_copy(set *s)
{
    set *new;
    int i,j;
    i=set_size(s);
    new = (set*) calloc(i,sizeof(set));
    if (new == NULL)
    {
        ON_ERROR("Creation of SET_Copy Failed\n");
    }
    for ( j = 0; j < i; j++)
    {
        new->ua[j] = new->ua[j];
    }
    new->sz = i;
    return new;
}
set* set_fromarray(arrtype *a, int n)
{
    set *new = NULL;
    new = (set*) calloc(1,sizeof(set));
    if (new == NULL)
    {
        ON_ERROR("Creation of SET_Copy Failed\n");
    }
    if (a==NULL)
    {
        printf("Can not set from arrary\n");
    }
    else
    {
        memcpy(new->ua->data,a,sizeof(arrtype)*n);
        new->ua->pz = n;
        new->sz = 1;
    }
    return new;
}
/* void set_insert(set* s, arrtype l)
{
    if (s==NULL)
    {
        ON_ERROR("SET_Insert Failed\n");
    }
} */
int set_size(set* s)
{
    if (s==NULL)
    {
        return 0;
    }
    return s->sz;
}
int set_contains(set* s, arrtype l)
{
    int i,len;
    len = s->ua->pz;
    if (s==NULL)
    {
        return 0;
    }
    for ( i = 0; i < len && s->ua->data[i]!=l; i++)
    {
        if (i<len)
        {
            return 1;
        }
    }
    return 0;
}

void set_remove(set* s, arrtype l)
{
    int Newlen;
    int i,l_index;
    if (set_contains(s,l)==0)
    {
        ON_ERROR("SET_Remove Failed\n");
    }
    else
    {
        Newlen = s->ua->pz-1;
        for ( i = 0; i <= Newlen; i++)
        {
            if (s->ua->data[i]==l)
            {
                l_index=i;
            }
        }
        for ( i = l_index; i < Newlen-1; i++)
        {
            s->ua->data[i]=s->ua->data[i+1];
        }
        s->ua->data = (arrtype*) realloc(s->ua->data, sizeof(arrtype)*(Newlen));
        if(s->ua->data == NULL){
            ON_ERROR("Removing of Array Failed\n");
        }
        s->ua->pz = Newlen;
    }
    
}
arrtype set_removeone(set* s)
{
    int index,Newlen;
    int i;
    arrtype *new;
    srand((unsigned)time(NULL));
    index = rand()%s->ua->pz;
    Newlen = s->ua->pz-1;
    for ( i = index; i < Newlen-1; i++)
    {
        s->ua->data[i]=s->ua->data[i+1];
    }
    new = (arrtype*) calloc(Newlen, sizeof(arrtype));
    if(new == NULL){
        ON_ERROR("Creation of set_removeoneArray Failed\n");
    }
    for ( i = 0; i < Newlen; i++)
    {
        new[i]=s->ua->data[i];
    }
    return new;
}

set* set_union(set* s1, set* s2)
{
    int index=0,i,s1_l,s2_l;
    s1_l = s1->ua->pz;
    s2_l = s2->ua->pz;
    set *new;
    new = (set*) calloc(1,sizeof(set));
    if (new == NULL)
    {
        ON_ERROR("Creation of SET_Copy Failed1\n");
    }
    arrtype *newarry;
    newarry=(arrtype*) calloc(s1_l+s2_l, sizeof(arrtype));
    if (newarry == NULL)
    {
        ON_ERROR("Creation of SET_Copy Failed2\n");
    }
    for ( i = 0; i < s1_l; i++)
    {
        newarry[index]=s1->ua->data[i];
        index++;
    }
    for ( i = 0; i < s2_l; i++)
    {
        newarry[index]=s2->ua->data[i];
        index++;
    }

    for ( i = 0; i < index; i++)
    {
        new->ua->data[i]=newarry[i];
    }
    new->ua->pz=s1_l+s2_l;
    new->sz =1;
    return new;
}

set* set_intersection(set* s1, set* s2)
{
    int temp,i,j;
    int *returnsize=0;
    set *new;
    new = (set*) calloc(1,sizeof(set));
    if (new == NULL)
    {
        ON_ERROR("Creation of SET_Copy Failed1\n");
    }
    SelectSort(s1->ua->data,s1->ua->pz);
    SelectSort(s2->ua->data,s2->ua->pz);
    
    



    return new;
}
void SelectSort(arrtype *elm,int size){
    int i,j,min,temp;
    for ( i = 0; i < size-1; i++)
    {
        min=i;
        for ( j = i+1; i < size; j++)
        {
            if (elm[min]>elm[j])
            {
                min=j;
            }
        }
        if (min!=i)
        {
            temp=elm[min];
            elm[min]=elm[i];
            elm[i] = temp;
        }
    }
}
void set_free(set**s)
{
    set *a = *s;
    if (*s==NULL)
    {
        printf("SET_Free is NUll\n");
    }
    free(a->ua);
    free(a);
    *s=NULL;
}
