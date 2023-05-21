//
// Created by Алексей Янкович on 14.05.23.
//
#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include "structs.h"
#include "constants.h"
#include "prototypes.h"

// Объявление глобальной переменной
int count_generation = 0;
int color_theme = 0;
struct ColorPalette clr;

struct Board init_board(){
    // инициализация поля
    struct Board board;
    set_color(&clr);
    board.height = HEIGHT_SIZE;
    board.width = WIDTH_SIZE;
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

void draw_board(struct Board* board, SDL_Renderer* renderer, TTF_Font* font){
    // отрисовка поля квадратов
    SDL_Rect rects[WIDTH_SIZE*HEIGHT_SIZE];
    // заполняем экран цветом
    SDL_SetRenderDrawColor(renderer, clr.DeadColor.r, clr.DeadColor.g, clr.DeadColor.b, 255); // белый
    SDL_RenderClear(renderer);
    draw_cells(rects, renderer, board);
    show_generation(font, renderer);
    // показать рендер
    SDL_RenderPresent(renderer);
    SDL_Delay(110);
}

void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, struct Board* board){
    // отрисовываем квадраты
    for (int i = 0; i<HEIGHT_SIZE; i++) {
        for (int j=0; j<WIDTH_SIZE; j++) {
            // инициализируем клетки
            rects[i*WIDTH_SIZE + j].y = (i) * CELL_SIZE;
            rects[i*WIDTH_SIZE + j].x = (j) * CELL_SIZE;
            rects[i*WIDTH_SIZE + j].w = CELL_SIZE;
            rects[i*WIDTH_SIZE + j].h = CELL_SIZE;
            // закрашиваем клетки
            if (board->board_array[i][j].alive) {
                SDL_SetRenderDrawColor(renderer, clr.AliveColor.r, clr.AliveColor.g, clr.AliveColor.b, 255); // зеленый
                SDL_RenderFillRect(renderer, &rects[i*WIDTH_SIZE + j]);
            }
            // рисуем границу клеток
            SDL_SetRenderDrawColor(renderer, clr.BorderColor.r, clr.BorderColor.g, clr.BorderColor.b, 255);
            SDL_RenderDrawRect(renderer, &rects[i * WIDTH_SIZE + j]);

        }
    }
}

int neighbors_count(struct Board* board, struct Cell* cell) {
    // подсчет живых соседей
    int neighbors = 0;
    int y_pos, x_pos;
    for (int i = cell->pos_y - 1; i <= cell->pos_y + 1; i++) {
        y_pos = i;
        if (i == -1){
            y_pos = HEIGHT_SIZE-1;
        }else if (i == HEIGHT_SIZE){
            y_pos = 0;
        }
        for (int j = cell->pos_x - 1; j <= cell->pos_x + 1; j++) {
            x_pos = j;
            if (j == -1){
                x_pos = WIDTH_SIZE-1;
            }else if (j == WIDTH_SIZE){
                x_pos = 0;
            }
            if (j == cell->pos_x && i == cell->pos_y) { continue; }
            if (board->board_array[y_pos][x_pos].alive) {
                neighbors++;
            }
        }
    }
    return neighbors;
}

