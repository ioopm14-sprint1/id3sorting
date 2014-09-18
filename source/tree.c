#include "tree.h"

struct Tree {
  struct Tree *next_sibling;
  struct Tree *first_child;
  void *data;
};


struct Tree* tree_create() {
  struct Tree *tree = malloc(sizeof(struct Tree));
  
  if (tree) {
    tree->next_sibling = NULL;
    tree->first_child = NULL;
    tree->data = NULL;
  }
  return tree;
}

struct Tree* tree_first_child(struct Tree *tree) {
  if (tree != NULL) {
    return tree->first_child;
  }
  return NULL;
}

struct Tree* tree_next_sibling(struct Tree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  return tree->next_sibling;
}

void tree_destroy();
void tree_add_sorted(struct Tree *tree, void *data);
int tree_size(struct Tree *tree);
void* tree_data(struct Tree *tree); 
