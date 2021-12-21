#include "../include/HeaderTetris.hpp"
#include "../include/resource.hpp"
#include <random>

int Tetris::RanNum(int up, int low) {
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<int> dist(up, low);
    return dist(mt);
}
Tetris::Tetris(D3DManager* in_dmanager, InputManager* in_imanager) {

    dmanager = in_dmanager;
    imanager = in_imanager;

    dmanager->createTexture(CELL, &cell);
    dmanager->createTexture(CELL_0, &cell_0);
    dmanager->createTexture(CELL_1, &cell_1);
    dmanager->createTexture(CELL_2, &cell_2);
    dmanager->createTexture(CELL_3, &cell_3);
    dmanager->createTexture(CELL_4, &cell_4);
    dmanager->createTexture(CELL_5, &cell_5);
    dmanager->createTexture(CELL_6, &cell_6);
    dmanager->createTexture(CELL_7, &cell_7);
    dmanager->createTexture(CELL_8, &cell_8);
    dmanager->createTexture(CELL_9, &cell_9);

    dmanager->createTexture(BLOCK, &block);

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            board[i][j].kinds = 0;
            board[i][j].num = 0;
        }
    }
    for (int i = 0; i < bHeight; i++) {
        board[i][0].kinds = 3;
        board[i][bWidth - 1].kinds = 3;
    }
    for (int i = 0; i < bWidth; i++) {
        board[bHeight - 1][i].kinds = 3;
    }
    char list[112] = {//
        1, 1, 1, 1,   // I
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        0, 0, 1, 0,   // reL
        1, 1, 1, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        1, 0, 0, 0,   // L
        1, 1, 1, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        0, 1, 0, 0,   // T
        1, 1, 1, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        1, 1, 0, 0,   //□
        1, 1, 0, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        1, 1, 0, 0,   // reS
        0, 1, 1, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0,   //
        0, 1, 1, 0,   // S
        1, 1, 0, 0,   //
        0, 0, 0, 0,   //
        0, 0, 0, 0};  //
    for (int i = 0; i < 112; i++) {
        minos[i] = list[i];
    }
    cube.init(dmanager);
    makeMino();
}

void Tetris::makeMino() {
    static unsigned int perm[7] = {0, 1, 2, 3, 4, 5, 6};
    static unsigned int newPerm[7] = {0, 1, 2, 3, 4, 5, 6};
    static unsigned int cNumPerm[4] = {1, 1, 1, 1};
    static int mCou = 0;
    static int cNumCou = 0;

    for (int i = 0; i < 3; i++) {
        int num = RanNum(0, 2 - i);
        int selected = cNumPerm[num];
        cNumPerm[num] = cNumPerm[3 - i];
        cNumPerm[3 - i] = selected;
    }
    if (mCou % 7 == 0) {
        for (int i = 0; i < 7; i++) {
            perm[i] = newPerm[i];
        }
        for (int i = 0; i < 6; i++) {
            int num = RanNum(0, 5 - i);
            int selected = newPerm[num];
            newPerm[num] = newPerm[6 - i];
            newPerm[6 - i] = selected;
        }
    }
    int mino = perm[mCou % 7];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (minos[16 * mino + 4 * i + j] > 0) {
                board[i][j + 4].num = cNumPerm[cNumCou];
                board[i][j + 4].kinds = 1;
                cNumCou++;
            }
        }
    }

    // nextmino

    int numNext = perm[1 + mCou % 7];
    int numAftNext = perm[2 + mCou % 7];
    if (mCou % 7 < 6) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (minos[16 * numNext + 4 * i + j] > 0) {
                    nextMino[i][j].kinds = 1;
                    nextMino[i][j].num = -1;
                } else {
                    nextMino[i][j].kinds = 0;
                    nextMino[i][j].num = 0;
                }
                if (minos[16 * numAftNext + 4 * i + j]) {
                    nextMino[i + 3][j].kinds = 1;
                    nextMino[i + 3][j].num = -1;
                } else {
                    nextMino[i + 3][j].kinds = 0;
                    nextMino[i + 3][j].num = 0;
                }
            }
        }
    } else if (1 == mCou % 7) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (minos[16 * numNext + 4 * i + j] > 0) {
                    nextMino[i][j].kinds = 1;
                    nextMino[i][j].num = -1;
                } else {
                    nextMino[i][j].kinds = 0;
                    nextMino[i][j].num = 0;
                }
                if (minos[16 * newPerm[0] + 4 * i + j] > 0) {
                    nextMino[i + 3][j].kinds = 1;
                    nextMino[i + 3][j].num = -1;
                } else {
                    nextMino[i + 3][j].kinds = 0;
                    nextMino[i + 3][j].num = 0;
                }
            }
        }
    } else {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (minos[16 * newPerm[0] + 4 * i + j] > 0) {
                    nextMino[i][j].kinds = 1;
                    nextMino[i][j].num = -1;
                } else {
                    nextMino[i][j].kinds = 0;
                    nextMino[i][j].num = 0;
                }
                if (minos[16 * newPerm[1] + 4 * i + j] > 0) {
                    nextMino[i + 3][j].kinds = 1;
                    nextMino[i + 3][j].num = -1;
                } else {
                    nextMino[i + 3][j].kinds = 0;
                    nextMino[i + 3][j].num = 0;
                }
            }
        }
    }

    mCou++;
    roCou = 16382;
    cNumCou = 0;
}
void Tetris::fallMino() {

    CellInf newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j] = board[i][j];
        }
    }
    for (int i = bHeight - 1; i >= 0; i--) {
        for (int j = 0; j < bWidth; j++) {
            if (board[i][j].kinds == 1 && board[i + 1][j].kinds < 2) {
                newBoard[i][j].kinds = 0;
                newBoard[i + 1][j].num = board[i][j].num;
                newBoard[i + 1][j].kinds = 1;
            } else if (board[i][j].kinds == 1 && board[i + 1][j].kinds > 1) {
                for (int i = 0; i < bHeight; i++) {
                    for (int j = 0; j < bWidth; j++) {
                        if (board[i][j].kinds == 1)
                            board[i][j].kinds = 2;
                    }
                }
                checkLine();
                makeMino();
                return;
            }
        }
    }

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

