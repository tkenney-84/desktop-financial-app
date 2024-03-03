#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Structure to hold key-value KeyPairs
typedef struct {
    char *key;
    char *value;
} KeyPair;

typedef struct {
    KeyPair *key_pairs;
    int *num_key_pairs;
} KeyPairArray;

// Loads a language file, returns array of KeyPairs (NULL on failure)
KeyPairArray* parse_util_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        printf(file_path);
        printf("\n");
        printf("Error opening file: %s\n", strerror(errno));
        return NULL;
    }

    KeyPairArray *key_pair_array = malloc(sizeof(KeyPairArray));
    (*key_pair_array).key_pairs = malloc(sizeof(KeyPair));
    (*key_pair_array).num_key_pairs = malloc(sizeof(int));

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *key, *value;
        key = strtok(line, "=");
        value = strtok(NULL, "=\n");

        // Reallocate KeyPairs array to add space for new KeyPair
        (*key_pair_array).key_pairs = realloc((*key_pair_array).key_pairs, ((*(*key_pair_array).num_key_pairs) + 1) * sizeof(KeyPair));
        (*key_pair_array).key_pairs[(*(*key_pair_array).num_key_pairs)].key = strdup(key);
        (*key_pair_array).key_pairs[(*(*key_pair_array).num_key_pairs)].value = strdup(value);
        (*(*key_pair_array).num_key_pairs)++;
    }

    fclose(file);

    return key_pair_array;
}

// Finds a value given a key
const char* get_value(KeyPairArray *key_pair_array, const char *key) {

    if (key_pair_array == NULL) {
        printf("KeyPairArray is NULL\n");
        return NULL;
    }

    if (key == NULL) {
        printf("Key is NULL\n");
        return NULL;
    }

    for (int i = 0; i < (*(*key_pair_array).num_key_pairs); i++) {
        if (strcmp((*key_pair_array).key_pairs[i].key, key) == 0) {
            return (*key_pair_array).key_pairs[i].value;
        }
    }

    return NULL;
}