void recalculate(struct Board* board) {
    // пропускаем цикл если клетка не была активна
    struct Cell** temp_board;
    temp_board = malloc(HEIGHT_SIZE *  sizeof(struct Cell*));
    for (int i = 0; i < HEIGHT_SIZE; i++) {
        temp_board[i] = malloc(WIDTH_SIZE * sizeof(struct Cell));
        // Инициализируем каждый элемент структурой Cell
        for (int j = 0; j < WIDTH_SIZE; j++) {
            // Создаем новый экземпляр структуры Cell
            int neighbors = neighbors_count(board, &board->board_array[i][j]);
            // Присваиваем значение элементу массива
            temp_board[i][j] = check_rules(&board->board_array[i][j], neighbors);
            temp_board[i][j].pos_x = j;
            temp_board[i][j].pos_y = i;
        }
    }
    free(board->board_array);
    board->board_array = temp_board;
    count_generation++;
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

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path) {
    SDL_Surface* surface = IMG_Load(file_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer) {
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void show_image(SDL_Renderer *renderer, char *file_path){
    char* image_path = NULL;
    if (color_theme == 1) {
        char white[6] = "1.png";
        image_path = (char*)malloc(strlen(file_path) + strlen(white) + 1);
        strcpy(image_path, file_path);
        strcat(image_path, white);
    } else {
        char green[5] = ".png";
        image_path = (char*)malloc(strlen(file_path) + strlen(green) + 1);
        strcpy(image_path, file_path);
        strcat(image_path, green);
    }
    // загрузка и отображение изображения
    SDL_RenderClear(renderer);
    SDL_Texture* splash_texture = load_texture(renderer, image_path);
    render_texture(splash_texture, renderer);
    SDL_RenderPresent(renderer);
    free(image_path);
}

void menu_events(SDL_Event* event, SDL_Renderer* renderer, struct Board* board, TTF_Font* font, int* state, bool* execute, bool* quit){
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = true;
                break;
            case SDL_KEYDOWN: {
                if (event->key.keysym.sym == SDLK_RETURN) {
                    draw_pentadec(board->board_array);
                    draw_board(board, renderer, font);
                    *state = 2;
                } else if (event->key.keysym.sym == SDLK_ESCAPE){
                    *state = 0;
                    count_generation = 0;
                    *board = init_board();
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (event->button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event->button.x;
                    int mouseY = event->button.y;
                    switch (*state) {
                        case 0: {
                            if (mouseY > 270 && mouseY < 330 && mouseX > 110 && mouseX < 410) {
                                show_image(renderer, MAIN_MENU_ACTIVE_PATH);
                                SDL_Delay(150);
                                //draw_board(board, renderer, font);
                                *state = 1;
                            } else if (mouseY > 155 && mouseY < 195 && mouseX > 640 && mouseX < 730) {
                                if (color_theme == 0) {
                                    color_theme = 1;
                                } else if (color_theme == 1){
                                    color_theme = 0;
                                }
                                set_color(&clr);
                                show_image(renderer, MAIN_MENU_PATH);
                            }
                            break;
                        }
                        case 1: {
                            if (mouseY > 270 && mouseY < 330 && mouseX > 110 && mouseX < 310) {
                                show_image(renderer, EMPTY_MODE_ACTIVE_PATH);
                                SDL_Delay(150);
                                //draw_board(board, renderer, font);
                                *state = 2;
                            } else if (mouseY > 350 && mouseY < 420 && mouseX > 110 && mouseX < 340) {
                                show_image(renderer, RANDOM_MODE_ACTIVE_PATH);
                                SDL_Delay(150);
                                draw_random(board->board_array);
                                draw_board(board, renderer, font);
                                *state = 2;
                            }
                            else if (mouseY > 440 && mouseY < 520 && mouseX > 110 && mouseX < 360) {
                                show_image(renderer, PATTERN_MODE_ACTIVE_PATH);
                                SDL_Delay(150);
                                draw_pentadec(board->board_array);
                                draw_board(board, renderer, font);
                                *state = 2;
                            } else if (mouseY > 155 && mouseY < 195 && mouseX > 640 && mouseX < 730) {
                                if (color_theme == 0) {
                                    color_theme = 1;
                                    set_color(&clr);
                                } else if (color_theme == 1){
                                    color_theme = 0;
                                    set_color(&clr);
                                }
                                show_image(renderer, MODE_MENU_PATH);
                            }
                            break;
                        }
                        default: break;
                    }
                    break;
                }
            }
            default: break;
        }
        break;
    }
}

void game_events(SDL_Event* event, SDL_Renderer* renderer, struct Board* board, TTF_Font* font, int* state, bool* execute, bool* quit){
    // обработчик событий
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = true;
                break;
            case SDL_KEYDOWN:
                if (event->key.keysym.sym == SDLK_RETURN) {
                    *execute = !*execute;
                    *state = 2;
                } else if (event->key.keysym.sym == SDLK_SPACE){
                    recalculate(board);
                    draw_board(board, renderer, font);
                } else if (event->key.keysym.sym == SDLK_ESCAPE){
                    *state = 0;
                    *execute = false;
                    count_generation = 0;
                    *board = init_board();
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event->button.x;
                    int mouseY = event->button.y;
                    // Обработка щелчка левой кнопкой мыши
                    change_cell(board, mouseX, mouseY);
                    *execute = false;
                    draw_board(board, renderer, font);
                    break;
                }
            default:
                break;
        }
    }
}