void Tetris::checkKey() {
    const int KEY_LEFT = 0;
    const int KEY_RIGHT = 1;
    const int KEY_DOWN = 2;
    const int KEY_UP = 3;
    const int KEY_Z = 4;
    const int KEY_C = 5;
    const int KEY_Q = 6;

#define keepPush 0b001
#define keepDePush 0b000
#define justPush 0b011
#define justDePush 0b100

    if (flame % 5 == 0) {
        if (imanager->getKey(KEY_LEFT) & keepPush) {
            moveMino(KEY_LEFT);
        }

        if (imanager->getKey(KEY_RIGHT) & keepPush) {
            moveMino(KEY_RIGHT);
        }

        if (imanager->getKey(KEY_DOWN) & keepPush) {
            fallMino();
        }
        if (imanager->getKey(KEY_UP) & keepPush) {
        }
    }
    if (flame % 3 == 0) {
        if (imanager->getKey(KEY_C) & keepPush) {
            rotateMino(KEY_C);
            if (std::abs(roCou - 16382) > 3)
                fallMino();
        }
        if (imanager->getKey(KEY_Z) & keepPush) {
            rotateMino(KEY_Z);
            if (std::abs(roCou - 16382) > 3)
                fallMino();
        }
    }
    if (imanager->getKey(KEY_Q)) {
        PostQuitMessage(0);
    }
}

void Tetris::moveMino(int keyIn) {
    const int KEY_LEFT = 0;
    const int KEY_RIGHT = 1;
    const int KEY_DOWN = 2;
    const int KEY_UP = 3;

    CellInf newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j] = board[i][j];
        }
    }

    if (keyIn == KEY_RIGHT) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = bWidth - 1; j > 0; j--) {
                if (board[i][j].kinds == 1 && board[i][j + 1].kinds < 2) {
                    newBoard[i][j].kinds = 0;
                    newBoard[i][j + 1].kinds = 1;
                    newBoard[i][j + 1].num = board[i][j].num;
                } else if (board[i][j].kinds == 1 && board[i][j + 1].kinds > 1) {
                    return;
                }
            }
        }
        for (int i = 0; i < bHeight; i++) {
            for (int j = 0; j < bWidth; j++) {
                board[i][j] = newBoard[i][j];
            }
        }
        return;
    }

    if (keyIn == KEY_LEFT) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 1; j < bWidth; j++) {
                if (board[i][j].kinds == 1 && board[i][j - 1].kinds < 2) {
                    newBoard[i][j].kinds = 0;
                    newBoard[i][j - 1].kinds = 1;
                    newBoard[i][j - 1].num = board[i][j].num;
                } else if (board[i][j].kinds == 1 && board[i][j - 1].kinds > 1) {
                    return;
                }
            }
        }
        for (int i = 0; i < bHeight; i++) {
            for (int j = 0; j < bWidth; j++) {
                board[i][j] = newBoard[i][j];
            }
        }
        return;
    }
}

