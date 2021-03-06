#include "trie.h"
#define DICTIONARY "large.txt"  // default args
#define TEXT "alice.txt"

TRNode * root = NULL;
/*
int main(int argc, char * argv[]){
    
    if (argc != 2 && argc != 3){
        printf("Usage: speller dictionary text\n");
    }
    char * dictionary = argc == 3 ? argv[1] : DICTIONARY; // default args if nothing provided
    char * text       = argc == 3 ? argv[2] : TEXT;
    
    bool is_loaded = load(dictionary);
    printf("dictionary* : %p\n", dictionary);
    printf("is loaded? : %d\n", is_loaded);
    
    FILE * tex = fopen(text, "r");
    char findme[MAX_LEN]; for(int f = 0; f < MAX_LEN; f++){ findme[f] = 0; }
    while(fscanf(tex, "%s", findme) != EOF){
        bool was_found = false;
        was_found = check(findme);
        printf("found?: %s %d\n", findme, was_found);
    }
    
    int trie_size = size();
    printf("size: %d\n", trie_size);
    
    bool is_unloaded = unload();
    printf("is_unloaded? : %d\n", is_unloaded);
    
    free(tex);
    
    
    return 0;
}
*/
bool load(const char * dictionary){
    char temp[LENGTH]; for(int q = 0; q < LENGTH; q++){temp[q] = 0;}
    FILE * dict = fopen(dictionary, "r");
    while(fscanf(dict, "%s", temp) != EOF){
        int i = 0;
        TRNode * trav = root;
        while(isalpha(temp[i])){
            unsigned int box = get_index(temp[i]);
            if(root == NULL){
                root = new_node();
                trav = root;
            }
            if(trav->children[box] == NULL){
                trav->children[box] = new_node();
            }
            trav = trav->children[box];
            i++;
        }
        if(trav != NULL){
            trav->is_word = true;
        }
    }
    free(dict);
    return true;
}

TRNode * new_node(void){
    TRNode * node = (TRNode*) malloc(1 * sizeof(TRNode));   /// error handling
    if(node == NULL){
        printf("You're out of memory\n");
        return NULL;
    }
    for (int q = 0; q < ALPHA; q++) {  /// avoid any garbage in memory (i know it exists)
        node->children[q] = NULL;
    }  
    return node;
}

bool check(const char * find_me){
    TRNode * trav = root;
    if(trav == NULL){
        return false;
    }
    int i = 0;
    while(find_me[i] != 0){
        unsigned int box = get_index(find_me[i]);
        if(trav->children[box] != NULL){
            trav = trav->children[box];
        }else{
            return false;
        }
        i++;
    }
    return trav->is_word;
}

bool unload(void){
    TRNode * trav = root;
    if (trav == NULL){
        return false;
    }
    free_node(trav);
    return true;
}

void free_node(TRNode * pointer){
    if(pointer == NULL){
        return;
    }
    for(int i = 0; i < ALPHA; i++){
        if(pointer->children[i] != NULL){
            free_node(pointer->children[i]);
        }
    }
    free(pointer);
}

unsigned int size(void){
    TRNode * trav = root;
    if(trav == NULL){
        return false;
    }
    int size = 0;
    size_helper(&size, trav);
    return size;
}

void size_helper(int * size, TRNode * pointer){
    for(int i = 0; i < ALPHA; i++){
        if(pointer->children[i] != NULL){
            size_helper(size, pointer->children[i]);
        }
    }
    if(pointer->is_word){
        *size = *size + 1;
    }
}

unsigned int get_index(const char symbol){
    if(symbol == '\''){
        return 26;
    }
    unsigned int num = 0;
    num = tolower(symbol) - 'a';
    return num;
}

