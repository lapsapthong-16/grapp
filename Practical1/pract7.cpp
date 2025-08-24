// ===================== Common Includes / Setup (Shared by Q1 & Q2) =====================
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include <cmath>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "Glu32.lib")

#define WINDOW_TITLE "OpenGL Window (Q1 + Q2)"

// -------- Interaction state --------
static float rotX = 20.0f;
static float rotY = -30.0f;
static float rotZ = 0.0f;
static float zoom = -4.0f;

static bool  g_glInited = false;

// App mode: which question we’re showing
enum class AppMode { Q1_PYRAMID, Q2_CUBE };
static AppMode g_mode = AppMode::Q1_PYRAMID;

// -------- Textures --------
static GLuint g_texBrick = 0; // used by Q1 and as an option in Q2
static GLuint g_texWood = 0; // Q2
static GLuint g_texMetal = 0; // Q2

enum class CubeTex { WOOD, METAL, BRICK };
static CubeTex g_cubeTex = CubeTex::WOOD;

// ----------------- Utility: create an RGB texture from raw pixels -----------------
static void uploadTexture(GLuint* texId, int W, int H, const std::vector<unsigned char>& imgRGB)
{
    if (*texId == 0) glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, *texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, imgRGB.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, W, H, GL_RGB, GL_UNSIGNED_BYTE, imgRGB.data());
}

// ================================ Q1: Pyramid + Brick ================================
static void createBrickTexture(GLuint* texId, int W = 256, int H = 256)
{
    const unsigned char mortar[3] = { 180, 180, 180 };
    const unsigned char brickA[3] = { 178,  73,  50 };
    const unsigned char brickB[3] = { 160,  60,  40 };

    const int brickH = 24;
    const int brickW = 48;
    const int mortarT = 3;

    std::vector<unsigned char> img(W * H * 3);

    for (int y = 0; y < H; ++y)
    {
        int row = y / brickH;
        int yIn = y % brickH;
        bool mortarRow = (yIn < mortarT);
        int xOffset = (row % 2) ? brickW / 2 : 0;

        for (int x = 0; x < W; ++x)
        {
            int xAdj = (x + W - (xOffset % brickW)) % W;
            int xIn = xAdj % brickW;
            bool mortarCol = (xIn < mortarT) || (xIn >= brickW - mortarT);

            const unsigned char* rgb;
            if (mortarRow || mortarCol) rgb = mortar;
            else                        rgb = ((xAdj / brickW) % 2) ? brickA : brickB;

            float shade = 0.85f + 0.15f * (float)y / (float)H;
            img[(y * W + x) * 3 + 0] = (unsigned char)(rgb[0] * shade);
            img[(y * W + x) * 3 + 1] = (unsigned char)(rgb[1] * shade);
            img[(y * W + x) * 3 + 2] = (unsigned char)(rgb[2] * shade);
        }
    }
    uploadTexture(texId, W, H, img);
}

static void drawTexturedPyramid()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_texBrick);

    const float s = 1.0f;
    const float h = 1.2f;

    // Base
    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(1, 0); glVertex3f(s, 0, -s);
    glTexCoord2f(1, 1); glVertex3f(s, 0, s);

    glTexCoord2f(0, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(1, 1); glVertex3f(s, 0, s);
    glTexCoord2f(0, 1); glVertex3f(-s, 0, s);
    glEnd();

    // Sides
    glBegin(GL_TRIANGLES);
    // +Z
    glNormal3f(0, h, s);
    glTexCoord2f(0, 0); glVertex3f(-s, 0, s);
    glTexCoord2f(1, 0); glVertex3f(s, 0, s);
    glTexCoord2f(0.5f, 1); glVertex3f(0, h, 0);

    // -Z
    glNormal3f(0, h, -s);
    glTexCoord2f(0, 0); glVertex3f(s, 0, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(0.5f, 1); glVertex3f(0, h, 0);

    // +X
    glNormal3f(s, h, 0);
    glTexCoord2f(0, 0); glVertex3f(s, 0, s);
    glTexCoord2f(1, 0); glVertex3f(s, 0, -s);
    glTexCoord2f(0.5f, 1); glVertex3f(0, h, 0);

    // -X
    glNormal3f(-s, h, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, 0, s);
    glTexCoord2f(0.5f, 1); glVertex3f(0, h, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// ================================ Q2: Cube + Switchable Textures ================================
// Very lightweight procedural textures so no image files are needed.

// --- Wood: vertical planks with darker seams and subtle grain ---
static void createWoodTexture(GLuint* texId, int W = 256, int H = 256)
{
    std::vector<unsigned char> img(W * H * 3);
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            // plank seams every ~48 px with 3 px dark gap
            int seam = (x % 48);
            bool isGap = (seam < 3);

            // base color + sine-based grain
            float grain = 0.5f + 0.5f * std::sin((x * 0.10f) + std::sin(y * 0.06f) * 0.8f);
            float r = 105.0f + 60.0f * grain;
            float g = 70.0f + 40.0f * grain;
            float b = 40.0f + 25.0f * grain;

            if (isGap) { r *= 0.35f; g *= 0.35f; b *= 0.35f; }

            img[(y * W + x) * 3 + 0] = (unsigned char)r;
            img[(y * W + x) * 3 + 1] = (unsigned char)g;
            img[(y * W + x) * 3 + 2] = (unsigned char)b;
        }
    }
    uploadTexture(texId, W, H, img);
}

// --- Metal: brushed look using vertical streaks + cool tone ---
static void createMetalTexture(GLuint* texId, int W = 256, int H = 256)
{
    std::vector<unsigned char> img(W * H * 3);
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            float base = 190.0f + 30.0f * std::sin(y * 0.25f);
            float brush = 25.0f * std::sin(x * 0.6f) + 20.0f * std::sin((x + y) * 0.15f);
            float v = std::fmax(120.0f, std::fmin(235.0f, base + brush));
            // bluish steel
            unsigned char r = (unsigned char)(v * 0.90f);
            unsigned char g = (unsigned char)(v * 0.95f);
            unsigned char b = (unsigned char)(v);

            img[(y * W + x) * 3 + 0] = r;
            img[(y * W + x) * 3 + 1] = g;
            img[(y * W + x) * 3 + 2] = b;
        }
    }
    uploadTexture(texId, W, H, img);
}

