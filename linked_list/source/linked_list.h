#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

struct List;
struct Node;

struct List*    list_create();
void            list_destroy(struct List **list);
int             list_size(struct List *list);
void            list_append(struct List *list, void* data);
void            list_prepend(struct List *list, void* data);
struct Node*    list_at(struct List *list, int index);
struct Node*    list_find(struct List *list, void *data);
void            list_delete(struct List *list, void *data);
struct Node*    list_first(struct List *list);
struct Node*    list_last(struct List *list);


void*           node_data(struct Node *node);
struct Node*    node_next(struct Node *node);


#endif // __LINKED_LIST_H__
