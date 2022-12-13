#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DblLinkedList {
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList() {
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