static GLuint currentCubeTexture()
{
    switch (g_cubeTex)
    {
    case CubeTex::WOOD:  return g_texWood;
    case CubeTex::METAL: return g_texMetal;
    default:             return g_texBrick;
    }
}

static void drawTexturedCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, currentCubeTexture());

    const float s = 1.0f;

    glBegin(GL_QUADS);
    // +Z (front)
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, s);

    // -Z (back)
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, -s);

    // +X (right)
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, s);

    // -X (left)
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);

    // +Y (top)
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, s, s);
    glTexCoord2f(1, 0); glVertex3f(s, s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);

    // -Y (bottom)
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(s, -s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, -s, s);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// ======================== Template plumbing + input handling ========================
bool initPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.cAlphaBits = 8;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 0;

    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    int n = ChoosePixelFormat(hdc, &pfd);
    return SetPixelFormat(hdc, n, &pfd) == TRUE;
}

static void resetView() { rotX = 20.0f; rotY = -30.0f; rotZ = 0.0f; zoom = -4.0f; }

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        if (g_glInited)
        {
            int w = LOWORD(lParam), h = HIWORD(lParam);
            if (h == 0) h = 1;
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
            glMatrixMode(GL_MODELVIEW);
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) PostQuitMessage(0);

        // rotate all axes
        if (wParam == VK_LEFT)  rotY -= 5.0f;
        if (wParam == VK_RIGHT) rotY += 5.0f;
        if (wParam == VK_UP)    rotX -= 5.0f;
        if (wParam == VK_DOWN)  rotX += 5.0f;
        if (wParam == 'Q')      rotZ -= 5.0f;
        if (wParam == 'E')      rotZ += 5.0f;

        // zoom
        if (wParam == VK_OEM_PLUS || wParam == '=') zoom += 0.2f;
        if (wParam == VK_OEM_MINUS || wParam == '-') zoom -= 0.2f;

        // reset
        if (wParam == 'R') resetView();

        // switch model (clear distinction Q1 vs Q2)
        if (wParam == '1') { g_mode = AppMode::Q1_PYRAMID; resetView(); }
        if (wParam == '2') { g_mode = AppMode::Q2_CUBE;    resetView(); }

        // Q2: switch cube texture
        if (wParam == 'W') g_cubeTex = CubeTex::WOOD;
        if (wParam == 'M') g_cubeTex = CubeTex::METAL;
        if (wParam == 'B') g_cubeTex = CubeTex::BRICK;
        if (wParam == 'T') // cycle
        {
            g_cubeTex = (g_cubeTex == CubeTex::WOOD) ? CubeTex::METAL :
                (g_cubeTex == CubeTex::METAL) ? CubeTex::BRICK : CubeTex::WOOD;
        }
        break;

    default: break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void display()
{
    if (!g_glInited) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -0.1f, zoom);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    if (g_mode == AppMode::Q1_PYRAMID)      drawTexturedPyramid(); // ===== Q1 =====
    else                                     drawTexturedCube();    // ===== Q2 =====
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSEX wc; ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = WINDOW_TITLE;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc)) return false;

    HWND hWnd = CreateWindow(
        WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 650, NULL, NULL, wc.hInstance, NULL);

    HDC hdc = GetDC(hWnd);
    if (!initPixelFormat(hdc)) return false;
    HGLRC hglrc = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    // GL init
    g_glInited = true;
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    // set projection once
    RECT rc; GetClientRect(hWnd, &rc);
    SendMessage(hWnd, WM_SIZE, 0, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

    // Build textures for both questions
    createBrickTexture(&g_texBrick); // Q1 + Q2
    createWoodTexture(&g_texWood);  // Q2
    createMetalTexture(&g_texMetal); // Q2

    ShowWindow(hWnd, nCmdShow);

    MSG msg; ZeroMemory(&msg, sizeof(msg));
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        display();
        SwapBuffers(hdc);
    }

    if (g_texBrick) glDeleteTextures(1, &g_texBrick);
    if (g_texWood)  glDeleteTextures(1, &g_texWood);
    if (g_texMetal) glDeleteTextures(1, &g_texMetal);

    UnregisterClass(WINDOW_TITLE, wc.hInstance);
    return true;
}
