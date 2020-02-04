#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"
int main()
{
    int i,j;
    mvm *map;
    mvmcell *m;
    char *str;
    char **av;
    char animals[5][10] = {"cat", "dog", "bird", "horse", "frog"};
    char noises[5][10] = {"meow", "bark", "tweet", "neigh", "croak"};
    printf("Basic MVM Tests ... Start\n");

    /* Linked List test */
    m=mvmcell_init();
    InsertNode(m,"value");
    mvmcell_free(m);

    map=mvm_init();
    /* Insert Different Keys */
    assert(map!=NULL);
    for ( i = 0; i < 5; i++)
    {
        mvm_insert(map,animals[i],noises[i]);
    }
    /* Insert Same Keys */
    mvm_insert(map,"key","data");
    mvm_insert(map,"key","data1");
    assert(map->size==6);

    /* Weird NULL insert() edge cases */
    mvm_insert(map, NULL, "quack");
    assert(map->size==6);
    mvm_insert(NULL, "duck", "quack");
    assert(map->size==6);
    mvm_insert(map, "duck", NULL);
    assert(map->size==6);

    /* Test building & printing */
    mvm_print(map);

    /* Search Keys */
    assert(mvm_search(map, "fox") == NULL);
    str = mvm_search(map,"cat");
    printf("%s\n",str); 
    free(str);

    /* Multisearching */
    av = mvm_multisearch(map,"key",&i);
    assert(i==2);
    i = strcmp(av[0], "data1");
    j = strcmp(av[1], "data"); 
    assert((i==0)&&(j==0));
    free(av); 

    /* Freeing */
    mvm_free(&map);
    assert(map==NULL);

    printf("Basic MVM Tests ... Stop\n");
    return 0;
}
