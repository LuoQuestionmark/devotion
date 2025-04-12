#include "gameplay/title.h"
#include <stdio.h>

int main() {
    title *t = init_title("god");
    title_add_prefix(t, 1);
    title_add_prefix(t, 2);
    title_add_prefix(t, 6);

    char temp[128];
    title_str_cpy(t, temp, sizeof(temp));
    puts(temp);

    title_free(t);
}
