#include <stdio.h>
#include "src/dynamic_array.h"

int main(void){
    DynamicArray array;

    if (!dynamic_array_init(&array, 2)) {
        printf("Échec de l'initialisation\n");
        return 1;
    }
    printf("Succès de l'initialisation\n");
    printf("Taille : %d\n", array.size);
    printf("Capacité : %d\n", array.capacity);

    insert_back(&array, 2);
    insert_back(&array, 5);
    insert_back(&array, 7);

    printf("Succès de l'insert back\n");
    printf("Taille : %d\n", array.size);
    printf("Capacité : %d\n", array.capacity);
    for(int i = 0; i < array.size; i++){
        printf(" %d ", array.data[i]);
    }

    insert_front(&array, 9);

    printf("\nSuccès de l'insert front\n");
    printf("Taille : %d\n", array.size);
    printf("Capacité : %d\n", array.capacity);
    for(int i = 0; i < array.size; i++){
        printf(" %d ", array.data[i]);
    }

    printf("\nValeur find trouvée à la position : %d\n",find(&array, 2));

    printf("La valeur get trouvée est : %d\n",get(&array, 1));
    
    remove_front(&array);

    printf("\nSuccès du remove front\n");
    printf("Taille : %d\n", array.size);
    printf("Capacité : %d\n", array.capacity);
    for(int i = 0; i < array.size; i++){
        printf(" %d ", array.data[i]);
    }

    free_collection(&array);

    return 0;
}
