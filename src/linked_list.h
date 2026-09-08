#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

void linked_list_init(LinkedList *list);
void linked_list_insert_front(LinkedList *list, int value);
void linked_list_insert_back(LinkedList *list, int value);
int linked_list_find(LinkedList *list, int value);
int linked_list_get(LinkedList *list, int index);
void linked_list_remove_front(LinkedList *list);
void linked_list_free_collection(LinkedList *list);

#endif
