#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Person{
    int id;
    int speed;
    struct Person* next;
}Person;

Person updatePerson(int id, int speed){
    Person per;
    per.id = id;
    per.speed = speed;
    return per;
}

void addPerson(Person** start, Person* new) {
    if(*start == NULL){
        new -> next = new;
        *start = new;
    } else{ //list is not empty and must add to the end of the list
        Person *cur = *start;
        while(cur -> next != *start){
            cur = cur -> next;
        }
        cur -> next = new;
        new -> next = *start;
    }
}

// Returns the winner
Person* play(Person* start) {
    Person* current = start;
    Person* it = start;
    Person* previous;
    int ducknum;
    int length = 1;
    Person* count= it -> next;
    while (count != it){
        length++;
        count = count -> next;
    }
    it = start;
    while (length > 1){
        ducknum = it -> id;
        previous= it;
        if (it -> id == current -> id) {
            current = current -> next;
        }

        while (ducknum > 0){
            if (it -> id == current -> id){
                current = current -> next;
            }
            printf("%d duck %d\n", it -> id, current -> id);
            ducknum--;
            previous = current;
            if (length!=2){
                current = current->next;
            }
        }
        if (it -> id == current -> id){
            current = current->next;
        }
        if (it -> speed > current -> speed){
            if (it -> id == current -> id){
                current = current -> next;
            }
            printf("%d goose! %d\n",it->id,current->id);
            Person* now = current;
            while (now -> next != current) {
                now = now -> next;
            }
            now -> next = current -> next;
            free(current);
            current = it -> next;
        }else if (it -> speed <= current -> speed){
            if (it -> id == current -> id) {
                current = current -> next;
            }
            printf("%d goose! %d\n", it -> id, current -> id);
            Person* now = it;
            while (now -> next != it) {
                now = now -> next;
            }
            now -> next = it -> next;
            free(it);
            it = current;
            current = it -> next;
        }
        length--;
    }
    printf("winner! %d\n", it -> id);
    return it;
} 

/*
int main(){
    int p, s;

    // List of people
    Person* lop = NULL;

    // Read in participants
    while (scanf("%d %d", &p, &s) == 2){
        Person* np = (Person*)malloc(sizeof(Person));
        *np = updatePerson(p, s);
        addPerson(&lop, np);
    }

    Person* winner = play(lop);
    free(winner);
} */