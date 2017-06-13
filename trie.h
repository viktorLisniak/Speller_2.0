#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<strings.h>
#include<stdbool.h>
#define ALPHA 26
#define MAX_LEN 45
#define tries_h

typedef struct trie{
    bool is_word;
    struct trie * children[ALPHA];
}TRNode;

bool check(const char * tofind);

bool load(const char * dictionary);

unsigned int size(void);

bool unload(void);


unsigned int get_index(const char symbol);



