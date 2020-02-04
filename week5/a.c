#include <stdio.h>
#include <string.h>
#include <assert.h>

int anagram(char s1[], char s2[]);
void test();

int main (int argc,char **argv) {
    if( argc==3 ){
        /* test(); */
        printf("Your test word is '%s' and '%s'\n", argv[1],argv[2]);
        anagram(argv[1],argv[2]);

    }else{
        printf("ERROR: Incorrect usage, try e.g. %s elvis lives", argv[0]);
    }
    return 0;
}

int anagram(char s1[], char s2[]){

    char s3[100];
    char s4[100];
    char temp;
    int i, j;
    int n  = strlen(s1);
    int n1 = strlen(s2);

    /* If both strings are of different length, then they are not anagrams */
    if( n != n1) {    
        printf("%s and %s are not anagrams! \n", s1, s2);
        return 0;
    }else{
        /* sort both strings first */
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if (s1[i] > s1[j]) {
                    temp  = s1[i];
                    s1[i] = s1[j];
                    s1[j] = temp;
                }
                if (s2[i] > s2[j]) {
                    temp  = s2[i];
                    s2[i] = s2[j];
                    s2[j] = temp;
                }
            }
        }
        /* Compare both strings character by character */
        for(i = 0; i<n; i++) {
            if(s1[i] != s2[i]) {    
                printf("Strings are not anagrams! \n");
                return 0;
            }
        }
        printf("Strings are anagrams! \n");
        return 1;
    
    }
    
}

void test(){
assert(anagram("elvis", "lives") == 1);
assert(anagram("dreads", "sadder") == 1);
assert(anagram("replays", "parsley") == 1);
assert(anagram("listen", "silent") == 1);
assert(anagram("orchestra", "carthorse") == 1);
/* Two identical words are not anagrams */
assert(anagram("elvis", "elvis") == 0);
assert(anagram("neill", "neil") == 0);
assert(anagram("neil", "neill") == 0);
assert(anagram("horse", "short") == 0);
}


