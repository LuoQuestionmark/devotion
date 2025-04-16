#include "gui/gui_title.h"
#include "config.h"
#include "gameplay/title.h"
#include <string.h>

void draw_title(Olivec_Canvas canvas, title *title) {
    olivec_rect(canvas, TITLE_WIDTH_SHIFT, TITLE_HEIGHT_SHIFT, TITLE_WIDTH, TITLE_HEIGHT, WHITE);
    char whole_name[TITLE_CHARACTERS_BY_LINE * TITLE_CHARACTERS_MAX_LINE_COUNT] = { 0 };
    title_str_cpy(title, whole_name, sizeof(whole_name));

    char temp[TITLE_CHARACTERS_BY_LINE + 1] = {};
    // char temp[100];
    for (size_t i = 0; i < TITLE_CHARACTERS_MAX_LINE_COUNT; i += 1) {
        strncpy(temp, whole_name + (TITLE_CHARACTERS_BY_LINE)*i, TITLE_CHARACTERS_BY_LINE);
        olivec_text(canvas, temp, TITLE_TEXT_WIDTH_SHIFT, TITLE_TEXT_HEIGHT_SHIFT + 25 * i,
                    olivec_default_font, 3, BLUE);
    }
}
