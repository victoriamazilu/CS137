#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

char *merge(char *s1, char *s2) {
    char *res = malloc(strlen(s1) + strlen(s2) + 2);
    int resIndex = 0;
    int s1Index = 0, s2Index = 0;
    int isComplete1 = false, isComplete2 = false;

    while (!(isComplete1 && isComplete2)) {
        //process s1
        while (s1[s1Index] != '\0' && s1[s1Index] != ' ') {
            res[resIndex++] = s1[s1Index++];
        }

        if (s1[s1Index] == ' ' && !isComplete1){
            res[resIndex++] = s1[s1Index++];
        } else{
            isComplete1 = true;
        }

        if ((isComplete1 && !isComplete2) && (res[resIndex - 1] != ' ')){
            res[resIndex++] = ' ';
        }


        //process s2
        while (s2[s2Index] != '\0' && s2[s2Index] != ' ') {
            res[resIndex++] = s2[s2Index++];
        }

        if (s2[s2Index] == ' ' && !isComplete2){
            res[resIndex++] = s2[s2Index++];
        } else{
            isComplete2 = true;
        }

        if ((!isComplete1 && isComplete2) && (res[resIndex - 1] != ' ')){
            res[resIndex++] = ' ';
        }
    }   


    res[resIndex] = '\0';
    return res;
}

/*
int main(void)
{
    char s1[] = "The brown jumps the dog";
    char s2[] = "quick fox over lazy";
    char *s = merge(s1, s2);
    assert(!strcmp(s, "The quick brown fox jumps over the lazy dog"));
    free(s);
    char s3[] = "the brown";
    char s4[] = "quick fox is sleeping today";
    s = merge(s3, s4);
    assert(!strcmp(s, "the quick brown fox is sleeping today"));
    free(s);
    char *s5 = "happy to you";
    char *s6 = "birthday";
    s = merge(s5, s6);
    assert(!strcmp(s, "happy birthday to you"));
    free(s);
    return 0;
} */
