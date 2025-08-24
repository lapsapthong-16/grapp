#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "Glu32.lib")

#define WINDOW_TITLE "OpenGL Window"

// ---------- Interaction state ----------
static float rotX = 20.0f;   // rotation around X axis
static float rotY = -30.0f;  // rotation around Y axis
static float rotZ = 0.0f;    // rotation around Z axis
static float zoom = -4.0f;   // camera distance

static bool g_glInited = false;
static GLuint g_brickTex = 0;

// ---------- Simple procedural brick texture ----------
static void createBrickTexture(GLuint* texId, int W = 256, int H = 256)
{
    if (*texId == 0) glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, *texId);

    const unsigned char mortar[3] = { 180, 180, 180 }; // light gray
    const unsigned char brickA[3] = { 178,  73,  50 }; // reddish
    const unsigned char brickB[3] = { 160,  60,  40 }; // darker reddish

    const int brickH = 24;   // pixels per brick row
    const int brickW = 48;   // pixels per brick width
    const int mortarT = 3;   // mortar thickness

    std::vector<unsigned char> img(W * H * 3);

    for (int y = 0; y < H; ++y)
    {
        int row = y / brickH;
        int yIn = y % brickH;
        bool mortarRow = (yIn < mortarT);
        int xOffset = (row % 2) ? brickW / 2 : 0; // stagger every other row

        for (int x = 0; x < W; ++x)
        {
            int xAdj = (x + W - (xOffset % brickW)) % W;
            int xIn = xAdj % brickW;
            bool mortarCol = (xIn < mortarT) || (xIn >= brickW - mortarT);

            const unsigned char* rgb;
            if (mortarRow || mortarCol)
            {
                rgb = mortar;
            }
            else
            {
                // subtle alternating bricks
                bool alt = ((xAdj / brickW) % 2) == 0;
                rgb = alt ? brickA : brickB;
            }

            // light shading based on vertical position for a bit of depth
            float shade = 0.85f + 0.15f * (float)y / (float)H;
            img[(y * W + x) * 3 + 0] = (unsigned char)(rgb[0] * shade);
            img[(y * W + x) * 3 + 1] = (unsigned char)(rgb[1] * shade);
            img[(y * W + x) * 3 + 2] = (unsigned char)(rgb[2] * shade);
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, W, H, GL_RGB, GL_UNSIGNED_BYTE, img.data());
}

// ---------- Render the pyramid ----------
static void drawTexturedPyramid()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_brickTex);

    // A square-base pyramid centered around origin,
    // base on y = 0, apex at y = 1.2 for nicer proportions.
    const float s = 1.0f;     // half size of base (extends [-s, s])
    const float h = 1.2f;     // height

    // Base (two triangles) – map texture to fill the square
    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(1, 0); glVertex3f(s, 0, -s);
    glTexCoord2f(1, 1); glVertex3f(s, 0, s);

    glTexCoord2f(0, 0); glVertex3f(-s, 0, -s);
    glTexCoord2f(1, 1); glVertex3f(s, 0, s);
    glTexCoord2f(0, 1); glVertex3f(-s, 0, s);
    glEnd();

    // Four side faces (triangles)
    glBegin(GL_TRIANGLES);
    // +Z face
    glNormal3f(0, h, s); // crude normal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, 0, s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(s, 0, s);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, h, 0);

    // -Z face
    glNormal3f(0, h, -s);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(s, 0, -s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, 0, -s);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, h, 0);

    // +X face
    glNormal3f(s, h, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(s, 0, s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(s, 0, -s);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, h, 0);

    // -X face
    glNormal3f(-s, h, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, 0, -s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, 0, s);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, h, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// ---------- Template window proc with controls added ----------
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

        // Rotate around all axes
        if (wParam == VK_LEFT)  rotY -= 5.0f;
        if (wParam == VK_RIGHT) rotY += 5.0f;
        if (wParam == VK_UP)    rotX -= 5.0f;
        if (wParam == VK_DOWN)  rotX += 5.0f;
        if (wParam == 'Q')      rotZ -= 5.0f;
        if (wParam == 'E')      rotZ += 5.0f;

        // Zoom
        if (wParam == VK_OEM_PLUS || wParam == '=') zoom += 0.2f;   // closer
        if (wParam == VK_OEM_MINUS || wParam == '-') zoom -= 0.2f;  // farther

        // Reset
        if (wParam == 'R') { rotX = 20.0f; rotY = -30.0f; rotZ = 0.0f; zoom = -4.0f; }
        break;

    default:
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// ---------- Pixel format (same as template) ----------
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

// ---------- Drawing ----------
void display()
{
    if (!g_glInited) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, -0.3f, zoom); // move back; slight drop to center
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    drawTexturedPyramid();
}

// ---------- WinMain ----------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = WINDOW_TITLE;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc)) return false;

    HWND hWnd = CreateWindow(
        WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, wc.hInstance, NULL);

    // ---- Initialize OpenGL context (template) ----
    HDC hdc = GetDC(hWnd);
    if (!initPixelFormat(hdc)) return false;
    HGLRC hglrc = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    // ---- One-time GL setup ----
    g_glInited = true;
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    // basic projection for initial window size
    RECT rc; GetClientRect(hWnd, &rc);
    SendMessage(hWnd, WM_SIZE, 0, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

    // texture
    createBrickTexture(&g_brickTex);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

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

    if (g_brickTex) glDeleteTextures(1, &g_brickTex);
    UnregisterClass(WINDOW_TITLE, wc.hInstance);
    return true;
}
