#include <stdio.h>
#include <stdlib.h>


typedef struct Film {
    char* title;
    int year;
    char* origin;
    char* genre;
    float rating;
} Film;

typedef struct Node {
    Film value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DblLinkedList {
    int size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList() {
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void push(DblLinkedList *list, Film data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}


Film pop(DblLinkedList *list) {
    Node *prev;
    Film tmp;
    if (list->head == NULL) {
        exit(2);
    }
    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
    return tmp;
}

void pushBack(DblLinkedList *list, Film value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

Film popBack(DblLinkedList *list) {
    Node *next;
    Film tmp;
    if (list->tail == NULL) {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    list->size--;
    return tmp;
}

void circleList (DblLinkedList* list) {
    list->tail->next = list->head;
    list->head->prev = list->tail;
}

int main() {
    return 0;
}
