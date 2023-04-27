#include <SDL.h>
#include <stdbool.h>

struct Cell{
    // true - white, false - black
    bool alive;
    //bool died;
    int pos_x;
    int pos_y;
};

struct Board {
    int height;
    int width;
    struct Cell** board_array;

};

int neighbors_count(struct Board* board, struct Cell* cell, int size);
struct Board init_board(int height, int width);
void draw_board(struct Board* board, SDL_Window* window, SDL_Renderer* renderer);
void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, int size, struct Board* board);
void recalculate(struct Board* board, int size);
int run_black_screen(SDL_Window*, SDL_Renderer*);
int change_screen_color(SDL_Window*, SDL_Renderer*);
struct Cell check_rules(struct Cell* cell, int count);


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Мое окно",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                              750, 750, SDL_WINDOW_SHOWN);
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
    struct Board board = init_board(15, 15);

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

    board.board_array[12][10].alive = true;
    board.board_array[12][11].alive = true;
    board.board_array[12][9].alive = true;

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
//    board.board_array[13][8].died = true;
//    board.board_array[12][7].died = true;
//    board.board_array[13][6].died = true;
    //printf("x: %d y: %d", board.board_array[14][9].pos_y, board.board_array[14][9].pos_x);
    //board.board_array[5][6].color = false;

    // calculate neighbors
//    for (int i=0; i<15; i++){
//        for(int j=0; j<15; j++) {
//            if (board.board_array[i][j].alive){
//                printf("Cell [%d][%d] has %d neighbors.\n", j+1, i+1, neighbors_count(&board, &board.board_array[i][j], 15));
//            }
//        }
//    }

    //draw_board(&board, window, renderer);

    // основной цикл обработки событий
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        draw_board(&board, window, renderer);
        recalculate(&board, 15);

        // обработка событий
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        recalculate(&board, 15);
                        draw_board(&board, window, renderer);
//                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
//                        SDL_RenderClear(renderer);
//                        SDL_RenderPresent(renderer);
                    }
                    break;
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



int run_black_screen(SDL_Window* window, SDL_Renderer* renderer){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int done = 0;

    while (!done) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    done = 1;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderClear(renderer);

                        SDL_RenderPresent(renderer);
                    }
                    break;
                }
                default: {break;}
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int change_screen_color(SDL_Window* window, SDL_Renderer* renderer){

    int r, g, b;
    r = g = b = 255;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int done = 0;

    while (!done) {
        r -= 5;
        g -= 25;
        b -= 15;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    done = 1;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_SPACE) {
//                        r -= 15;
//                        g -= 15;
//                        b -= 15;
//                        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
//                        SDL_RenderClear(renderer);
//
//                        SDL_RenderPresent(renderer);
                    }
                    break;
                }
                default: {break;}
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

// works
void draw_board(struct Board* board, SDL_Window* window, SDL_Renderer* renderer){
    // отрисовка поля квадратов
    int size = 15;
    SDL_Rect rects[size*size];

    // заполняем экран белым цветом
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    draw_cells(rects, renderer, size, board);

    // показать рендер
    SDL_RenderPresent(renderer);

    SDL_Delay(500);
}

void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, int size, struct Board* board){
    // отрисовываем квадратов
    for (int i = 0; i<size; i++) {
        for (int j=0; j<size; j++) {
            // инициализируем клетки
            rects[i*size + j].y = (i) * 50;
            rects[i*size + j].x = (j) * 50;
            rects[i*size + j].w = 50;
            rects[i*size + j].h = 50;
            // закрашиваем клетки
            if (board->board_array[i][j].alive) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rects[i*size + j]);
            }
            // рисуем границу клеток
//            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//            SDL_RenderDrawRect(renderer, &rects[i * size + j]);
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
            struct Cell new_cell = {
                    .alive = false, /*.died = board->board_array[i][j].died,*/ .pos_x = j, .pos_y = i};
            // Создаем новый экземпляр структуры Cell
            int neighbors = neighbors_count(board, &board->board_array[i][j], 15);
            temp_board[i][j] = check_rules(&board->board_array[i][j], neighbors); // Присваиваем значение элементу массива
            temp_board[i][j].pos_x = j;
            temp_board[i][j].pos_y = i;
        }
    }
    free(board->board_array);
    board->board_array = temp_board;
}

struct Cell check_rules(struct Cell* cell, int count){
    struct Cell result;
    if (!cell->alive && count == 3){
        // правило 4
            result.alive = true;
        return result;
    } else if (!cell->alive){
        result.alive = false;
        return result;
    }
    if (count < 2) {
        result.alive = false;
        //temp_board[i][j].died = true;
        // правило 2
    } else if (count > 3){
        result.alive = false;
        // правило 3
    }else {
        result.alive = true;
    }

    return result;
}