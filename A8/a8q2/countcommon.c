#include <stdio.h>
#include <assert.h>

int count_common(int a[], int n1, int b[], int n2) {
    int counted[10] = {0}; //keep track of counted digits
    int count = 0;
    int i = 0, j = 0;

    while (i < n1 && j < n2) {
        if (a[i] < b[j]) { //since the arrays are in increasing orders
            i++;
        } else if (b[j] < a[i]) {
            j++;
        } else {
            //if digit has not been counted yet, increment the count
            if (counted[a[i]] == 0) {
                count++;
                counted[a[i]] = 1; //mark digit as counted
            }
            //move past all identical elements in both arrays
            int val = a[i];
            while (i < n1 && a[i] == val) i++;
            while (j < n2 && b[j] == val) j++;
        }
    }

    return count;
}


/*int main(void){
    int a1[4] = {1,1,1,1};
    int b1[8] = {1,1,1,1,1,1,1,1};
    assert(1 == count_common(a1,4,b1,8));
    int a2[8] = {1,3,3,4,5,8,9,100};
    int b2[7] = {4,4,8,15,20,40,100};
    assert(3 == count_common(a2,8,b2,7));
    return 0;
}*/