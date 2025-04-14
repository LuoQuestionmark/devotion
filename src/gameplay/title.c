#include "gameplay/title.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

title *init_title(char *name) {
    title *ret = calloc(1, sizeof(title));

    ret->prefixes = 0;
    strncpy(ret->name, name, sizeof(ret->name));

    return ret;
}

void title_add_prefix(title *title, unsigned short index) {
    assert(index < PREFIX_MAX_COUNT);

    uint32_t new_title = (1 << index);
    title->prefixes |= new_title;
}

int title_str_cpy(title *title, char *dst, size_t dst_size) {
    int ret = 0;
    char temp[dst_size];
    strcpy(temp, "");

    size_t available = dst_size - strlen(title->name) - 1;

    for (int i = 0; i < PREFIX_MAX_COUNT; i++) {
        uint32_t prefix = (1 << i);
        if ((title->prefixes & prefix) == 0) continue;

        if (available < strlen(prefix_table[i])) {
            ret = -1;
            break;
        }

        strcat(temp, prefix_table[i]);
    }

    strcat(temp, title->name);
    strncpy(dst, temp, dst_size);

    return ret;
}

void title_free(title *title) {
    free(title);
}
