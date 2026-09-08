#include <stdio.h>
#include <time.h>

#include "../src/hash_table.h"

int main(void)
{
    HashTable table;
    hash_table_init(&table);

    printf("Taille de la table : %d\n", TABLE_SIZE);
    printf(
        "Premier bucket vide après init : %s\n",
        table.buckets[0] == NULL ? "oui" : "non"
    );

    int value1 = 12;
    int value2 = value1 + TABLE_SIZE;
    int value3 = value2 + TABLE_SIZE;

    hash_insert(&table, value1);
    hash_insert(&table, value2);
    hash_insert(&table, value3);
    hash_insert(&table, 42);
    hash_insert(&table, -1);

    printf("\n--- Recherche ---\n");
    printf("Contient %d : %d (attendu : 1)\n", value1, hash_contains(&table, value1));
    printf("Contient %d : %d (attendu : 1)\n", value2, hash_contains(&table, value2));
    printf("Contient %d : %d (attendu : 1)\n", value3, hash_contains(&table, value3));
    printf("Contient 42 : %d (attendu : 1)\n", hash_contains(&table, 42));
    printf("Contient -1 : %d (attendu : 1)\n", hash_contains(&table, -1));
    printf("Contient 99 : %d (attendu : 0)\n", hash_contains(&table, 99));

    int collision_bucket = hash_good(value1);
    int collision_count = 0;
    Entry *current = table.buckets[collision_bucket];

    while (current != NULL) {
        collision_count++;
        current = current->next;
    }

    printf("\n--- Collisions ---\n");
    printf("Bucket utilisé : %d\n", collision_bucket);
    printf("Nombre d'entrées dans ce bucket : %d (attendu : 3)\n", collision_count);

    hash_table_free_collection(&table);

    printf("\n--- Libération ---\n");
    printf(
        "Bucket vide après libération : %s\n",
        table.buckets[collision_bucket] == NULL ? "oui" : "non"
    );

    HashTable good_table;
    HashTable bad_table;
    hash_table_init(&good_table);
    hash_table_init(&bad_table);

    const int value_count = 100000;
    const int repetitions = 1000;

    for (int i = 0; i < value_count; i++) {
        hash_insert_with(&good_table, i, hash_good);
        hash_insert_with(&bad_table, i, hash_bad);
    }

    struct timespec start;
    struct timespec end;
    volatile int found = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < repetitions; i++) {
        found += hash_contains_with(&good_table, -1, hash_good);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    long good_nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000L
        + (end.tv_nsec - start.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < repetitions; i++) {
        found += hash_contains_with(&bad_table, -1, hash_bad);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    long bad_nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000L
        + (end.tv_nsec - start.tv_nsec);

    printf("\n--- hash_good contre hash_bad ---\n");
    printf("Recherche absente avec hash_good : %ld ns\n", good_nanoseconds);
    printf("Recherche absente avec hash_bad : %ld ns\n", bad_nanoseconds);

    hash_table_free_collection(&good_table);
    hash_table_free_collection(&bad_table);

    (void)found;

    return 0;
}