void Tetris::rotateMino(int keyIn) {

    const int KEY_Z = 4;
    const int KEY_C = 5;

    CellInf newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j].kinds = 0;
            newBoard[i][j].num = board[i][j].num;
            if (board[i][j].kinds == 2) {
                newBoard[i][j].kinds = 2;
                newBoard[i][j].num = board[i][j].num;
            }
        }
    }
    for (int i = 0; i < bHeight; i++) {
        newBoard[i][0].kinds = 3;
        newBoard[i][0].num = 0;
        newBoard[i][bWidth - 1].kinds = 3;
        newBoard[i][bWidth - 1].num = 0;
    }
    for (int i = 0; i < bWidth; i++) {
        newBoard[bHeight - 1][i].kinds = 3;
        newBoard[bHeight - 1][i].num = 0;
    }

    int xCou = 0;
    int yCou = 0;
    int numCou = 0;

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            if (1 == board[i][j].kinds) {
                xCou += j;
                yCou += i;
                numCou++;
            }
        }
    }
    int aveX = xCou / numCou;
    int aveY = yCou / numCou;

    if (keyIn == KEY_C) {
        roCou--;
    }

    if (keyIn == KEY_Z) {
        roCou++;
    }

    if (roCou % 2 == 0) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 1; j < bWidth - 1; j++) {
                if (board[i][j].kinds == 1) {
                    float lerX = j - aveX;
                    float lerY = i - aveY;
                    if ((aveY + (int)lerX) > 0 && (aveY + (int)lerX) < (bHeight - 1) && (aveX - (int)lerY) > 0 &&
                        (aveX - (int)lerY) < (bWidth - 1) && board[aveY + (int)lerX][aveX - (int)lerY].kinds != 2) {
                        newBoard[aveY + (int)lerX][aveX - (int)lerY].kinds = 1;
                        newBoard[aveY + (int)lerX][aveX - (int)lerY].num = board[i][j].num;
                    } else {
                        return;
                    }
                }
            }
        }
    }
    if (roCou % 2 == 1) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 0; j < bWidth; j++) {
                if (board[i][j].kinds == 1) {
                    float lerX = j - aveX;
                    float lerY = i - aveY;
                    if ((aveY - (int)lerX) > 0 && (aveY - (int)lerX) < (bHeight - 1) && (aveX + (int)lerY) > 0 &&
                        (aveX + (int)lerY) < (bWidth - 1) && board[aveY - (int)lerX][aveX + (int)lerY].kinds != 2) {
                        newBoard[aveY - (int)lerX][aveX + (int)lerY].kinds = 1;
                        newBoard[aveY - (int)lerX][aveX + (int)lerY].num = board[i][j].num;
                    } else {
                        return;
                    }
                }
            }
        }
    } else {
        return;
    }
    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

void Tetris::checkLine() {
    for (int i = 0; i < bHeight; i++) {
        int lineCou = 0;
        for (int j = 0; j < bWidth; j++) {
            lineCou += board[i][j].num;
        }
        if (10 == lineCou) {
            CellInf newBoard[bHeight][bWidth];
            for (int I = 0; I < bHeight; I++) {
                for (int J = 0; J < bWidth; J++) {
                    newBoard[I][J].kinds = 0;
                    newBoard[I][J].num = 0;
                }
            }
            for (int J = 1; J < bWidth - 1; J++) {
                board[i][J].kinds = 0;
                board[i][J].num = 0;
            }
            for (int I = 0; I < bHeight; I++) {
                for (int J = 0; J < bWidth; J++) {
                    if (board[I][J].kinds == 2) {
                        newBoard[I][J].kinds = 2;
                        newBoard[I][J].num = board[I][J].num;
                    }
                }
            }
            for (int I = 0; I < bHeight; I++) {
                newBoard[I][0].kinds = 3;
                newBoard[I][0].num = 0;
                newBoard[I][bWidth - 1].kinds = 3;
                newBoard[I][bWidth - 1].num = 0;
            }
            for (int I = 0; I < bWidth; I++) {
                newBoard[bHeight - 1][I].kinds = 3;
                newBoard[bHeight - 1][I].num = 0;
            }
            for (int I = i; I >= 0; I--) {
                for (int J = 0; J < bWidth; J++) {
                    if (board[I][J].kinds == 2) {
                        newBoard[I][J].kinds = 0;
                        newBoard[I][J].num = 0;
                        newBoard[I + 1][J].kinds = 2;
                        newBoard[I + 1][J].num = board[I][J].num;
                    }
                }
            }
            for (int I = 0; I < bHeight; I++) {
                for (int J = 0; J < bWidth; J++) {
                    board[I][J] = newBoard[I][J];
                }
            }
            i = 0;
        }
    }
}

