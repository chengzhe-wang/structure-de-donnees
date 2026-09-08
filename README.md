# TP - Structures de données

Ce projet contient trois structures de données en C :

- un tableau dynamique ;
- une liste chaînée ;
- une table de hachage.

## Lancer les tests

Toutes les commandes suivantes doivent être lancées depuis la racine du projet.

### Tableau dynamique

```sh
cc tests/test_dynamic_array.c src/dynamic_array.c -o test_dynamic_array && ./test_dynamic_array
```

### Liste chaînée

```sh
cc tests/test_linked_list.c src/linked_list.c -o test_linked_list && ./test_linked_list
```

### Table de hachage

```sh
cc tests/test_hash_table.c src/hash_table.c -o test_hash_table && ./test_hash_table
```
