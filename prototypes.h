//
// Created by Алексей Янкович on 29.04.23.
//

#ifndef CONWAYS_GAME_OF_LIFE_PROTOTYPES_H
#define CONWAYS_GAME_OF_LIFE_PROTOTYPES_H

int neighbors_count(struct Board* board, struct Cell* cell, int size);
struct Board init_board(int height, int width);
void draw_board(struct Board* board, SDL_Renderer* renderer);
void draw_cells(SDL_Rect rects[], SDL_Renderer* renderer, int size, struct Board* board);
void recalculate(struct Board* board, int size);
struct Cell check_rules(struct Cell* cell, int count);
void add_cell(struct Board* board, int x, int y);

#endif //CONWAYS_GAME_OF_LIFE_PROTOTYPES_H
