#include "linked_list.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    struct Node *next;
    void *data;
};

struct Node* node_create() {
    struct Node *node = malloc(sizeof(struct Node));
    assert(node);
    node->next = NULL;
    node->data = NULL;
    return node;
}

void node_destroy(struct Node **node) {
    assert(node && *node);
    free(*node);
    *node = NULL;
}



struct List {
    struct Node *first;
    struct Node *last;
    int size;
};

struct List* list_create() {
    struct List *list = malloc(sizeof(struct List));
    assert(list != NULL);

    list->first = NULL;
    list->last  = NULL;
    list->size  = 0;
    //memset(list, 0, sizeof(struct List));
    return list;
}

void list_destroy(struct List **list) {
    assert(list && *list);

    struct Node *iterator = (*list)->first;
    struct Node *node = NULL;

    while (iterator != NULL) {
        node = iterator;
        iterator = iterator->next;
        node_destroy(&node);
    }

    (*list)->first = NULL;
    (*list)->last  = NULL;
    (*list)->size  = 0;
    free(*list);
    *list = NULL;
}

int list_size(struct List *list) {
    assert(list != NULL);
    return list->size;
}


void list_prepend(struct List *list, void *data) {

    struct Node *node = node_create();
    assert(list != NULL && node != NULL);

    node->data  = data;
    node->next  = list->first;
    list->first = node;
    list->size += 1;

    // list is empty
    if (list->last ==  NULL) {
        list->last = node;
    }
}

void list_append(struct List *list, void *data) {

    struct Node *node = node_create();
    assert(list != NULL && node != NULL);

    if (list->first && list->last) {
        list->last->next = node;
    } else { // list is empty
        list->first = node;
    }

    node->data = data;
    node->next = NULL;
    list->last = node;
    list->size += 1;
}

struct Node* list_at(struct List *list, int index) {
    assert(list != NULL && index >= 0);
    struct Node *iterator = list->first;

    while (iterator && index > 0) {
        iterator = iterator->next;
        index--;
    }
    return iterator;
}

struct Node* list_find(struct List *list, void *data) {
    assert(list != NULL);
    struct Node *iterator = list->first;

    while(iterator && iterator->data != data) {
        iterator = iterator->next;
    }
    return iterator;
}


void list_delete(struct List *list, void *data) {

    assert(list != NULL);

    struct Node *prev = list->first;
    struct Node *iterator = list->first;

    while (iterator && iterator->data != data) {
        prev = iterator;
        iterator = iterator->next;
    }

    if (iterator != NULL) {
        if (iterator == list->first) {
            list->first = list->first->next;
            node_destroy(&iterator);
        } else {
            if (iterator == list->last) {
                list->last = prev;
            }
            prev->next = iterator->next;
            node_destroy(&iterator);
        }
        list->size -= 1;
    }
}


struct Node* list_first(struct List *list) {
    assert(list != NULL);
    return list->first;
}

struct Node* list_last(struct List *list) {
    assert(list != NULL);
    return list->last;
}


void* node_data(struct Node *node) {
    assert(node != NULL);
    return node->data;
}

struct Node* node_next(struct Node *node) {
    assert(node != NULL);
    return node->next;
}
