#include "config.h"
#include "gameplay/board.h"
#include "gameplay/title.h"
#include "gui/callback.h"
#include "gui/gui_board.h"
#include "gui/gui_title.h"

static uint32_t pixels[WIDTH * HEIGHT];
static float triangle_angle = 0;

float sqrtf(float x);
float atan2f(float y, float x);
float sinf(float x);
float cosf(float x);

#define OLIVEC_IMPLEMENTATION
#include "olive.c"

#include <SDL2/SDL.h>
#include <stdio.h>

#define return_defer(value)                                                                        \
    do {                                                                                           \
        result = (value);                                                                          \
        goto defer;                                                                                \
    } while (0)

static SDL_Texture *vc_sdl_texture = NULL;
static size_t vc_sdl_actual_width  = 0;
static size_t vc_sdl_actual_height = 0;

static bool vc_sdl_resize_texture(SDL_Renderer *renderer, size_t new_width, size_t new_height) {
    if (vc_sdl_texture != NULL) SDL_DestroyTexture(vc_sdl_texture);
    vc_sdl_actual_width  = new_width;
    vc_sdl_actual_height = new_height;
    vc_sdl_texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                          vc_sdl_actual_width, vc_sdl_actual_height);
    if (vc_sdl_texture == NULL) return false;
    return true;
}

Olivec_Canvas vc_render(board *board, title *title, float dt) {
    Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);

    olivec_fill(oc, BACKGROUND_COLOR);
    board_update(board, dt);
    draw_board(oc, board);
    draw_title(oc, title);

    return oc;
}

int main(void) {
    int result = 0;

    SDL_Window *window     = NULL;
    SDL_Renderer *renderer = NULL;

    board *bd = init_board();
    title *tl = init_title("god");

    title_add_prefix(tl, 1);
    title_add_prefix(tl, 2);
    title_add_prefix(tl, 3);
    title_add_prefix(tl, 4);
    title_add_prefix(tl, 5);
    title_add_prefix(tl, 6);
    title_add_prefix(tl, 7);
    title_add_prefix(tl, 8);

    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) return_defer(1);

        window = SDL_CreateWindow("Devotion by thopterist", 0, 0, 0, 0, 0);
        if (window == NULL) return_defer(1);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) return_defer(1);

        Uint32 prev = SDL_GetTicks();
        bool pause  = false;
        for (;;) {
            // Compute Delta Time
            Uint32 curr = SDL_GetTicks();
            float dt    = (curr - prev) / 1000.f;
            prev        = curr;

            // Flush the events
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT: {
                    return_defer(0);
                } break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_callback(event);
                    break;
                    // case SDL_KEYDOWN: {
                    //     if (event.key.keysym.sym == SDLK_SPACE)
                    //         pause = !pause;
                    // } break;
                }
            }

            SDL_Rect window_rect = { 0, 0, vc_sdl_actual_width, vc_sdl_actual_height };

            if (!pause) {
                // Render the texture
                Olivec_Canvas oc_src = vc_render(bd, tl, dt);
                if (oc_src.width != vc_sdl_actual_width || oc_src.height != vc_sdl_actual_height) {
                    if (!vc_sdl_resize_texture(renderer, oc_src.width, oc_src.height))
                        return_defer(1);
                    SDL_SetWindowSize(window, vc_sdl_actual_width, vc_sdl_actual_height);
                }
                void *pixels_dst;
                int pitch;
                if (SDL_LockTexture(vc_sdl_texture, &window_rect, &pixels_dst, &pitch) < 0)
                    return_defer(1);
                for (size_t y = 0; y < vc_sdl_actual_height; ++y) {
                    // TODO: it would be cool if Olivec_Canvas supported pitch in bytes instead of
                    // pixels It would be more flexible and we could draw on the locked texture
                    // memory directly
                    memcpy((char *)pixels_dst + y * pitch, oc_src.pixels + y * vc_sdl_actual_width,
                           vc_sdl_actual_width * sizeof(uint32_t));
                }
                SDL_UnlockTexture(vc_sdl_texture);
            }

            // Display the texture
            if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) < 0) return_defer(1);
            if (SDL_RenderClear(renderer) < 0) return_defer(1);
            if (SDL_RenderCopy(renderer, vc_sdl_texture, &window_rect, &window_rect) < 0)
                return_defer(1);
            SDL_RenderPresent(renderer);
        }
    }

defer:
    switch (result) {
    case 0:
        printf("OK\n");
        break;
    default:
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    }
    if (vc_sdl_texture) SDL_DestroyTexture(vc_sdl_texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();

    board_free(bd);
    title_free(tl);
    return result;
}
