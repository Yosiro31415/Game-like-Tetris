#include "../include/HeaderTetris.hpp"
#include "../include/resource.hpp"
#include <random>
namespace random {
std::mt19937 mt{std::random_device{}()};

std::uniform_int_distribution<int> dist(1, 6);

} // namespace random

Tetris::Tetris(D3DManager& dmanager) {
    dmanager.createTexture(CELL, &cell);
    dmanager.createTexture(BLOCK, &block);
    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i < bHeight; i++) {
        board[i][0] = 3;
        board[i][bWidth - 1] = 3;
    }
    for (int i = 0; i < bWidth; i++) {
        board[bHeight - 1][i] = 3;
    }
    int list[112] = {//
        1, 1, 1, 1,  // I
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        0, 0, 1, 0,  // reL
        1, 1, 1, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        1, 0, 0, 0,  // L
        1, 1, 1, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        0, 1, 0, 0,  // T
        1, 1, 1, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        1, 1, 0, 0,  //□
        1, 1, 0, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        1, 1, 0, 0,  // reS
        0, 1, 1, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0,  //
        0, 1, 1, 0,  // S
        1, 1, 0, 0,  //
        0, 0, 0, 0,  //
        0, 0, 0, 0}; //
    for (int i = 0; i < 112; i++) {
        minos[i] = list[i];
    }
    makeMino();
}
void Tetris::makeMino() {
    static unsigned int perm[7] = {0, 1, 2, 3, 4, 5, 6};

    if (mCounta % 7 == 0) {
        for (int i = 0; i < 6; i++) {
            int num = RanNum(0, 5 - i);
            int selected = perm[num];
            perm[num] = perm[6 - i];
            perm[6 - i] = selected;
        }
    }
    int mino = perm[mCounta % 7];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j + 4] += minos[16 * mino + 4 * i + j];
        }
    }
    mCounta++;
    roCou = 16382;
}
void Tetris::fallMino() {
    int newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j] = board[i][j];
        }
    }

    for (int i = bHeight - 1; i >= 0; i--) {
        for (int j = 0; j < bWidth; j++) {
            if (board[i][j] == 1 && board[i + 1][j] < 2) {
                newBoard[i][j] = 0;
                newBoard[i + 1][j] = 1;
            } else if (board[i][j] == 1 && board[i + 1][j] >= 2) {
                for (int i = 0; i < bHeight; i++) {
                    for (int j = 0; j < bWidth; j++) {
                        if (board[i][j] == 1)
                            board[i][j] = 2;
                    }
                }
                checkMinos();
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

void Tetris::getKeyIn(InputManager& imanager) {
    const int LEFT = 0;
    const int RIGHT = 1;
    const int DOWN = 2;
    const int UP = 3;
    const int KEY_Z = 4;
    const int KEY_C = 5;

#define keepPush 0b001
#define keepDePush 0b000
#define justPush 0b011
#define justDePush 0b100

    if (flame % 5 == 0) {
        if (imanager.getKey(LEFT) & keepPush) {
            moveMino(LEFT);
        }

        if (imanager.getKey(RIGHT) & keepPush) {
            moveMino(RIGHT);
        }

        if (imanager.getKey(DOWN) & keepPush) {
            fallMino();
        }
        if (imanager.getKey(UP) & keepPush) {
        }
    }
    if (flame % 3 == 0) {
        if (imanager.getKey(KEY_C) & keepPush) {
            rotateMino(KEY_C);
            if (std::abs(roCou - 16382) % 1 || std::abs(roCou - 16382) > 3)
                fallMino();
        }
        if (imanager.getKey(KEY_Z) & keepPush) {
            rotateMino(KEY_Z);
            if (std::abs(roCou - 16382) % 1 || std::abs(roCou - 16382) > 3)
                fallMino();
        }
    }
}

void Tetris::moveMino(int keyIn) {
    const int LEFT = 0;
    const int RIGHT = 1;
    const int DOWN = 2;
    const int UP = 3;

    int newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j] = board[i][j];
        }
    }

    if (keyIn == RIGHT) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = bWidth - 1; j > 0; j--) {
                if (board[i][j] == 1 && board[i][j + 1] < 2) {
                    newBoard[i][j] = 0;
                    newBoard[i][j + 1] = 1;
                } else if (board[i][j] == 1 && board[i][j + 1] > 1) {
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

    if (keyIn == LEFT) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 1; j < bWidth; j++) {
                if (board[i][j] == 1 && board[i][j - 1] < 2) {
                    newBoard[i][j] = 0;
                    newBoard[i][j - 1] = 1;
                } else if (board[i][j] == 1 && board[i][j - 1] > 1) {
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

    int newBoard[bHeight][bWidth];

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            newBoard[i][j] = 0;
            if (board[i][j] == 2) {
                newBoard[i][j] = 2;
            }
        }
    }
    for (int i = 0; i < bHeight; i++) {
        newBoard[i][0] = 3;
        newBoard[i][bWidth - 1] = 3;
    }
    for (int i = 0; i < bWidth; i++) {
        newBoard[bHeight - 1][i] = 3;
    }

    int countaX = 0;
    int countaY = 0;
    int numCounta = 0;

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            if (board[i][j] == 1) {
                countaX += j;
                countaY += i;
                numCounta++;
            }
        }
    }
    int aveX = countaX / numCounta;
    int aveY = countaY / numCounta;

    if (keyIn == KEY_C) {
        roCou--;
    }

    if (keyIn == KEY_Z) {
        roCou++;
    }

    if (roCou % 2 == 0) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 1; j < bWidth - 1; j++) {
                if (board[i][j] == 1) {
                    float lerX = j - aveX;
                    float lerY = i - aveY;
                    if ((aveY + (int)lerX) > 0 && (aveY + (int)lerX) < (bHeight - 1) && (aveX - (int)lerY) > 0 &&
                        (aveX - (int)lerY) < (bWidth - 1) && board[aveY + (int)lerX][aveX - (int)lerY] != 2)
                        newBoard[aveY + (int)lerX][aveX - (int)lerY] = 1;
                    else {
                        return;
                    }
                }
            }
        }
    }
    if (roCou % 2 == 1) {
        for (int i = 0; i < bHeight; i++) {
            for (int j = 0; j < bWidth; j++) {
                if (board[i][j] == 1) {
                    float lerX = j - aveX;
                    float lerY = i - aveY;
                    if ((aveY - (int)lerX) > 0 && (aveY - (int)lerX) < (bHeight - 1) && (aveX + (int)lerY) > 0 &&
                        (aveX + (int)lerY) < (bWidth - 1) && board[aveY - (int)lerX][aveX + (int)lerY] != 2)
                        newBoard[aveY - (int)lerX][aveX + (int)lerY] = 1;
                    else {

                        return;
                    }
                }
            }
        }
    } else {
        return;
    }

    // if (std::abs(roCou - 16382) % 2 == 1) {

    //}

    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

