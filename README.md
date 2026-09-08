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

## Lancer le benchmark

Le benchmark teste 1 000, 10 000, 100 000 et 1 000 000 d'éléments avec une horloge monotone.

```sh
cc benchmarks/benchmark.c src/dynamic_array.c src/linked_list.c src/hash_table.c -O2 -o benchmark && ./benchmark
```

Les durées affichées sont des moyennes par opération et peuvent varier entre deux exécutions.

## 1. Complexités théoriques

`n` représente le nombre d'éléments stockés. Pour la table de hachage, les complexités moyennes supposent une bonne répartition des valeurs dans les buckets.

| Opération | Dynamic Array | Linked List | Hash Table | Gagnant prévu |
|---|---:|---:|---:|---|
| `get(index)` | O(1) | O(n) | Non applicable | Dynamic Array |
| `find(value)` / `hash_contains` | O(n) | O(n) | O(1) en moyenne, O(n) au pire | Hash Table en moyenne |
| `insert_front` | O(n) | O(1) | Non applicable | Linked List |
| `insert_back` / `hash_insert` | O(1) si une case est disponible, O(n) avec réallocation | O(n) | O(1) en moyenne, O(n) au pire | Dynamic Array ou Hash Table en moyenne |
| `remove_front` | O(n) | O(1) | Non applicable | Linked List |
| Parcours complet | O(n) | O(n) | O(TABLE_SIZE + n) | Dynamic Array en pratique |
| Libération | O(1) | O(n) | O(TABLE_SIZE + n) | Dynamic Array |

Le tableau dynamique actuel augmente sa capacité d'une case lors d'une réallocation. Une insertion en fin reste O(1) lorsqu'une case est disponible, mais une suite d'agrandissements peut coûter O(n²). Une croissance multiplicative permettrait d'obtenir un coût amorti O(1).

## 2. Prédictions avant benchmark

Avant de consulter les mesures, les hypothèses sont les suivantes :

- le Dynamic Array doit gagner pour `get(index)`, grâce à l'accès direct par indice ;
- `find(value)` est O(n) pour le tableau et la liste, mais le tableau devrait être plus rapide grâce à sa mémoire contiguë ;
- la Linked List doit gagner pour `insert_front` et `remove_front`, car elle modifie seulement quelques pointeurs ;
- le Dynamic Array doit gagner pour `insert_back` lorsqu'une case est déjà disponible ;
- le Dynamic Array devrait gagner pour le parcours complet grâce à une meilleure utilisation du cache ;
- `hash_good` doit permettre une recherche proche de O(1), tandis que `hash_bad` doit dégénérer vers O(n).

## 3. Résultats et comparaison

Les mesures ci-dessous sont les moyennes de cinq exécutions complètes compilées avec `-O2`. Chaque exécution utilise `CLOCK_MONOTONIC` et plusieurs répétitions internes. Les résultats sont exprimés en nanosecondes moyennes par opération.

### Dynamic Array contre Linked List à 1 000 000 d'éléments

| Opération | Dynamic Array | Linked List | Plus rapide |
|---|---:|---:|---|
| `get(n/2)` | 0,71 ns | 239 500 ns | Dynamic Array |
| Recherche absente | 260 666,67 ns | 885 466,66 ns | Dynamic Array |
| `insert_front` | 65 533,33 ns | 16,76 ns | Linked List |
| `insert_back` | 15,39 ns | 556 666,67 ns | Dynamic Array |
| Parcours avec somme | 40 600 ns | 817 333,33 ns | Dynamic Array |

Le benchmark de `insert_back` du tableau est réalisé avec une case déjà disponible : il mesure donc l'insertion elle-même, sans réallocation. La liste ne possède pas de pointeur vers sa fin et doit parcourir tous ses nœuds pour insérer le dernier élément.

Les prédictions sont confirmées : la liste est très efficace pour l'insertion en tête, mais ses parcours deviennent coûteux lorsque `n` augmente. Le tableau bénéficie de l'accès direct et de données contiguës en mémoire. Les valeurs inférieures à une nanoseconde sont des moyennes issues de nombreuses répétitions ; il faut surtout interpréter les tendances et non une mesure isolée.

### `hash_good` contre `hash_bad`

| Nombre d'éléments | `hash_good` | `hash_bad` |
|---:|---:|---:|
| 1 000 | 1,41 ns | 730,90 ns |
| 10 000 | 1,43 ns | 9 391 ns |
| 100 000 | 3,62 ns | 90 530 ns |
| 1 000 000 | 59,32 ns | 1 151 800 ns |

Avec `hash_good`, les valeurs sont réparties entre les buckets et la recherche reste rapide. Avec `hash_bad`, toutes les valeurs sont placées dans le bucket 0. La table devient alors une seule longue liste chaînée et la recherche absente évolue en O(n).

## 4. Recommandation finale

### Situation A : collection rarement modifiée et 1 000 000 de recherches

La Hash Table avec `hash_good` est le meilleur choix. Sa construction demande de calculer les indices et d'allouer les entrées, et sa consommation mémoire est supérieure à celle d'un tableau. Ce coût initial est cependant compensé par le très grand nombre de recherches, qui sont en O(1) en moyenne. Une bonne fonction de hachage est indispensable pour éviter le comportement de `hash_bad`.

### Situation B : mémoire très limitée et seulement 10 recherches

Le Dynamic Array est préférable. Il stocke les entiers dans une zone contiguë avec peu de mémoire supplémentaire, contrairement à la liste qui ajoute un pointeur à chaque nœud et à la table qui réserve `TABLE_SIZE` buckets en plus des entrées. Dix recherches en O(n) restent acceptables et ne justifient pas le surcoût mémoire d'une table de hachage.

Le choix n'est donc pas le même pour les deux situations : la situation A privilégie la vitesse de recherche, tandis que la situation B privilégie la consommation mémoire et la simplicité.
