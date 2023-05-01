#include <SDL.h>
#include <SDL_mouse.h>
#include <stdbool.h>
#include "structs.h"
#include "prototypes.h"

#define SIZE 25
#define CELL_SIZE 30


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Мое окно",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                              SIZE*CELL_SIZE, SIZE*CELL_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Ошибка при создании окна: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Ошибка при создании рендерера: %s\n", SDL_GetError());
        return 1;
    }

    // создание поля
    struct Board board = init_board(SIZE, SIZE);

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

    // палочка
//    board.board_array[12][10].alive = true;
//    board.board_array[12][11].alive = true;
//    board.board_array[12][9].alive = true;

    // пентадекатлон
    board.board_array[17][10].alive = true;
    board.board_array[17][11].alive = true;

    board.board_array[16][12].alive = true;
    //board.board_array[17][12].alive = true;
    board.board_array[18][12].alive = true;

    board.board_array[17][13].alive = true;
    board.board_array[17][14].alive = true;
    board.board_array[17][15].alive = true;
    board.board_array[17][16].alive = true;

    board.board_array[16][17].alive = true;
    //board.board_array[17][17].alive = true;
    board.board_array[18][17].alive = true;

    board.board_array[17][18].alive = true;
    board.board_array[17][19].alive = true;

    // хлам
//    board.board_array[0][0].alive = true;
//    board.board_array[14][14].alive = true;
//    board.board_array[0][9].alive = true;
//    board.board_array[14][11].alive = true;
//    board.board_array[2][1].alive = true;
//    board.board_array[8][3].alive = true;
//    board.board_array[8][0].alive = true;
//    board.board_array[8][14].alive = true;
//    board.board_array[11][12].alive = true;

    // основной цикл обработки событий
    SDL_Event event;

    // показать указатель мыши
    SDL_ShowCursor(SDL_ENABLE);

    draw_board(&board, renderer);
    bool quit = false;
    bool execute = false;
    while (!quit) {
        if (execute) {
            recalculate(&board, SIZE);
            draw_board(&board, renderer);

            // цикличные события
//            if (SDL_PollEvent(&event)){
//                switch (event.type) {
//                    case SDL_QUIT:
//                        quit = true;
//                        break;
//                    case SDL_KEYDOWN:
//                        if (event.key.keysym.sym == SDLK_RETURN) {
//                            execute = false;
//                        }
//                        break;
//
//                    default:
//                        break;
//                }
//            }
//            continue;
        }
        // пауза и выход
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        execute = !execute;
                    } else if (event.key.keysym.sym == SDLK_SPACE){
                        recalculate(&board, SIZE);
                        draw_board(&board, renderer);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        // Обработка щелчка левой кнопкой мыши

                        change_cell(&board, mouseX, mouseY);
                        execute = false;
                        draw_board(&board, renderer);
                        //printf("%d\n", board.board_array[mouseX][mouseY].alive);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

struct Board init_board(int height, int width){
    struct Board board;
    board.height = height;
    board.width = width;
    board.board_array = malloc(board.height *  sizeof(struct Cell*));
    for (int i = 0; i < board.height; i++) {
        board.board_array[i] = malloc(board.width * sizeof(struct Cell));
        // Инициализируем каждый элемент структурой Cell
        for (int j = 0; j < board.width; j++) {
            struct Cell new_cell = {
                    .alive = false, .pos_x = j, .pos_y = i}; // Создаем новый экземпляр структуры Cell
            board.board_array[i][j] = new_cell; // Присваиваем значение элементу массива
        }
    }

    return board;
}

void draw_board(struct Board* board, SDL_Renderer* renderer){
    // отрисовка поля квадратов
    SDL_Rect rects[SIZE*SIZE];
    // заполняем экран белым цветом
    SDL_SetRenderDrawColor(renderer, 0, 153, 51, 255);
    SDL_RenderClear(renderer);
    draw_cells(rects, renderer, SIZE, board);
    // показать рендер
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
}

void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, int size, struct Board* board){
    // отрисовываем квадратов
    for (int i = 0; i<size; i++) {
        for (int j=0; j<size; j++) {
            // инициализируем клетки
            rects[i*size + j].y = (i) * CELL_SIZE;
            rects[i*size + j].x = (j) * CELL_SIZE;
            rects[i*size + j].w = CELL_SIZE;
            rects[i*size + j].h = CELL_SIZE;
            // закрашиваем клетки
            if (board->board_array[i][j].alive) {
                SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
                SDL_RenderFillRect(renderer, &rects[i*size + j]);
            }
            // рисуем границу клеток
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rects[i * size + j]);

        }
    }
}

int neighbors_count(struct Board* board, struct Cell* cell, int size) {
    int neighbors = 0;
    for (int i = cell->pos_y - 1; i <= cell->pos_y + 1; i++) {
        if (i == -1){
            i++;
        }else if (i == size){continue;}
        for (int j = cell->pos_x - 1; j <= cell->pos_x + 1; j++) {
            if (j == -1){
                j++;
            }else if (j == size){continue;}
            if (j == cell->pos_x && i == cell->pos_y) { continue; }
            if (board->board_array[i][j].alive) {
                neighbors++;
            }
        }
    }

    return neighbors;
}

void recalculate(struct Board* board, int size) {
    // пропускаем цикл если клетка не была активна
    struct Cell** temp_board;
    temp_board = malloc(size *  sizeof(struct Cell*));
    for (int i = 0; i < size; i++) {
        temp_board[i] = malloc(size * sizeof(struct Cell));
        // Инициализируем каждый элемент структурой Cell
        for (int j = 0; j < size; j++) {
            // Создаем новый экземпляр структуры Cell
            int neighbors = neighbors_count(board, &board->board_array[i][j], SIZE);
            // Присваиваем значение элементу массива
            temp_board[i][j] = check_rules(&board->board_array[i][j], neighbors);
            temp_board[i][j].pos_x = j;
            temp_board[i][j].pos_y = i;
        }
    }
    free(board->board_array);
    board->board_array = temp_board;
}

struct Cell check_rules(struct Cell* cell, int count){
    struct Cell result;
    // правило 4
    if (!cell->alive && count == 3){
            result.alive = true;
        return result;
    } else if (!cell->alive){
        result.alive = false;
        return result;
    }
    if (count < 2) {
        result.alive = false;
        // правило 2
    } else if (count > 3){
        result.alive = false;
        // правило 3
    }else {
        result.alive = true;
    }

    return result;
}

void change_cell(struct Board* board, int y, int x){
    int pos_x = x / CELL_SIZE;
    int pos_y = y / CELL_SIZE;
    struct Cell* new_cell = malloc(sizeof(struct Cell));
    new_cell->alive = !board->board_array[pos_x][pos_y].alive;
    new_cell->pos_x = pos_y;
    new_cell->pos_y = pos_x;
    board->board_array[pos_x][pos_y] = *new_cell;

}