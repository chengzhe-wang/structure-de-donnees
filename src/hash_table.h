#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 10007

typedef struct Entry {
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
} HashTable;

void hash_table_init(HashTable *table);
void hash_insert(HashTable *table, int value);
int hash_contains(HashTable *table, int value);
void hash_table_free_collection(HashTable *table);

int hash_good(int value);
int hash_bad(int value);

#endif