void Tetris::checkMinos() {
    for (int i = 0; i < bHeight; i++) {
        short lineCounta = 0;
        for (int j = 0; j < bWidth; j++) {
            lineCounta += board[i][j];
        }
        if (lineCounta == 26) {
            int newBoard[bHeight][bWidth];
            for (int I = 0; I < bHeight; I++) {
                for (int J = 0; J < bWidth; J++) {
                    newBoard[I][J] = 0;
                }
            }

            for (int J = 1; J < bWidth - 1; J++) {
                board[i][J] = 0;
            }
            for (int I = 0; I < bHeight; I++) {
                for (int J = 0; J < bWidth; J++) {
                    if (board[I][J] == 2) {
                        newBoard[I][J] = 2;
                    }
                }
            }
            for (int I = 0; I < bHeight; I++) {
                newBoard[I][0] = 3;
                newBoard[I][bWidth - 1] = 3;
            }
            for (int I = 0; I < bWidth; I++) {
                newBoard[bHeight - 1][I] = 3;
            }
            for (int I = i; I >= 0; I--) {
                for (int J = 0; J < bWidth; J++) {
                    if (board[I][J] == 2) {
                        newBoard[I][J] = 0;
                        newBoard[I + 1][J] = 2;
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

void Tetris::dispBoard(D3DManager& dmanager) {
    static ModelSquare cube;
    cube.init(&dmanager);
    cube.colG = 0;
    cube.colR = 0;
    cube.sclX = 80;
    cube.sclY = 80;

    dmanager.applyTexture(&cell);
    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            if (board[i][j] == 1) {
                dmanager.applyTexture(&cell);
                cube.colR = 0.9;
                cube.colG = 0;
                cube.colB = 0;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                dmanager.drawModel(&cube);
            } else if (board[i][j] == 2) {
                dmanager.applyTexture(&cell);
                cube.colR = 0.5;
                cube.colG = 0.0;
                cube.colB = 0.0;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                dmanager.drawModel(&cube);
            } else if (board[i][j] == 3) {
                dmanager.applyTexture(&block);
                cube.colR = 0.5;
                cube.colG = 0.5;
                cube.colB = 0.5;
                cube.posX = +j * 80 - 80 * 6;
                cube.posY = -i * 80 + 80 * 11;
                dmanager.drawModel(&cube);
            }
        }
    }
}

int Tetris::Tmain(D3DManager& dmanager, InputManager& imanager) {

    getKeyIn(imanager);

    if (flame % 30 == 0) {
        fallMino();
    }

    dispBoard(dmanager);
    flame++;
    return 1;
}

int Tetris::RanNum(int Lower, int Upper) {
    using namespace std;

    random_device seedGen;
    mt19937 engineNumber(seedGen());
    uniform_real_distribution<> rangeGenerate(Lower, Upper);

    int numberOutput = rangeGenerate(engineNumber);

    return numberOutput;
}