#include "trie.h"
#define DICTIONARY "small.txt"  // default args
#define TEXT "text.txt"

TRNode * root = NULL;

int main(int argc, char * argv[]){
    
    if (argc != 2 && argc != 3){
        printf("Usage: speller dictionary text\n");
    }
    char * dictionary = argc == 3 ? argv[1] : DICTIONARY; // default args if nothing provided
    char * text       = argc == 3 ? argv[2] : TEXT;
    
    bool is_loaded = load(dictionary);
    
    printf("is loaded? : %d\n", is_loaded);
    
    FILE * tex = fopen(text, "r");
    char findme[MAX_LEN]; for(int f = 0; f < MAX_LEN; f++){ findme[f] = 0; }
    while(fscanf(tex, "%s", findme) != EOF){
        bool was_found = check(findme);
        printf("found?: %s %d\n", findme, was_found);
    }
    
    bool is_unloaded = unload();
    printf("is_unloaded? : %d\n", is_unloaded);
    
    
    return 0;
}

bool load(const char * dictionary){
    char temp[MAX_LEN]; for(int q = 0; q < MAX_LEN; q++){temp[q] = 0;}
    FILE * dict = fopen(dictionary, "r");
    
    while(fscanf(dict, "%s", temp) != EOF){
        int i = 0;
        TRNode * trav = root;
        printf("trav: %p\n", trav); //debug
        printf("root: %p\n", root);
        while(temp[i] != 0){
            unsigned int box = get_index(temp[i]);
            if(root == NULL){
                root = (TRNode*) malloc(1 * sizeof(TRNode));
                trav = root;
            }else{
                printf("trev: %p\n", trav); //debug
                printf("root: %p\n", root);
                if(trav->children[box] == NULL){
                    trav->children[box] = (TRNode*) malloc(1 * sizeof(TRNode));
                    trav = trav->children[box];
                }else{
                    trav = trav->children[box];
                }
                i++;
            }
            printf("trav: %p\n", trav); //debug
            printf("root: %p\n", root);
        }
        if(trav != NULL){
            trav->is_word = true;
        }
    }
	free(dict);
    return true;  // it's not forever
}

bool check(const char * find_me){
    TRNode * trav = root;
    bool found_me = false;
    int i = 0;
    while(find_me[i] != 0){
        unsigned int box = get_index(find_me[i]);
        if(trav->children[box] != NULL){
            trav = trav->children[box];
        }else{
            return found_me;
        }
        i++;
    }
    return trav->is_word;
}

/**
* not working yet
**/
bool unload(void){
    TRNode * trav = root;
    if (trav == NULL){
        return false;
    }
    free_node(trav);
    return true;
}

void free_node(TRNode * pointer){
    printf("pointer: %p\n", pointer);  ///debug
    if(pointer == NULL){
        return;
    }else{
        for(int i = 0; i < ALPHA; i++){
            printf("pointer->children[%d] %p\n", i, pointer->children[i]);  //debug
            if(pointer->children[i] != NULL){
                free_node(pointer->children[i]);
                printf("pointer: %p\n", pointer); /// debug
            }
        }
	free(pointer);
    }
}

unsigned int get_index(const char symbol){
    unsigned int num = 0;
    num = tolower(symbol) - 'a';
    return num;
}
//create_node(TRNode ** node, char a){
//    TRNode * node = (TRNode*) malloc(1* sizeof(TRNode));
//}
