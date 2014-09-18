#ifndef __TREE_H__
#define __TREE_H__

struct Tree;

struct Tree* tree_create();
struct Tree* tree_first_child(struct Tree *tree);
struct Tree* tree_next_sibling(struct Tree *tree);

void tree_destroy();
void tree_add_sorted(struct Tree *tree, void *data);
int tree_size(struct Tree *tree);
void* tree_data(struct Tree *tree);





#endif //__TREE_H__
