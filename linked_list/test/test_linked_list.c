#include "test_linked_list.h"
#include "../source/linked_list.h"
#include "test.h"


static void *ONE   = (void*)1;
static void *TWO   = (void*)2;
static void *THREE = (void*)3;


bool test_create_list() {
    struct List *list = list_create();

    if (list && list_size(list) == 0) {
        list_destroy(&list);
        return true;
    }
    return false;
}

bool test_append_to_list() {
    struct List *list = list_create();
    list_append(list, ONE);

    if (list_size(list) == 1) {
        list_destroy(&list);
        return true;
    }

    list_destroy(&list);
    return false;
}

bool test_multiple_values_in_list() {
    struct List *list = list_create();
    list_prepend(list, ONE);
    list_prepend(list, TWO);
    list_prepend(list, THREE);

    if (list_size(list) == 3) {
        list_destroy(&list);
        return true;
    }

    list_destroy(&list);
    return false;
}

bool test_it_keep_values_in_added_order() {
    struct List *list = list_create();
    list_prepend(list, TWO);
    list_append(list, THREE);
    list_prepend(list, ONE);

    if ((node_data(list_at(list, 0)) == ONE) &&
        (node_data(list_at(list, 1)) == TWO) &&
        (node_data(list_at(list, 2)) == THREE)) {
            list_destroy(&list);
            return true;
    }

    list_destroy(&list);
    return false;
}

bool test_it_finds_values() {
    struct List *list = list_create();
    list_append(list, ONE);
    list_append(list, TWO);
    list_append(list, THREE);

    void* NOT_IN_LIST = (void*)42;

    if ((node_data(list_find(list, ONE)) == ONE) &&
        (node_data(list_find(list, TWO)) == TWO) &&
        (node_data(list_find(list, THREE)) == THREE) &&
            list_find(list, NOT_IN_LIST) == NULL) {
            list_destroy(&list);
        return true;
    }

    return false;
}

bool test_it_deletes_values() {
    struct List *list = list_create();
    list_append(list, THREE);
    list_append(list, TWO);
    list_append(list, ONE);

    // delete last element
    if (node_data(list_find(list, ONE)) != ONE || list_size(list) != 3) {
        list_destroy(&list);
        return false;
    }
    list_delete(list, ONE);

    if (list_find(list, ONE) != NULL || node_data(list_first(list)) != THREE || node_data(list_last(list)) != TWO) {
        list_destroy(&list);
        return false;
    }

    // delete last element
    if (node_data(list_find(list, TWO)) != TWO || list_size(list) != 2) {
        list_destroy(&list);
        return false;
    }
    list_delete(list, TWO);

    if (list_find(list, TWO) != NULL || node_data(list_first(list)) != THREE || node_data(list_last(list)) != THREE) {
        list_destroy(&list);
        return false;
    }

    // delete last element
    if (node_data(list_find(list, THREE)) != THREE || list_size(list) != 1) {
        list_destroy(&list);
        return false;
    }
    list_delete(list, THREE);

    if (list_find(list, THREE) != NULL || list_size(list) != 0) {
        list_destroy(&list);
        return false;
    }

    list_destroy(&list);

    return true;
}


void test_linked_list() {
    RUN_TEST(test_create_list);
    RUN_TEST(test_append_to_list);
    RUN_TEST(test_multiple_values_in_list);
    RUN_TEST(test_it_keep_values_in_added_order);
    RUN_TEST(test_it_finds_values);
    RUN_TEST(test_it_deletes_values);
}
