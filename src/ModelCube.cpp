﻿#include "../include/HeaderApp.hpp"

bool ModelCube::init(D3DManager* pManager) {

    const unsigned int kNumVtx = 24U;
    const unsigned int kNumIdx = 36U;
    numIdx = kNumIdx;

    struct Vertex dataPCNU[kNumVtx] = {
        // right
        {+5.f, -5.f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {+5.f, +5.f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {+5.f, +5.f, +5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {+5.f, -5.f, +5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        // left
        {-5.f, -5.f, +5.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-5.f, +5.f, +5.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-5.f, +5.f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-5.f, -5.f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        // top
        {-5.f, +5.f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {-5.f, +5.f, +5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {+5.f, +5.f, +5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {+5.f, +5.f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        // bottom
        {-5.f, -5.f, +5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        {-5.f, -5.f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        {+5.f, -5.f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        {+5.f, -5.f, +5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        // back
        {+5.f, -5.f, +5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {+5.f, +5.f, +5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {-5.f, +5.f, +5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {-5.f, -5.f, +5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        // front
        {-5.f, -5.f, -5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-5.f, +5.f, -5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, +5.f, -5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {+5.f, -5.f, -5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},

    };
    float idxSmall[6] = {0, 1, 2, 0, 2, 3};
    unsigned int dataIdx[kNumIdx];

    for (int i = 0; i < kNumIdx; ++i) {
        dataIdx[i] = idxSmall[i % 6] + 4 * (i / 6);
    }

    return pManager->createModelBuffers(kNumVtx, dataPCNU, dataIdx, this);
}