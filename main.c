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
    printf("Size %d, data %d", list->size, list->head->next->next->next->value);
    return 0;
}
