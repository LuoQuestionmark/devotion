#include "gui/gui_god_intervention.h"
#include "config.h"

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
        olivec_text(canvas, next_intervention.description, GOD_INTERVENTION_TEXT_WIDTH_SHIFT,
                    GOD_INTERVENTION_TEXT_HEIGHT_SHIFT + GOD_INTERVENTION_UNITY_HEIGHT * i + 25,
                    olivec_default_font, 3, BLUE);
    }
}