void show_generation(TTF_Font* font, SDL_Renderer* renderer){
    // Pixels from our text
    SDL_Color color = {clr.FontColor.r, clr.FontColor.g, clr.FontColor.b};
    char* gen;
    gen = malloc(25 * sizeof(char));
    sprintf(gen, "Generation: %d", count_generation);
    SDL_Surface* surfaceText = TTF_RenderText_Solid(font, gen, color);
    free(gen);
    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);
    // Free the surface
    // We are done with it after we have uploaded to
    // the texture
    SDL_FreeSurface(surfaceText);

    // Create a rectangle to draw on
    SDL_Rect rectangle;
    rectangle.x = 40;
    rectangle.y = 500;
    rectangle.w = 150;
    rectangle.h = 50;

    //SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);

    // Render our text on a rectangle
    SDL_RenderCopy(renderer,textureText,NULL,&rectangle);
}

void draw_random(struct Cell** board_array){
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    for (int i=0; i<HEIGHT_SIZE; i++){
        for (int j=0; j<WIDTH_SIZE; j++){
            int random_number = rand() % 2; // Генерация случайного числа от 0 до 2
            if (random_number == 0) {
                board_array[i][j].alive = false;
            } else {
                board_array[i][j].alive = true;
            }
        }
    }
}


void draw_pentadec(struct Cell** board_array){
    // стартовая раскладка клеток
//    // 2 квадрата
//    board_array[5][5].alive = true;
//    board_array[5][6].alive = true;
//    board_array[6][5].alive = true;
//    board_array[6][6].alive = true;
//    board_array[3][3].alive = true;
//    board_array[4][3].alive = true;
//    board_array[3][4].alive = true;
//    board_array[4][4].alive = true;
    // пентадекатлон
    board_array[17][10].alive = true;
    board_array[17][11].alive = true;
    board_array[16][12].alive = true;
    board_array[18][12].alive = true;
    board_array[17][13].alive = true;
    board_array[17][14].alive = true;
    board_array[17][15].alive = true;
    board_array[17][16].alive = true;
    board_array[16][17].alive = true;
    board_array[18][17].alive = true;
    board_array[17][18].alive = true;
    board_array[17][19].alive = true;
}

void set_color(struct ColorPalette* colorPalette){
    switch (color_theme){
        case 1:
            // Черный
            colorPalette->AliveColor.r = 0;
            colorPalette->AliveColor.g = 0;
            colorPalette->AliveColor.b = 0;

            // Белый
            colorPalette->DeadColor.r = 255;
            colorPalette->DeadColor.g = 255;
            colorPalette->DeadColor.b = 255;

            //
            colorPalette->FontColor.r = 0;
            colorPalette->FontColor.g = 153;
            colorPalette->FontColor.b = 51;

            // Светло-серый
            colorPalette->BorderColor.r = 200;
            colorPalette->BorderColor.g = 200;
            colorPalette->BorderColor.b = 200;
            break;
        default: {
            colorPalette->DeadColor.r = 51;
            colorPalette->DeadColor.g = 51;
            colorPalette->DeadColor.b = 51;

            colorPalette->AliveColor.r = 0;
            colorPalette->AliveColor.g = 153;
            colorPalette->AliveColor.b = 51;

            colorPalette->FontColor.r = 0;
            colorPalette->FontColor.g = 0;
            colorPalette->FontColor.b = 0;

            colorPalette->BorderColor.r = 4;
            colorPalette->BorderColor.g = 24;
            colorPalette->BorderColor.b = 4;
            break;
        }
    }
}