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

    printf("Find 20 : %d (attendu : 1)\n", linked_list_find(&list, 20));
    printf("Find 99 : %d (attendu : -1)\n", linked_list_find(&list, 99));
    printf("Get 2 : %d (attendu : 10)\n", linked_list_get(&list, 2));
    printf("Get -1 : %d (attendu : -1)\n", linked_list_get(&list, -1));

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

    printf("Après libération : taille = %d (attendu : 0)\n", list.size);
    printf("Tête vide : %s\n", list.head == NULL ? "oui" : "non");

    return 0;
}
