#include "vlinteger.h"
#include <stdlib.h>
#include <stdio.h>

struct linteger *vlintegerCreate(void)
{
	struct linteger *t1 = malloc(sizeof(struct linteger));
	t1->arr = NULL;
	t1->length = 0;	// no values in t1.
	return t1;
}

void vlintegerPrint(struct linteger *t1)
{
	printf("length=%d\n", t1->length);
	for (int i = 0; i < t1->length; ++i){
		printf("%d", t1->arr[i]);
	}
	printf("\n");
}

void vlintegerDestroy(struct linteger *t1)
{
	if (t1){
		free(t1->arr);	// free the inside array first
		free(t1);	// then free the structure
	}
}

void vlintegerRead(struct linteger *t1)
{
    int num;
    int *temp;
    while(scanf("%d", &num) == 1){
        temp = realloc(t1->arr, (t1->length + 1) * sizeof(int));
        t1->arr = temp;
        t1->arr[t1->length] = num;
        t1->length++;
    }
}

int max(int x, int y){
	return x > y? x: y;
}


struct linteger *vlintegerAdd(struct linteger *t1, struct linteger *t2){	
    int lenOne = t1->length;
    int lenTwo = t2->length;
    int maxL = max(lenOne, lenTwo);
    int carry = 0;

    struct linteger *result = vlintegerCreate();
    result->arr = calloc(maxL + 1, sizeof(int)); // Using calloc for initialization

    for (int i = 1; i <= maxL; i++) {
        int a = 0;
        int b = 0;

        if (i <= lenOne) {
            a = t1->arr[lenOne - i];
        }

        if (i <= lenTwo) {
            b = t2->arr[lenTwo - i];
        }

        int sum = a + b + carry;
        result->arr[maxL - i + 1] = sum % 10; // Adjust index for potential carry
        carry = sum / 10;
    }

    if (carry > 0) {
        result->arr[0] = carry;
        result->length = maxL + 1;
    } else {
        // Shift the digits to remove the leading zero if no carry
        for (int i = 0; i < maxL; i++) {
            result->arr[i] = result->arr[i + 1];
        }
        result->length = maxL;
    }
    return result;
} 

struct linteger *vlintegerMult(struct linteger *t1, struct linteger *t2) {
    struct linteger *result = vlintegerCreate();
    int maxL = t1->length + t2->length;
    result->arr = calloc(maxL, sizeof(int));
    result->length = maxL;

    for (int i = t1->length-1; i >= 0; i--) {
        for (int j = t2->length-1; j >= 0; j--) {
            int index = i + j + 1;
            result->arr[index] += t1->arr[i] * t2->arr[j];
            result->arr[index - 1] += result->arr[index] / 10;
            result->arr[index] = result->arr[index] % 10;
        }
    }

    if (result->arr[0] == 0) {
        for (int i = 0; i < result->length - 1; i++) {
            result->arr[i] = result->arr[i + 1];
        }
        result->length -= 1;
    }

    return result;
}
