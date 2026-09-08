#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/dynamic_array.h"
#include "../src/hash_table.h"
#include "../src/linked_list.h"

volatile long long result_benchmark = 0;

long long get_time(struct timespec start, struct timespec end){
    return (end.tv_sec - start.tv_sec) * 1000000000LL
        + (end.tv_nsec - start.tv_nsec);
}

int get_repetitions(int size){
    int repetitions = 2000000 / size;

    if(repetitions < 3){
        repetitions = 3;
    }

    if(repetitions > 2000){
        repetitions = 2000;
    }

    return repetitions;
}

void remove_linked_back(LinkedList *list){
    if(list->head->next == NULL){
        free(list->head);
        list->head = NULL;
        list->size = 0;
        return;
    }

    Node *current = list->head;

    while(current->next->next != NULL){
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    list->size--;
}

void benchmark_array_and_list(int size){
    DynamicArray array;
    LinkedList list;

    if(!dynamic_array_init(&array, size + 1)){
        printf("Erreur pendant la création du tableau dynamique\n");
        exit(1);
    }

    linked_list_init(&list);

    for(int i = 0; i < size; i++){
        insert_back(&array, i);
    }

    for(int i = size - 1; i >= 0; i--){
        linked_list_insert_front(&list, i);
    }

    int repetitions = get_repetitions(size);
    int repetitions_get_list = get_repetitions(size / 2);
    int repetitions_fast = 100000;

    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions_fast; i++){
        result_benchmark += get(&array, size / 2);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double array_get = (double)get_time(start, end) / repetitions_fast;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions_get_list; i++){
        result_benchmark += linked_list_get(&list, size / 2);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double list_get = (double)get_time(start, end) / repetitions_get_list;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions; i++){
        result_benchmark += find(&array, -1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double array_find = (double)get_time(start, end) / repetitions;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions; i++){
        result_benchmark += linked_list_find(&list, -1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double list_find = (double)get_time(start, end) / repetitions;

    long long total_array_front = 0;
    for(int i = 0; i < repetitions; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        insert_front(&array, -1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        total_array_front += get_time(start, end);
        remove_front(&array);
    }
    double array_insert_front = (double)total_array_front / repetitions;

    long long total_list_front = 0;
    for(int i = 0; i < repetitions_fast; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        linked_list_insert_front(&list, -1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        total_list_front += get_time(start, end);
        linked_list_remove_front(&list);
    }
    double list_insert_front = (double)total_list_front / repetitions_fast;

    long long total_array_back = 0;
    for(int i = 0; i < repetitions_fast; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        insert_back(&array, -1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        total_array_back += get_time(start, end);
        array.size--;
    }
    double array_insert_back = (double)total_array_back / repetitions_fast;

    long long total_list_back = 0;
    for(int i = 0; i < repetitions; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        linked_list_insert_back(&list, -1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        total_list_back += get_time(start, end);
        remove_linked_back(&list);
    }
    double list_insert_back = (double)total_list_back / repetitions;

    long long sum_array = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int repeat = 0; repeat < repetitions; repeat++){
        for(int i = 0; i < array.size; i++){
            sum_array += array.data[i];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    result_benchmark += sum_array;
    double array_sum = (double)get_time(start, end) / repetitions;

    long long sum_list = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int repeat = 0; repeat < repetitions; repeat++){
        Node *current = list.head;

        while(current != NULL){
            sum_list += current->value;
            current = current->next;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    result_benchmark += sum_list;
    double list_sum = (double)get_time(start, end) / repetitions;

    printf("\nTaille : %d éléments\n", size);
    printf("%-22s %16s %16s\n", "Opération", "Dynamic Array", "Linked List");
    printf("%-22s %13.2f ns %13.2f ns\n", "get(n/2)", array_get, list_get);
    printf("%-22s %13.2f ns %13.2f ns\n", "find(absente)", array_find, list_find);
    printf("%-22s %13.2f ns %13.2f ns\n", "insert_front", array_insert_front, list_insert_front);
    printf("%-22s %13.2f ns %13.2f ns\n", "insert_back", array_insert_back, list_insert_back);
    printf("%-22s %13.2f ns %13.2f ns\n", "parcours + somme", array_sum, list_sum);

    free_collection(&array);
    linked_list_free_collection(&list);
}

void benchmark_hash(int size){
    HashTable good_table;
    HashTable bad_table;

    hash_table_init(&good_table);
    hash_table_init(&bad_table);

    for(int i = 0; i < size; i++){
        hash_insert_with(&good_table, i, hash_good);
        hash_insert_with(&bad_table, i, hash_bad);
    }

    int repetitions_bad = get_repetitions(size);
    int repetitions_good = 100000;
    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions_good; i++){
        result_benchmark += hash_contains_with(&good_table, -1, hash_good);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double good_time = (double)get_time(start, end) / repetitions_good;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < repetitions_bad; i++){
        result_benchmark += hash_contains_with(&bad_table, -1, hash_bad);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double bad_time = (double)get_time(start, end) / repetitions_bad;

    printf("%-22s %16s %16s\n", "Hachage", "hash_good", "hash_bad");
    printf("%-22s %13.2f ns %13.2f ns\n", "recherche absente", good_time, bad_time);

    hash_table_free_collection(&good_table);
    hash_table_free_collection(&bad_table);
}

int main(void){
    int sizes[] = {1000, 10000, 100000, 1000000};
    int number_of_sizes = 4;

    printf("Toutes les durées sont des moyennes par opération.\n");

    for(int i = 0; i < number_of_sizes; i++){
        benchmark_array_and_list(sizes[i]);
        benchmark_hash(sizes[i]);
    }

    return 0;
}
