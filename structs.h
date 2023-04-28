//
// Created by Алексей Янкович on 28.04.23.
//

#ifndef CONWAYS_GAME_OF_LIFE_STRUCTS_H
#define CONWAYS_GAME_OF_LIFE_STRUCTS_H

struct Cell{
    bool alive;
    int pos_x;
    int pos_y;
};

struct Board {
    int height;
    int width;
    struct Cell** board_array;

};

#endif //CONWAYS_GAME_OF_LIFE_STRUCTS_H
