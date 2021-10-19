#include "../include/HeaderApp.hpp"
bool ModelCircle::init(D3DManager* pManager) {
    const float C_PI = 3.141592;
    // number of vertex without center
    const unsigned int numVer = 10000U;
    const unsigned int kNumVtx = numVer + 1;
    const unsigned int kNumIdx = 3 * numVer;
    numIdx = kNumIdx;
    struct Vertex dataPCNU[kNumVtx];
    dataPCNU[0] = {0.f, 0.f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f};

    for (int i = 1; i < kNumVtx; i++) {
        dataPCNU[i] = {std::sinf(2.f * C_PI * (float)i / (float)numVer),
            std::cosf(2.f * C_PI * (float)i / (float)numVer), 0.f, std::sinf(2.f * C_PI * (float)i / (float)numVer),
            std::sinf(2 * C_PI / 3 + 2.f * C_PI * (float)i / (float)numVer),
            std::sinf(4 * C_PI / 3 + 2.f * C_PI * (float)i / (float)numVer), 1.0f, 0.0f, 0.0f, -1.0f};
    }

    unsigned int smallIdx[kNumVtx + 1];
    for (int i = 0; i < kNumVtx; i++) {
        smallIdx[i] = i;
    }
    smallIdx[kNumVtx] = 1;

    unsigned int dataIdx[kNumIdx];
    for (int i = 0; i < numVer; i += 1) {
        dataIdx[3 * i] = 0;
        dataIdx[3 * i + 1] = smallIdx[i + 1];
        dataIdx[3 * i + 2] = smallIdx[i + 2];
    }

    return pManager->createModelBuffers(kNumVtx, dataPCNU, dataIdx, this);
}