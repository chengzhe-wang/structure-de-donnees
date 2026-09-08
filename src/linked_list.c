#include "linked_list.h"
#include <stdlib.h>

void linked_list_init(LinkedList *list){
    list->head = NULL;
    list->size = 0;
}

void linked_list_insert_front(LinkedList *list, int value){
    Node *new_node = malloc(sizeof(Node));

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;

    list->size++;
}

void linked_list_insert_back(LinkedList *list, int value){
    if(list == NULL){
        return;
    }

    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        return;
    }

    new_node->value = value;
    new_node->next = NULL;

    if(list->head == NULL){
        list->head = new_node;
    }
    else{
        Node *current = list->head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
}

int linked_list_find(LinkedList *list, int value){
    Node *current = list->head;

    int count = 0;

    while (current != NULL){
        if(current->value == value){
            break;
            
        }
        else{
            current = current->next;
            count++;
        }
        count = -1;
    }

    return count;
    
}


int linked_list_get(LinkedList *list, int index){
    int result = 0;
    int count = 0;
    Node *current = list->head;
    
    while(count <= index){
        if(count == index){
            return count;
        }
        current = current->next;
        count++;
    }

    return -1;
}

void linked_list_remove_front(LinkedList *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    Node *old_head = list->head;

    list->head = old_head->next;
    free(old_head);
    list->size--;
}

void linked_list_free_collection(LinkedList *list) {
    Node *current = list->head;

    while (current != NULL) {
        Node *next = current->next;

        free(current);

        current = next;
    }
}
