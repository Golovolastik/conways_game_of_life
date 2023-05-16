//
// Created by Алексей Янкович on 29.04.23.
//

#ifndef CONWAYS_GAME_OF_LIFE_PROTOTYPES_H
#define CONWAYS_GAME_OF_LIFE_PROTOTYPES_H

int neighbors_count(struct Board* board, struct Cell* cell);
struct Board init_board(int height, int width);
void draw_board(struct Board* board, SDL_Renderer* renderer, TTF_Font* font);
void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, struct Board* board);
void recalculate(struct Board* board);
struct Cell check_rules(struct Cell* cell, int count);
void change_cell(struct Board* board, int x, int y);

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);
void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
void show_menu(SDL_Renderer *renderer, const char *file_path);

void game_events(SDL_Event* event, SDL_Renderer* renderer, struct Board* board, TTF_Font* font, int* state, bool* execute, bool* quit);
void menu_events(SDL_Event* event, SDL_Renderer* renderer, struct Board* board, TTF_Font* font, int* state, bool* execute, bool* quit);

void show_generation(TTF_Font* font, SDL_Renderer* renderer);




#endif //CONWAYS_GAME_OF_LIFE_PROTOTYPES_H
