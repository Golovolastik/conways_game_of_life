#include <SDL.h>

int run_black_screen(SDL_Window*, SDL_Renderer*);
int change_screen_color(SDL_Window*, SDL_Renderer*);



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

    //run_black_screen(window, renderer);
    change_screen_color(window, renderer);

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