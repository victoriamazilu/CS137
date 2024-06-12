#include <stdio.h>

void printarr(int a[], int len){
    for (int i=0; i<len-1; i++)
       printf("%d ", a[i]);
    printf("%d\n", a[len-1]);
} 

void doubleselectionsort(int a[], int len){
int startPos = 0;
    int endPos = len - 1;

    while(startPos < endPos) {
        int min = a[startPos];
        int max = a[startPos];
        int minIn = startPos;
        int maxIn = startPos;

        for(int k = startPos; k <= endPos; k++){
            if(a[k] < min){
                min = a[k];
                minIn = k;
            }
            if(a[k] > max){
                max = a[k];
                maxIn = k;
            }
        }

        //swap min with the starting pos
        int temp = a[startPos];
        a[startPos] = a[minIn];
        a[minIn] = temp;

        //update maxIn in case min was swapped from the max pos
        if (maxIn == startPos) {
            maxIn = minIn;
        }
        
        //swap max with end pos
        temp = a[endPos];
        a[endPos] = a[maxIn];
        a[maxIn] = temp;

        //move towards the inside of the arr
        startPos++;
        endPos--;

        printarr(a, len);
    }
}

/*
int main(void) {
   
    int a[7] = {4, 4, 4, 0, 0, -10, -10};
    doubleselectionsort(a,7);
    int a2[5] = {6, 11, 2, -4, -1};
    doubleselectionsort(a2,5);
    int a3[10] = {1, 8, 5, 4, 6, 2, 5, 6, 2, 9};
    doubleselectionsort(a3,10);
    
    return 0;
} */
