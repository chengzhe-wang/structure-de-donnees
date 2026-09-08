#include "hash_table.h"
#include <stdlib.h>

void hash_table_init(HashTable *table){
    for(int i = 0; i < TABLE_SIZE; i++){
        table->buckets[i] = NULL;
    }
}

int hash_good(int id) {
    int hash = id % TABLE_SIZE;
    return hash < 0 ? hash + TABLE_SIZE : hash;
}

int hash_bad(int id) {
    (void)id;
    return 0;
}

void hash_insert_with(HashTable *table, int value, HashFunction hash_function){
    if(table == NULL || hash_function == NULL){
        return;
    }

    int hash = hash_function(value);

    if(hash < 0 || hash >= TABLE_SIZE){
        return;
    }

    Entry *new_entry = malloc(sizeof(Entry));

    if(new_entry == NULL){
        return;
    }

    new_entry->value = value;
    new_entry->next = table->buckets[hash];
    table->buckets[hash] = new_entry;
}

void hash_insert(HashTable *table, int value){
    hash_insert_with(table, value, hash_good);
}

int hash_contains_with(HashTable *table, int value, HashFunction hash_function){
    if(table == NULL || hash_function == NULL){
        return 0;
    }

    int hash = hash_function(value);

    if(hash < 0 || hash >= TABLE_SIZE){
        return 0;
    }

    Entry *current = table->buckets[hash];

    while(current != NULL){
        if(current->value == value){
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int hash_contains(HashTable *table, int value){
    return hash_contains_with(table, value, hash_good);
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
