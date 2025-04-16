#include "gui/gui_god_intervention.h"
#include "config.h"
#include <string.h>

void draw_interventions(Olivec_Canvas canvas, intervention_list *list) {
    uint32_t bg_color = WHITE;
    for (int i = 0; i < INTERVENTION_MAX_COUNT; i++) {
        int ivt = (1 << i);
        if ((list->available & ivt) == 0) continue;

        bg_color = (bg_color == WHITE ? PALE_LEMON_YELLOW : WHITE);

        intervention next_intervention = intervention_table[i];
        olivec_rect(canvas, GOD_INTERVENTION_WIDTH_SHIFT,
                    GOD_INTERVENTION_HEIGHT_SHIFT + GOD_INTERVENTION_UNITY_HEIGHT * i,
                    GOD_INTERVENTION_WIDTH, GOD_INTERVENTION_UNITY_HEIGHT, bg_color);
        // name
        olivec_text(canvas, next_intervention.name, GOD_INTERVENTION_TEXT_WIDTH_SHIFT,
                    GOD_INTERVENTION_TEXT_HEIGHT_SHIFT + GOD_INTERVENTION_UNITY_HEIGHT * i,
                    olivec_default_font, 3, GREEN);
        // description
        char description1[GOD_INTERVENTION_MAX_LINE_CHARACTERS + 1] = "";
        char description2[GOD_INTERVENTION_MAX_LINE_CHARACTERS + 1] = "";
        strncpy(description1, next_intervention.description, GOD_INTERVENTION_MAX_LINE_CHARACTERS);
        olivec_text(canvas, description1, GOD_INTERVENTION_TEXT_WIDTH_SHIFT,
                    GOD_INTERVENTION_TEXT_HEIGHT_SHIFT + GOD_INTERVENTION_UNITY_HEIGHT * i + 25,
                    olivec_default_font, 3, BLUE);

        if (strlen(next_intervention.description) <= GOD_INTERVENTION_MAX_LINE_CHARACTERS) continue;
        strncpy(description2, next_intervention.description + GOD_INTERVENTION_MAX_LINE_CHARACTERS,
                GOD_INTERVENTION_MAX_LINE_CHARACTERS);
        olivec_text(canvas, description2, GOD_INTERVENTION_TEXT_WIDTH_SHIFT,
                    GOD_INTERVENTION_TEXT_HEIGHT_SHIFT + GOD_INTERVENTION_UNITY_HEIGHT * i + 50,
                    olivec_default_font, 3, BLUE);
    }
}
