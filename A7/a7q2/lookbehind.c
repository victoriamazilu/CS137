#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void lookBehind(const char *check, const char *s_sub, char *word){
    char *updatedW = malloc(strlen(word) * sizeof(char));
    int index = 0;
    int lenCheck = strlen(check);
    int lenSub = strlen(s_sub);

    if(s_sub[0] == '\0'){ //empty
        return;
    }

    for(int i = 0; i < strlen(word); i++){
        //check if current char matches the first character of 'check'
        if(word[i] == check[0] || check[0] == '\0'){
            bool foundCheck = true; //check pattern found
            for (int j = 0; j < lenCheck; j++){ //complete 'check' pattern in word
                if (word[i + j] != check[j]){
                    foundCheck = false;
                    break;
                }
            }

            if(foundCheck){
                //copy 'check' pattern
                for (int j = 0; j < lenCheck; j++){
                    updatedW[index] = word[i + j];
                    index++;
                }
                i += lenCheck;

                int nSub = 0; //how many times 's_sub' is found
                int searching = true;

                while(searching){
                    bool found = true;
                    for (int j = 0; j < lenSub; j++){
                        if (word[i + j] != s_sub[j]){
                            found = false;
                            searching = false;
                            break;
                        }
                    } 

                    if (found){
                        nSub++;
                        i += lenSub;
                    }
                }
            }
        }
        updatedW[index] = word[i];
        index++;
    }

    updatedW[index] = '\0';
    strcpy(word, updatedW);
    free(updatedW);
}

/*
int main(void){
    char word[] = "foo bar loop hoop";
    lookBehind("l", "oo", word);
    assert(0 == strcmp("foo bar lp hoop", word));
    lookBehind("o", "o", word);
    assert(0 == strcmp("fo bar lp hop", word));

    char word3[] = "CS137 137";
    lookBehind("CS", "137", word3);
    assert(0 == strcmp("CS 137", word3));
    char word3b[] = "CS137137";
    lookBehind("CS", "137", word3b);
    assert(0 == strcmp("CS", word3b));

    char word4[] = "111111";
    lookBehind("1", "1", word4);
    assert(0 == strcmp("1", word4));

    char word5[] = "wow";
    lookBehind("", "w", word5);
    assert(0 == strcmp("o", word5));

    char word6[] = "wow";
    lookBehind("w", "", word6);
    assert(0 == strcmp("wow", word6));

    return 0;
} */
