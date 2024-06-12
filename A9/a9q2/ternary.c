#include <stdio.h>
#include <assert.h>

int ternarylastsearch(int L[], int len, int target) {
    int beginning = 0;
    int end = len - 1;
    int index = -1; // Initialize index to -1 to indicate not found

    while (beginning <= end) {
        int mid1 = beginning + (end - beginning) / 3;
        int mid2 = end - (end - beginning) / 3;

        printf("Examining indices %d and %d\n", mid1, mid2);

        if(target == L[mid2]){
            index = mid2; 
            beginning = mid2 + 1;
        } else if(target == L[mid1]) {
            index = mid1;
            if(mid1 + 1 == mid2) { //if mid2 is the next element after mid1, move beginning past mid2
                beginning = mid2 + 1;
            } else{ //move beginning to mid1 + 1 to examine the next segment
                beginning = mid1 + 1;
                end = mid2 - 1; //adjust end
            }
        } else{
            if (target > L[mid2]) {
                beginning = mid2 + 1;
            } else if (target < L[mid1]) {
                end = mid1 - 1;
            } else { //target is between mid1 and mid2
                beginning = mid1 + 1;
                end = mid2 - 1;
            }
        }

        //narrowing down to a single element, check if it's the target
        if (beginning == end && L[beginning] == target) {
            printf("Examining indices %d and %d\n", beginning, end);
            index = beginning;
            break;
        }
    }

    return index;
}


/*
int main(void) {
   
    int a[10] = {1, 2, 3, 4, 5, 6, 6, 6, 9, 100};
    assert(7 == ternarylastsearch(a,10,6));
	printf("\n");
	int a2[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    assert(-1 == ternarylastsearch(a2,10,100));
	printf("\n");
	assert(-1 == ternarylastsearch(a2,10,11));
	printf("\n");
	assert(0 == ternarylastsearch(a2,10,2));
	printf("\n");
	int a3[12] = {6,6,6,6,6,6,6,6,6,6,6,6};
    assert(11 == ternarylastsearch(a3,12,6));

    return 0;
} */


