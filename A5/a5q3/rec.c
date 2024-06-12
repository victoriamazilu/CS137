#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Point{
	int x;
	int y;
} point;

typedef struct Rectangle {
   point bottomLeft;
   int width;
   int height;
} rectangle;

int min(int x, int y) {
    return x < y? x: y;
}

int max(int x, int y) {
    return x > y? x: y;
}

int isIntersection(rectangle rects[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if((rects[i].width - (abs(rects[i].bottomLeft.y - rects[i+1].bottomLeft.y))) <= 0){
            return 0;
        } else{
            if((max(rects[i].height, rects[i+1].height) - (abs(rects[i].bottomLeft.y - rects[i+1].bottomLeft.y))) <= 0){
                return 0;
            }
        }
    }
    return 1;
}

rectangle intersection(rectangle rects[], int n){
	if (!isIntersection(rects, n)) {
        rectangle result = {{0, 0}, 0, 0};
        return result; // Empty intersection
    }

    // Find the initial intersection using the first rectangle
    rectangle result = rects[0];

    for (int i = 0; i < n - 1; i++) {
        result.bottomLeft.x = rects[i].bottomLeft.x > rects[i+1].bottomLeft.x? rects[i].bottomLeft.x: rects[i+1].bottomLeft.x;
        result.bottomLeft.y = rects[i].bottomLeft.y > rects[i+1].bottomLeft.y? rects[i].bottomLeft.y: rects[i+1].bottomLeft.y;
        result.width = rects[i].width < rects[i+1].width? rects[i].width: rects[i+1].width;
        result.height = rects[i].height < rects[i+1].height? rects[i].height: rects[i+1].height;
    }

    return result;
    
}

/*int main(){
	
	rectangle result;

	rectangle r = {{2,6},3,4};
	rectangle s = {{0,7},7,1};
	rectangle t = {{3,5},1,6};
	rectangle u = {{5,6},3,4};
	
	// Test 1
	rectangle rects1[2] = {r, s};
	result = intersection(rects1, 2);
	
	assert(result.bottomLeft.x == 2);
	assert(result.bottomLeft.y == 7);
	assert(result.width == 3);
	assert(result.height == 1);
	

	// Test 2
	rectangle rects2[3] = {r, s, t};
	result = intersection(rects2, 3);
	assert(result.bottomLeft.x == 3);
	assert(result.bottomLeft.y == 7);
	assert(result.width == 1);
	assert(result.height == 1);
	
	
	// Test 3
	rectangle rects3[4] = {r, s, t, u};
	result = intersection(rects3, 4);
	assert(result.bottomLeft.x == 0);
	assert(result.bottomLeft.y == 0);
	assert(result.width == 0);
	assert(result.height == 0);


	return 0;
} */
