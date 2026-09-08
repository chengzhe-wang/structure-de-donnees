#include <stdio.h>

#include "../src/linked_list.h"

int main(void)
{
    LinkedList list;
    linked_list_init(&list);

    printf("Après initialisation : taille = %d\n", list.size);

    linked_list_insert_back(&list, 10);
    linked_list_insert_front(&list, 20);
    linked_list_insert_front(&list, 30);
    linked_list_insert_back(&list, 40);

    printf("Après les insertions : taille = %d\n", list.size);
    printf("Liste : ");

    Node *current = list.head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    linked_list_remove_front(&list);

    printf("Après remove_front : taille = %d\n", list.size);
    printf("Liste : ");

    current = list.head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    linked_list_free_collection(&list);

    return 0;
}
