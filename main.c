#include <SDL.h>
#include <stdbool.h>

struct Board init_board(int height, int width);
void draw_board(struct Board* board, SDL_Window* window, SDL_Renderer* renderer);
int run_black_screen(SDL_Window*, SDL_Renderer*);
int change_screen_color(SDL_Window*, SDL_Renderer*);

struct Cell{
    // true - white, false - black
    bool color;
};

struct Board {
    int height;
    int width;
    struct Cell** board_array;

};



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Мое окно",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Ошибка при создании окна: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Ошибка при создании рендерера: %s\n", SDL_GetError());
        return 1;
    }

    // calculate board
    // render

    // создание поля
    struct Board board = init_board(10, 10);

    draw_board(&board, window, renderer);
    //run_black_screen(window, renderer);
    //change_screen_color(window, renderer);

    // основной цикл обработки событий
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        //draw_board(&board, window, renderer);
        // обработка событий
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                default:
                    break;
            }
        }
    }

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
        SDL_Delay(300);
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
    board.board_array = malloc(board.width *  sizeof(struct Cell*));
    for (int i = 0; i < board.height; i++) {
        board.board_array[i] = malloc(board.width * sizeof(struct Cell));
        // Инициализируем каждый элемент структурой Cell
        for (int j = 0; j < board.width; j++) {
            struct Cell new_cell = { .color = true }; // Создаем новый экземпляр структуры Cell
            board.board_array[i][j] = new_cell; // Присваиваем значение элементу массива
        }
    }

    return board;
}

void draw_board(struct Board* board, SDL_Window* window, SDL_Renderer* renderer){
    // отрисовка поля квадратов
    SDL_Rect rects[100];
    for (int i = 0; i < 100; i++) {
        rects[i].x = (i % 10) * 50;
        rects[i].y = (i / 10) * 50;
        rects[i].w = 50;
        rects[i].h = 50;
    }

    // заполняем экран белым цветом
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // отрисовываем 100 квадратов
    for (int i = 0; i < 100; i++) {
        // рисуем границу квадрата
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rects[i]);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    // показать рендер
    //SDL_RenderPresent(renderer);
    SDL_RenderFillRect(renderer, &rects[34]);
    SDL_RenderPresent(renderer);
}

void render(SDL_Window* window, SDL_Renderer* renderer, struct Board* board){

}