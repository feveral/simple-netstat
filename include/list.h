
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct listCell {
    void *value;
    struct listCell *next; 
    size_t size;
} ListCell;

typedef struct list {
    ListCell *head;
    ListCell *tail;
    int count;
} List;

List* listNew();
void listAppend(List *list, ListCell *cell);
void listAppendString(List *list, char *);
void listForEach(List *list, void (*func)(void *));
ListCell* listGet(List *list, int index);

#endif