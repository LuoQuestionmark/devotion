#ifndef TITLE_H
#define TITLE_H

#include <stdint.h>
#include <stdlib.h>

#define PREFIX_MAX_COUNT 32

static const char prefix_table[PREFIX_MAX_COUNT][16] = {
    "多雨的", "湿润的", "多产的", "好幻想的", "稀疏的", "疑惑的", "实验性的", "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",     "NULL",   "NULL",   "NULL",     "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",     "NULL",   "NULL",   "NULL",     "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",     "NULL",   "NULL",   "NULL",     "NULL",
};

struct title {
    uint32_t prefixes;
    char name[32];
};
typedef struct title title;

title *title_init(char *name);
void title_add_prefix(title *title, unsigned short index);
int title_str_cpy(title *title, char *dst, size_t dst_size);
void title_free(title *title);

#endif
