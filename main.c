#include <stdio.h>

#include "./src/localization/localization_main.c"
#include "./src/view/view_main.c"
#include "./src/database/database_main.c"

int main(int argc, char *argv[]) {
    LocalizationArray *localization_group = init_localization("en_US");
    init_open_gl(localization_group);
    free_localization(localization_group);
    return 0;
}