void Tetris::dispBoard() {

    cube.colG = 0;
    cube.colR = 0;

    cube.sclX = 80;
    cube.sclY = 80;
    dmanager->applyTexture(&cell);
    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            if (board[i][j].kinds == 1) {
                dmanager->applyTexture(&cell);
                cube.colR = 0.9;
                cube.colG = 0;
                cube.colB = 0;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                if (board[i][j].num == 0) {
                    dmanager->applyTexture(&cell_0);
                } else if (board[i][j].num == 1) {
                    dmanager->applyTexture(&cell_1);
                } else if (board[i][j].num == 2) {
                    dmanager->applyTexture(&cell_2);
                } else if (board[i][j].num == 3) {
                    dmanager->applyTexture(&cell_3);
                } else if (board[i][j].num == 4) {
                    dmanager->applyTexture(&cell_4);
                } else if (board[i][j].num == 5) {
                    dmanager->applyTexture(&cell_5);
                } else if (board[i][j].num == 6) {
                    dmanager->applyTexture(&cell_6);
                } else if (board[i][j].num == 7) {
                    dmanager->applyTexture(&cell_7);
                } else if (board[i][j].num == 8) {
                    dmanager->applyTexture(&cell_8);
                } else if (board[i][j].num == 9) {
                    dmanager->applyTexture(&cell_9);
                } else {
                    dmanager->applyTexture(&cell);
                }
                dmanager->drawModel(&cube);
            } else if (board[i][j].kinds == 2) {
                dmanager->applyTexture(&cell);
                cube.colR = 0.5;
                cube.colG = 0.0;
                cube.colB = 0.0;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                if (board[i][j].num == 0) {
                    dmanager->applyTexture(&cell_0);
                } else if (board[i][j].num == 1) {
                    dmanager->applyTexture(&cell_1);
                } else if (board[i][j].num == 2) {
                    dmanager->applyTexture(&cell_2);
                } else if (board[i][j].num == 3) {
                    dmanager->applyTexture(&cell_3);
                } else if (board[i][j].num == 4) {
                    dmanager->applyTexture(&cell_4);
                } else if (board[i][j].num == 5) {
                    dmanager->applyTexture(&cell_5);
                } else if (board[i][j].num == 6) {
                    dmanager->applyTexture(&cell_6);
                } else if (board[i][j].num == 7) {
                    dmanager->applyTexture(&cell_7);
                } else if (board[i][j].num == 8) {
                    dmanager->applyTexture(&cell_8);
                } else if (board[i][j].num == 9) {
                    dmanager->applyTexture(&cell_9);
                } else {
                    dmanager->applyTexture(&cell);
                }
                dmanager->drawModel(&cube);
            } else if (board[i][j].kinds == 3) {
                dmanager->applyTexture(&block);
                cube.colR = 0.5;
                cube.colG = 0.5;
                cube.colB = 0.5;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                dmanager->drawModel(&cube);
            }
        }
    }
}

void Tetris::dispNextMino() {
    cube.colG = 0;
    cube.colR = 0;
    cube.sclX = 80;
    cube.sclY = 80;
    dmanager->applyTexture(&cell);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (nextMino[i][j].kinds == 1) {
                dmanager->applyTexture(&cell);
                cube.colR = 0.9;
                cube.colG = 0;
                cube.colB = 0;
                cube.posX = +j * 80 + 700;
                cube.posY = -i * 80 + 700;
                dmanager->drawModel(&cube);
            }
        }
    }
}

int Tetris::Tmain() {
    checkKey();
    if (flame % 30 == 0) {
        fallMino();
    }
    dispBoard();
    dispNextMino();
    flame++;
    return 1;
}
