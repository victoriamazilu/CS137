#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct dlnode{
	int data;
	struct dlnode *next;
	struct dlnode *prev;
}dlnode;

typedef struct ndlst{
	dlnode *head;	//points to the first element otherwise NULL
	dlnode *tail;	//points to the last element otherwise NULL
	int len;	// number of elements
}ndlst;

//Pre: None
//Post: Creates a null list
ndlst *dlistCreate(void){
	ndlst *ret = malloc(sizeof(ndlst));
	ret->head = NULL;
	ret->tail = NULL;
	ret->len = 0;
	return ret;
}

//Pre: lst is a valid list ( even null )
//Post: Destroys the list
void dlistDestroy(ndlst *lst){
	dlnode *nextDelete = lst -> tail;
	dlnode *curDelete = NULL;
	while(nextDelete){
		curDelete = nextDelete;
		nextDelete = curDelete -> prev;
		free(curDelete);
	}
	free(lst);
}

//Pre: lst is valid
//Post: returns the number of elements in the list
int dlistLength(ndlst *lst){
	return lst -> len;
}

//Pre: lst is a valid list with length of at least n
//Post: nth item removed
void dlistRemoveElem(ndlst *lst, int n){
	if (lst->head == NULL || n < 1 || n > lst->len) {
        // Invalid request, return early
        return;
    }
	
	dlnode *curPos = lst->head;
    for (int i = 1; i < n; i++) {
        curPos = curPos->next;
    }
	
	if(n == 1){ // elem is at start
        lst->head = curPos->next;
        if (lst->head != NULL) {
            lst->head->prev = NULL;
        }
        if (lst->len == 1) {
            lst->tail = NULL;
        }
    } else if(n == lst->len){ // elem is at end
        lst->tail = curPos->prev;
        if (lst->tail != NULL) {
            lst->tail->next = NULL;
        }
    } else{ // somewhere in the middle
        curPos->prev->next = curPos->next;
        curPos->next->prev = curPos->prev;
    }

    free(curPos);
    lst->len--;

}

// lst is a valid list
void dlistAddToFront(ndlst *lst, int elem){
    dlnode *node = malloc(sizeof(dlnode));
    node->data = elem;
    node->next = lst->head;
    node->prev = NULL;

    if (lst->head != NULL) {
        lst->head->prev = node;
    }

    lst->head = node;
    if (lst->tail == NULL) {
        lst->tail = node;
    }

    lst->len++;
}


// lst is a valid list
void dlistAddToEnd(ndlst *lst, int elem){
	dlnode *node = malloc(sizeof(dlnode));
    node -> data = elem;
    node -> next = NULL;
    if (lst->tail != NULL) {
        lst -> tail -> next = node;
		node -> prev = lst -> tail;
    } else {
        lst -> head = node; // If the list was empty, the new node is now the head as well.
		node -> prev = NULL;
		node -> next = NULL;
    }
    
    lst -> tail = node; // The new node is always the new tail.
    lst -> len++;
}

//Pre: lst is valid
//prints the items in the list from start to end.
/*void dlistPrint(ndlst *lst){
	dlnode *node = lst->head;
	// iterate over the nodes (items) until node is NULL 
	// and print the data
	for (; node; node = node->next)
		printf("%d  ", node->data);
	printf("\n");
}

void dlistPrintReverse(ndlst *lst){
	dlnode *node = lst->tail;
	// iterate over the nodes (items) until node is NULL 
	// and print the data
	for (; node; node = node->prev)
		printf("%d  ", node->data);
	printf("\n");
} */

// lst is a valid list, to be sorted in ascending order
void dlistSort(ndlst *lst){
    int sorted;
	int i;
    dlnode *origHead = lst -> head;
    dlnode *temp = NULL;

    if(origHead == NULL){
        return;
    }

    do{
        sorted = 0;
        origHead = lst->head;

        while(origHead->next != temp) {
            if((origHead -> data) > (origHead -> next -> data)) {
				sorted = 1;
                int t = origHead -> data;
                origHead -> data = origHead -> next -> data;
                origHead -> next -> data = t;
            }
            origHead = origHead -> next;
        }
        temp = origHead;
    } while(sorted);
}


// rotate the list n times to the left, assume, list not empty
void dlistRotateLeft(ndlst *lst, int n){
    dlnode *origHead = NULL;

    for (int i = 0; i < n; i++) {
        origHead = lst->head; 
        lst->head = origHead->next;
        lst->head->prev = NULL;

        lst->tail->next = origHead; 
        origHead->prev = lst->tail; 
        origHead->next = NULL;

        lst->tail = origHead; 
    }
}


// rotate the list n times to the right, assume, lst not empty
void dlistRotateRight(ndlst *lst, int n){
    dlnode *origTail = NULL;

    for (int i = 0; i < n; i++) {
        origTail = lst -> tail;
        lst -> tail = origTail -> prev; 
        lst -> tail -> next = NULL; 

        origTail -> next = lst -> head; 
        lst -> head -> prev = origTail; 
        lst -> head = origTail; 
        origTail -> prev = NULL; 
    }
}

/*
int main(void){
	ndlst *lst1 = dlistCreate();
	assert(dlistLength(lst1) == lst1->len);
	assert(dlistLength(lst1) == 0);
	dlistAddToEnd(lst1, 10);
	dlistAddToFront(lst1, -20);
	dlistAddToFront(lst1, 0);
	dlistAddToEnd(lst1, 9);
	dlistAddToFront(lst1, -9);
	dlistAddToFront(lst1, 7);
	dlistAddToEnd(lst1, 40);
	assert(dlistLength(lst1) == lst1->len);
	assert(dlistLength(lst1) == 7);
	dlistPrint(lst1);
	dlistPrintReverse(lst1);
	dlistRemoveElem(lst1, 5);
	dlistRemoveElem(lst1, 1);
	dlistRemoveElem(lst1, 5);
	dlistAddToEnd(lst1, 100);
	assert(dlistLength(lst1) == lst1->len);
	assert(dlistLength(lst1) == 5);
	dlistPrint(lst1);
	dlistPrintReverse(lst1);
	dlistSort(lst1);
	dlistPrint(lst1);
	dlistRotateLeft(lst1, 2);
	dlistPrint(lst1);
	dlistRotateRight(lst1, 3);
	dlistPrint(lst1);
	dlistDestroy(lst1);

     // should add more tests
	return 0;
} */
