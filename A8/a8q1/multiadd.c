#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void firstMult(long long int arr[], long long int products[], int length){
    long long int firstIndex = 0;
    long long int secondIndex = 0;

    for (int i = 0; i < length; i++) {
        while (arr[firstIndex] == 0) {
            firstIndex++;
        }
        arr[firstIndex]--; // Decrement the found non-zero element

        // Find the next non-zero element starting from secondIndex
        while (arr[secondIndex] == 0) {
            secondIndex++;
        }
        arr[secondIndex]--; // Decrement the found non-zero element

        // Store the product of the two indices
        products[i] = firstIndex * secondIndex;
    }
}

void add(long long int a[],int n){
    for (int i = 0; i < n; i++){
        a[i]= a[i + i] + a[i + i + 1];
    }
}

void mult(long long int a[],int n){
    for(int i = 0; i < n; i++){
        a[i]= a[i + i] * a[i + i + 1];
    }
}

long long int multiadd(long long int a[], int n){
    if(n == 2){
        return a[0] * a[1];
    }

    long long int *res = calloc(n + 1, sizeof(long long int));
    
    for (int i = 0; i < n; i++){
        res[a[i]]++;
    }

    n /= 2;

    firstMult(res, a, n);
    while(n > 1){
        n /= 2;
        add(a, n);
    
        if(n == 1){
            break;
        } else{
            n /= 2;
            mult(a, n);
        }
    }

    free(res);
    return a[0];
}

/* sint main(void){
    long long int a[8] = {1,4,3,6,5,3,2,8};
    assert(748 == multiadd(a,8));
    long long int b[16] = {0};
    assert(0 == multiadd(b,16));
    long long int c[16] = {1,6,5,8,6,7,5,4,8,9,10,2,12,14,1,1};
    assert(27498 == multiadd(c,16));
    
    return 0;
} */