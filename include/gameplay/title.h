#ifndef TITLE_H
#define TITLE_H

#include <stdint.h>
#include <stdlib.h>

#define PREFIX_MAX_COUNT 32

static const char prefix_table[PREFIX_MAX_COUNT][16] = {
    "rainy ",  "all-mighty ", "silent ",      "humble ",      "eerie ", "prosperous ", "devine ",
    "strong ", "god-like ",   "domiciliary ", "flourishing ", "NULL",   "NULL",        "NULL",
    "NULL",    "NULL",        "NULL",         "NULL",         "NULL",   "NULL",        "NULL",
    "NULL",    "NULL",        "NULL",         "NULL",         "NULL",   "NULL",        "NULL",
    "NULL",    "NULL",        "NULL",         "NULL",
};

struct title {
    uint32_t prefixes;
    char name[32];
};
typedef struct title title;

title *init_title(char *name);
void title_add_prefix(title *title, unsigned short index);
int title_str_cpy(title *title, char *dst, size_t dst_size);
void title_free(title *title);

#endif
