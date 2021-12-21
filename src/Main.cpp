#include "../include/HeaderTetris.hpp"
#include "../include/resource.hpp"

#include <chrono>
#include <iostream>
void dispTime() {

    using namespace std::chrono;

    static high_resolution_clock::time_point oldTime = high_resolution_clock::now();
    static high_resolution_clock::time_point nowTime = high_resolution_clock::now();
    nowTime = high_resolution_clock::now();
    // 1flame描画するのにかかった時間の取得
    nanoseconds elapsed_time = duration_cast<nanoseconds>(nowTime - oldTime);
    std::cout << "fps " << 1000000000 / elapsed_time.count() << std::endl;
    oldTime = nowTime;
}

void rgb(Model& in_model) {
    const float PI = 3.1415926535;
    static float time = 0;
    in_model.colR = 10000 * std::sinf(PI * time);
    in_model.colG = 10000 * std::sinf(2 * PI / 3 + PI * time);
    in_model.colB = 10000 * std::sinf(4 * PI / 3 + PI * time);
    time += 0.1;
}

int main() {
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWDEFAULT);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR pCmd, int cmdShow) {
    Sleep(120);

    LPCWSTR kNameWnd = L"テスト";
    LPCWSTR kNameWndClass = L"DX11_CLASS";
    const unsigned int kWidth = 2736U;
    const unsigned int kHeight = 1824U;
    const bool kWindowed = MessageBoxW(nullptr, L"フルスクリーンで起動しますか", L"確認", MB_YESNO) == IDNO;

    D3DManager dmanager = D3DManager();

    if (!dmanager.init(hInst, cmdShow, kNameWnd, kNameWndClass, kWidth, kHeight, kWindowed))
        return 1;

    // camera
    Camera camera = Camera();
    dmanager.createCamera((float)kWidth, (float)kHeight, &camera);
    camera.posZ = -20.f;

    dmanager.applyCamera(&camera);

    // model

    ModelSquare BG = ModelSquare();
    if (!BG.init(&dmanager))
        dmanager.DebugBox("error");

    BG.sclY = 5000;
    BG.sclX = 5000;
    BG.posZ = 200;
    BG.colR = 0.1;
    BG.colG = 0.1;
    BG.colB = 0.1;
    ModelSquare BG_C = ModelSquare();
    if (!BG_C.init(&dmanager))
        dmanager.DebugBox("error");

    BG_C.sclY = 1800;
    BG_C.sclX = 825;
    BG_C.posX = -30;
    BG_C.posY = 100;
    BG_C.posZ = 100;

    ModelSquare BG_L = ModelSquare();
    if (!BG_L.init(&dmanager))
        dmanager.DebugBox("error");

    ModelSquare BG_R = ModelSquare();
    if (!BG_R.init(&dmanager))
        dmanager.DebugBox("error");

    // texture
    Texture Back = Texture();
    dmanager.createTexture(BOLD, &Back);

    // input
    const int KEY_LEFT = 0;
    const int KEY_RIGHT = 1;
    const int KEY_DOWN = 2;
    const int KEY_UP = 3;
    const int KEY_Z = 4;
    const int KEY_C = 5;
    const int KEY_Q = 6;

    InputManager imanager = InputManager();

    imanager.addKeycode(KEY_LEFT, VK_LEFT, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_DPAD_LEFT);
    imanager.addKeycode(KEY_RIGHT, VK_RIGHT, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager.addKeycode(KEY_UP, VK_UP, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_DPAD_UP);
    imanager.addKeycode(KEY_DOWN, VK_DOWN, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_DPAD_DOWN);
    imanager.addKeycode(KEY_Z, 0x5A, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_A);
    imanager.addKeycode(KEY_C, 0x43, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_B);
    imanager.addKeycode(KEY_Q, 0x51, GAMEPAD_KEYTYPE::Buttons, XINPUT_GAMEPAD_START);
    // te
    Tetris Tmanager = Tetris(&dmanager, &imanager);

    // main loop
    float Time = 0.;
    MSG msg;
    while (true) {
        dispTime();
        if (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } else {
            imanager.inspect();
            dmanager.drawBegin();
            dmanager.applyTexture(&Back);
            dmanager.drawModel(&BG);
            dmanager.drawModel(&BG_C);
            if (!Tmanager.Tmain())
                dmanager.DebugBox("error");
            dmanager.applyCamera(&camera);
            dmanager.drawEnd();
        }
    }

    UnregisterClassW(kNameWndClass, hInst);
    return 0;
}