#include "hash_table.h"
#include <stdlib.h>

void hash_table_init(HashTable *table){
    for(int i = 0; i < TABLE_SIZE; i++){
        table->buckets[i] = NULL;
    }
}

int hash_good(int id) {
    return id % TABLE_SIZE;
}

int hash_bad(int id) {
    return 0;
}

void hash_insert(HashTable *table, int value){
    int hash = hash_good(value);

    Entry *new_entry = malloc(sizeof(Entry));

    new_entry->value = value;
    new_entry->next = table->buckets[hash];
    table->buckets[hash] = new_entry;
}

int hash_contains(HashTable *table, int value){
    int hash = hash_good(value);

    if(table->buckets[hash] != NULL){
        Entry *new_entry = table->buckets[hash];
        while(new_entry != NULL){
            if(new_entry->value == value){
                return 1;
            }
            new_entry = new_entry->next;
        }
    }
    return 0;
}

void hash_table_free_collection(HashTable *table){
    for(int i = 0; i < TABLE_SIZE; i++){
        Entry *current = table->buckets[i];

        while(current != NULL){
            Entry *next = current->next;
            free(current);
            current = next;
        }
        table->buckets[i] = NULL;
    }
}