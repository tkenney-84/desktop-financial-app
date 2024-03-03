#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <./src/persistence_engine.c>

LocalizationArray* get_available_localizations() {
    return load_language_file("./assets/localization/available.lang");
}

LocalizationArray* init_localization(char * localization_file_name) {
    char* base_file_path = "./assets/localization/";
    char* file_extension = ".lang";
    char* file_path = malloc(strlen(base_file_path) + strlen(localization_file_name) + strlen(file_extension) + 1);
    strcpy(file_path, base_file_path);
    strcat(file_path, localization_file_name);
    strcat(file_path, file_extension);
    return load_language_file(file_path);
}

// Finds a Localization given the key
const char* get_loc_str(LocalizationArray *localization_group, const char *key) {
    if (localization_group == NULL) {
        printf("Localization group is NULL\n");
        return NULL;
    }

    if (key == NULL) {
        printf("Key is NULL\n");
        return NULL;
    }

    for (int i = 0; i < (*(*localization_group).num_localizations); i++) {
        if (strcmp((*localization_group).localizations[i].key, key) == 0) {
            return (*localization_group).localizations[i].value;
        }
    }

    return NULL;
}

// Frees memory used by Localizations
void free_localization(LocalizationArray *localization_group) {

    for (int i = 0; i < (*(*localization_group).num_localizations); i++) {
        free((*localization_group).localizations[i].key);
        free((*localization_group).localizations[i].value);
    }

    free(localization_group->localizations);
    free(localization_group->num_localizations);
    free(localization_group);
}