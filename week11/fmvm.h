/* Multi-Value Map ADT : via static hashmap Linked List
    Both key & data are strings (char*) 
    Multiple Keys may be stored
    If a key corresponds to multiple values, 
    store the value in the linked list
    New value is inserted at the front of the list:
    O(1) insertion
    O(1) search
*/

/* Error that can't be ignored */
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
#define HASHSIZE 150000
#define MAXLEN 3000
struct valuenode {
    char* val;
    struct valuenode* next;
};
typedef struct valuenode valuenode;
struct mvmcell{
    char* key;
    valuenode *datahead;
    struct mvmcell* next;
};
typedef struct mvmcell mvmcell;
struct mvm{
    mvmcell *hashtable[HASHSIZE];
    int size;
};
typedef struct mvm mvm;

mvm* mvm_init(void);
mvmcell* mvmcell_init(void);
/*If a key corresponds to multiple values, store the value in the linked list */
void InsertNode(mvmcell *n,char *value);
void PrintNodeList(valuenode *l);
void InsertHashNode(mvmcell*n,char *value,char *key);
void mvmcell_free(mvmcell* p);

/* Return a key as Integer */
unsigned int hash(char *key);
/* Insert one key/value pair */
void mvm_insert(mvm *m, char* key, char* data);
/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key);
/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key,int *num);
/* Show the Hashmap */
void mvm_print(mvm *m);
/* Free & set p to NULL */
void mvm_free(mvm** p);
