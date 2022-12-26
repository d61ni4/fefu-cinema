#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


typedef struct Film {
    wchar_t* title;
    wchar_t* year;
    wchar_t* origin;
    wchar_t* genre;
    wchar_t* rating;
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

Film* filmInit() {
    Film* film = (Film*)malloc(sizeof(Film));
    film->title = (wchar_t*)malloc(sizeof(wchar_t)*100);
    film->year = (wchar_t*)malloc(sizeof(wchar_t)*100);
    film->origin = (wchar_t*)malloc(sizeof(wchar_t)*100);
    film->genre = (wchar_t*)malloc(sizeof(wchar_t)*100);
    film->rating = (wchar_t*)malloc(sizeof(wchar_t)*100);
    return film;
}

Film* getFilm(FILE* films) {
    Film* film = filmInit();
    if (fgetws(film->title, 100,films) != NULL) {

        fgetws(film->year, 100,films);

        fgetws(film->origin, 100,films);

        fgetws(film->genre, 100,films);

        fgetws(film->rating, 100,films);

    } else {
        //printf("Ne prokanaklo)");
        return NULL;
    }
    return film;
}

DblLinkedList* getFilms() {

    FILE* films = fopen("films.txt", "r");
    DblLinkedList* filmsList = createDblLinkedList();

    Film* film = getFilm(films);

    while(film != NULL) {
        push(filmsList, *film);
        //printf("Added %ls", film->year);
        film = getFilm(films);
    }
    return filmsList;
}

void circleList (DblLinkedList* list) {
    list->tail->next = list->head;
    list->head->prev = list->tail;
}

void printFilm(Film* film) {
    printf("Title: %ls", film->title);
    printf("Year: %ls", film->year);
    printf("Origin: %ls", film->origin);
    printf("Genre: %ls", film->genre);
    printf("Rating: %ls", film->rating);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    DblLinkedList* films = getFilms();
    printf("%d", films->size);
    circleList(films);
    printFilm(&films->head->value);
}
