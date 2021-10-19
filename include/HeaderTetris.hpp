#include "../include/HeaderAPP.hpp"

struct cell{
    int kinds;
    int num; 
};

class Tetris {

public:
    int Tmain(D3DManager& dmanager, InputManager& imanager);
    Tetris(D3DManager& dmanager);

private:
    unsigned int flame = 0;
    unsigned int mCounta = 0;
    const static int bHeight = 22;
    const static int bWidth = 12;
    short roCou = 16382;
    int board[bHeight][bWidth];
    int minos[112];
    void initTetris();
    void makeMino();
    void fallMino();
    void getKeyIn(InputManager& imanager);
    void moveMino(int keyIn);
    void rotateMino(int keyIn);
    void checkMinos();
    void dispBoard(D3DManager& dmanager);
    int RanNum(int Lower, int Upper);
    Texture block;
    Texture cell;
};
