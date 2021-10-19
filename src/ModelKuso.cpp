#include "../include/HeaderApp.hpp"

bool ModelKuso::init(D3DManager* pManager) {

    const unsigned int kNumVtx = 8U;
    const unsigned int kNumIdx = 36U;
    numIdx = kNumIdx;

    struct Vertex dataPCNU[kNumVtx] =
       {{-5.f, -5.f, +5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-5.f, +5.f, +5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, +5.f, +5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, -5.f, +5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-5.f, -5.f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-5.f, +5.f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, +5.f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, -5.f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f}};
    unsigned int dataIdx[kNumIdx] = {
        0, 1, 2, 0, 2, 3, 7, 6, 5, 7, 5, 4, 3, 2, 6, 3, 6, 7, 5, 1, 0, 5, 0, 4, 2, 1, 5, 2, 5, 6, 3, 4, 0, 3, 7, 4};

    return pManager->createModelBuffers(kNumVtx, dataPCNU, dataIdx, this);
}