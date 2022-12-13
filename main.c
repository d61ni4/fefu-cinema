#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
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

void push(DblLinkedList *list, int data) {
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


int pop(DblLinkedList *list) {
    Node *prev;
    int tmp;
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

void pushBack(DblLinkedList *list, int value) {
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

int popBack(DblLinkedList *list) {
    Node *next;
    int tmp;
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
    DblLinkedList* list = createDblLinkedList();
    push(list, 5);
    push(list, 10);
    push(list, 15);
    circleList(list);
    printf("Size %d, data %d\n", list->size, list->head->next->value);
    printf("Size %d, data %d\n", list->size, list->head->next->next->value);
    printf("Size %d, data %d\n", list->size, list->head->next->next->next->value);
    int n = pop(list);
    printf("%d", n);
    printf("Size %d, data %d\n", list->size, list->head->next->next->value);
    pushBack(list, 7);
    printf("Size %d, data %d\n", list->size, list->tail->value);
    n = popBack(list);
    printf("%d %d", n, list->size);

    return 0;
}
