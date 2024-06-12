#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//function to check if a substring s[start...end] is a palindrome
bool is_palindrome(char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

//helper function to recursively check for semidrome starting from 'start'
bool check_for_semidrome(char *s, int start) {
    int length = strlen(s);
    if ((length - start) < 2) {
        return false;
    } else if (is_palindrome(s, start, length - 1)) {
        return true;
    }

    for (int i = 1; i < length - start; i++) {
        if (is_palindrome(s, start, start + i) && check_for_semidrome(s, start + i + 1)) {
            return true;
        }
    } 
    return false;
}

//main function to check if the string s is a semidrome
bool is_semidrome(char *s) {
    int length = strlen(s);
    if (length < 2) { 
        return false;
    } else if (is_palindrome(s, 0, length - 1)) {
        return true;
    }

    for (int i = 1; i < length; i++) {
        if (is_palindrome(s, 0, i)) {
            if (check_for_semidrome(s, i + 1)) {
                return true;
            }
        }
    }
    return false; 
}

/*int main(void){

    assert(is_semidrome("popeye"));
	assert(is_semidrome("racecar"));
	assert(!is_semidrome("aab"));
	assert(is_semidrome("abcba"));
    assert(is_semidrome("aacaa"));
    assert(is_semidrome("aaccbb"));
    assert(!is_semidrome("aaccbbo"));
    assert(!is_semidrome("abcd"));
    assert(!is_semidrome("abab"));
	
    return 0;
}*/

