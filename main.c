#include <SDL.h>
#include <SDL_mouse.h>
#include <stdbool.h>
#include "structs.h"
#include "constants.h"
#include "prototypes.h"


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Мое окно",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                              WIDTH_SIZE*CELL_SIZE, HEIGHT_SIZE*CELL_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Ошибка при создании окна: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Ошибка при создании рендерера: %s\n", SDL_GetError());
        return 1;
    }

    // показать указатель мыши
    SDL_ShowCursor(SDL_ENABLE);

    // создание поля
    struct Board board = init_board(HEIGHT_SIZE, WIDTH_SIZE);

    // стартовая раскладка клеток

    // 2 квадрата
    board.board_array[5][5].alive = true;
    board.board_array[5][6].alive = true;
    board.board_array[6][5].alive = true;
    board.board_array[6][6].alive = true;
    board.board_array[3][3].alive = true;
    board.board_array[4][3].alive = true;
    board.board_array[3][4].alive = true;
    board.board_array[4][4].alive = true;

    // пентадекатлон
    board.board_array[17][10].alive = true;
    board.board_array[17][11].alive = true;
    board.board_array[16][12].alive = true;
    board.board_array[18][12].alive = true;
    board.board_array[17][13].alive = true;
    board.board_array[17][14].alive = true;
    board.board_array[17][15].alive = true;
    board.board_array[17][16].alive = true;
    board.board_array[16][17].alive = true;
    board.board_array[18][17].alive = true;
    board.board_array[17][18].alive = true;
    board.board_array[17][19].alive = true;

    bool quit = false;
    bool execute = false;
    int state = 0;
    // основной цикл обработки событий
    SDL_Event event;
    while (!quit) {
        switch (state) {
            // главное меню
            case 0: {
                show_menu(renderer, IMAGE_PATH);
                menu_events(&event, renderer, &board, &state, &execute, &quit);
            }
            // симуляция
            case 1: {
                if (execute) {
                    recalculate(&board);
                    draw_board(&board, renderer);
                }
                game_events(&event, renderer, &board, &state, &execute, &quit);

            }
            default:
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}