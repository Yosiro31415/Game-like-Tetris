#include "../include/HeaderAPP.hpp"

struct CellInf {
    char kinds;
    char num;
};

class Tetris {

public:
    int Tmain();
    Tetris(D3DManager* dmanager, InputManager* imanager);

private:
    unsigned int flame = 0;
    const static char bHeight = 22;
    const static char bWidth = 12;
    short roCou = 12000;
    CellInf board[bHeight][bWidth];
    CellInf nextMino[5][4];
    char minos[112];

    void makeMino();
    void fallMino();
    void checkKey();
    void moveMino(int keyIn);
    void rotateMino(int keyIn);
    void checkLine();
    void dispBoard();
    void dispNextMino();
    int RanNum(int Lower, int Upper);

    D3DManager* dmanager;
    InputManager* imanager;

    ModelSquare cube;

    Texture block;
    Texture cell;
    Texture cell_0;
    Texture cell_1;
    Texture cell_2;
    Texture cell_3;
    Texture cell_4;
    Texture cell_5;
    Texture cell_6;
    Texture cell_7;
    Texture cell_8;
    Texture cell_9;
};
