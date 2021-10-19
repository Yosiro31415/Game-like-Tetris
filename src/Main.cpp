#include "../include/HeaderTetris.hpp"
#include "../include/resource.hpp"

void rgb(Model& in_model) {
    const float PI = 3.1415926535;
    static float time = 0;
    in_model.colR = 10000 * std::sinf(PI * time);
    in_model.colG = 10000 * std::sinf(2 * PI / 3 + PI * time);
    in_model.colB = 10000 * std::sinf(4 * PI / 3 + PI * time);
    time += 0.1;
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

    const int LEFT = 0;
    const int RIGHT = 1;
    const int DOWN = 2;
    const int UP = 3;
    const int KEY_Z = 4;
    const int KEY_C = 5;

    InputManager imanager = InputManager();

    imanager.addKeycode(LEFT, VK_LEFT, GAMEPAD_KEYTYPE::ThumbLL, XINPUT_GAMEPAD_DPAD_LEFT);
    imanager.addKeycode(RIGHT, VK_RIGHT, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager.addKeycode(UP, VK_UP, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager.addKeycode(DOWN, VK_DOWN, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager.addKeycode(KEY_Z, 0x5A, GAMEPAD_KEYTYPE::LTrigger, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager.addKeycode(KEY_C, 0x43, GAMEPAD_KEYTYPE::RTrigger, XINPUT_GAMEPAD_DPAD_RIGHT);
    // tetris
    Tetris Tmanager = Tetris(dmanager);

    // main loop
    float Time = 0.;
    MSG msg;
    while (true) {
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
            if (!Tmanager.Tmain(dmanager, imanager))
                dmanager.DebugBox("error");
            dmanager.applyCamera(&camera);
            dmanager.drawEnd();
        }
    }

    UnregisterClassW(kNameWndClass, hInst);
    return 0;
}