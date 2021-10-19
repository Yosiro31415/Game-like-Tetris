#pragma once
#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <wrl/client.h>
#include <cmath>
#include <unordered_map>
#include <xinput.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "xinput.lib")

using Microsoft::WRL::ComPtr;

struct ConstantBuffer {
    DirectX::XMFLOAT4X4 matScl;
    DirectX::XMFLOAT4X4 matRot;
    DirectX::XMFLOAT4X4 matTrs;
    DirectX::XMFLOAT4X4 matView;
    DirectX::XMFLOAT4X4 matProj;
    DirectX::XMFLOAT4 vecColar;
    DirectX::XMFLOAT4 vecLight;
};

struct D3DInf {
    //ジェネラル
    ComPtr<ID3D11Device> pDevice;
    ComPtr<ID3D11DeviceContext> pImContext;
    ComPtr<IDXGISwapChain> pSwapChain;
    ComPtr<ID3D11RenderTargetView> pRTView;
    ComPtr<ID3D11DepthStencilView> pDSView;
    D3D11_VIEWPORT viewport;

    // shader
    ComPtr<ID3D11VertexShader> pVShader;
    ComPtr<ID3D11PixelShader> pPShader;

    // polygon
    ComPtr<ID3D11Buffer> pCBuffer;
    ConstantBuffer cbuffer;
    // maybe vertex call
    ComPtr<ID3D11InputLayout> pILayout;
};

struct Vertex {
    float pcnu[12];
};

struct ModelInf {
    unsigned int numIdx;
    float posX, posY, posZ;
    float degX, degY, degZ;
    float sclX, sclY, sclZ;
    float colR, colG, colB, colA;
    ComPtr<ID3D11Buffer> pVBuffer;
    ComPtr<ID3D11Buffer> pIBuffer;
};

struct Camera {
    float width, height;
    float angle, nearZ, farZ;
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    float uppX, uppY, uppZ;
};

struct Texture {
    unsigned int width, height;
    ComPtr<ID3D11ShaderResourceView> pSRView;
};

class D3DManager {
private:
    HWND hWnd;
    D3DInf inf;

public:
    D3DManager();
    void quit(HINSTANCE hInst);
    // general
    void drawBegin();
    void drawEnd();
    bool init(HINSTANCE hInst, int cmdShow, LPCWSTR nameWnd, LPCWSTR nameWndClass, unsigned int width,
        unsigned int height, bool windowed);
    HWND* getWindowHandle();

    // model
    bool createModelBuffers(unsigned int numVtx, Vertex* dataPCU, unsigned int* dataIdxm, ModelInf* minf);
    void drawModel(ModelInf* minf);

    // debug
    void DebugBox(int i);
    void DebugBox(const char* str);
    D3DInf* getD3DInformation();

    // camera
    void createCamera(float width, float height, Camera* camera);
    void applyCamera(Camera* camera);

    bool createTexture(unsigned int id, Texture* pTexture);
    void applyTexture(Texture* pTexture);
};


// input
enum struct GAMEPAD_KEYTYPE : int {
    Buttons,
    LTrigger,
    RTrigger,
    ThumbLL,
    ThumbLR,
    ThumbLU,
    ThumbLD,
    ThumbRL,
    ThumbRR,
    ThumbRU,
    ThumbRD,
};

struct KeyInf {
    char state;
    char codeKey;
    char codeKeyboard;
    GAMEPAD_KEYTYPE typeGamepadKey;
    short codeGamepad;
};

class InputManager {
private:
    int numRegistered;
    char statePrev[64];
    KeyInf inf[64];
public:
    InputManager();
    bool addKeycode(char codeKey,char codeKeyboard,GAMEPAD_KEYTYPE typeGamepadKey,short codeGamepad);
    void inspect();
    char getKey(char codeKey);
};

#endif
