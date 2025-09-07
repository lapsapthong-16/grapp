#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float g_light0[4] = { -2.0f, 5.0f, 3.0f, 1.0f };
float g_light1[4] = { 2.0f, 5.0f,-3.0f, 1.0f };
float g_camYaw = 20.0f;

HDC    g_hdc = nullptr;
GLuint g_fontBase = 0;
bool   g_fontReady = false;

void drawCube()
{
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);  glVertex3f(0.5f, -0.5f, 0.5f);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);  glVertex3f(-0.5f, -0.5f, -0.5f);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(0.5f, 0.5f, -0.5f);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);  glVertex3f(0.5f, -0.5f, 0.5f);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(-0.5f, 0.5f, 0.5f);
    glNormal3f(0, 0, -1);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
}

void drawGround()
{
    glNormal3f(0, 1, 0);
    const float S = 8.0f;
    glBegin(GL_QUADS);
    glVertex3f(-S, 0.0f, -S);
    glVertex3f(S, 0.0f, -S);
    glVertex3f(S, 0.0f, S);
    glVertex3f(-S, 0.0f, S);
    glEnd();
}

void makeShadowMatrix(float out[16], const float L[4], const float P[4])
{
    float dot = P[0] * L[0] + P[1] * L[1] + P[2] * L[2] + P[3] * L[3];
    out[0] = dot - L[0] * P[0]; out[4] = -L[0] * P[1]; out[8] = -L[0] * P[2]; out[12] = -L[0] * P[3];
    out[1] = -L[1] * P[0];      out[5] = dot - L[1] * P[1]; out[9] = -L[1] * P[2]; out[13] = -L[1] * P[3];
    out[2] = -L[2] * P[0];      out[6] = -L[2] * P[1]; out[10] = dot - L[2] * P[2]; out[14] = -L[2] * P[3];
    out[3] = -L[3] * P[0];      out[7] = -L[3] * P[1]; out[11] = -L[3] * P[2]; out[15] = dot - L[3] * P[3];
}

static void mulMat4Vec4(const float M[16], const float v[4], float out[4])
{
    out[0] = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
    out[1] = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
    out[2] = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
    out[3] = M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3];
}

static bool invertMatrix4(const float m[16], float invOut[16])
{
    float inv[16];
    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
    inv[3] = -m[1] * m[6] * m[15] + m[1] * m[7] * m[14] + m[5] * m[2] * m[15] - m[5] * m[3] * m[14] - m[13] * m[2] * m[7] + m[13] * m[3] * m[6];
    inv[7] = m[0] * m[6] * m[15] - m[0] * m[7] * m[14] - m[4] * m[2] * m[15] + m[4] * m[3] * m[14] + m[12] * m[2] * m[7] - m[12] * m[3] * m[6];
    inv[11] = -m[0] * m[5] * m[15] + m[0] * m[7] * m[13] + m[4] * m[1] * m[15] - m[4] * m[3] * m[13] - m[12] * m[1] * m[7] + m[12] * m[3] * m[5];
    inv[15] = m[0] * m[5] * m[14] - m[0] * m[6] * m[13] - m[4] * m[1] * m[14] + m[4] * m[2] * m[13] + m[12] * m[1] * m[6] - m[12] * m[2] * m[5];
    float det = m[0] * inv[0] + m[4] * inv[1] + m[8] * inv[2] + m[12] * inv[3];
    if (det == 0.0f) return false;
    det = 1.0f / det;
    for (int i = 0; i < 16; i++) invOut[i] = inv[i] * det;
    return true;
}

static void transformPlaneEye(const float modelView[16], const float planeWorld[4], float planeEye[4])
{
    float invMV[16], invMV_T[16];
    invertMatrix4(modelView, invMV);
    invMV_T[0] = invMV[0];  invMV_T[1] = invMV[4];  invMV_T[2] = invMV[8];  invMV_T[3] = invMV[12];
    invMV_T[4] = invMV[1];  invMV_T[5] = invMV[5];  invMV_T[6] = invMV[9];  invMV_T[7] = invMV[13];
    invMV_T[8] = invMV[2];  invMV_T[9] = invMV[6];  invMV_T[10] = invMV[10]; invMV_T[11] = invMV[14];
    invMV_T[12] = invMV[3]; invMV_T[13] = invMV[7]; invMV_T[14] = invMV[11]; invMV_T[15] = invMV[15];
    mulMat4Vec4(invMV_T, planeWorld, planeEye);
}

template <typename DrawFunc>
void drawShadowEye(const float lightWorld[4], const float modelView[16], DrawFunc drawObject)
{
    float lightEye[4];
    mulMat4Vec4(modelView, lightWorld, lightEye);
    const float planeWorld[4] = { 0,1,0,0 };
    float planeEye[4];
    transformPlaneEye(modelView, planeWorld, planeEye);
    float M[16];
    makeShadowMatrix(M, lightEye, planeEye);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.f, 0.f, 0.f, 0.45f);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glMultMatrixf(M);
    drawObject();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_KEYDOWN: if (wParam == VK_ESCAPE) PostQuitMessage(0); break;
    default: break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.cAlphaBits = 8; pfd.cColorBits = 32; pfd.cDepthBits = 24; pfd.cStencilBits = 0;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iLayerType = PFD_MAIN_PLANE; pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); pfd.nVersion = 1;
    int n = ChoosePixelFormat(hdc, &pfd);
    return SetPixelFormat(hdc, n, &pfd) ? true : false;
}

template <typename DrawFunc>
void drawShadow(const float light[4], DrawFunc drawObject)
{
    const float plane[4] = { 0,1,0,0 };
    float M[16];
    makeShadowMatrix(M, light, plane);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glMultMatrixf(M);
    drawObject();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void setupHudFont(HDC hdc)
{
    if (g_fontReady) return;
    HFONT font = CreateFontA(-16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
    SelectObject(hdc, font);
    g_fontBase = glGenLists(96);
    wglUseFontBitmapsA(hdc, 32, 96, g_fontBase);
    g_fontReady = true;
}

inline void hudText(float x, float y, const char* s)
{
    if (!g_fontReady || !s) return;
    glRasterPos2f(x, y);
    glListBase(g_fontBase - 32); 
    glCallLists((GLsizei)std::strlen(s), GL_UNSIGNED_BYTE, s);
}

void drawHUD()
{
    if (!g_fontReady) return;
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.f, 1.f, 1.f);
    char buf[128];
    std::snprintf(buf, sizeof(buf), "Light0 x = %.2f", g_light0[0]);
    hudText(10.f, 575.f, buf);
    std::snprintf(buf, sizeof(buf), "Light1 x = %.2f", g_light1[0]);
    hudText(10.f, 555.f, buf);
    hudText(10.f, 25.f, "Controls: Left/Right = Light0,  ,/. = Light1");
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void display()
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) g_light0[0] -= 0.05f;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) g_light0[0] += 0.05f;
    if (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) g_light1[0] -= 0.05f;
    if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) g_light1[0] += 0.05f;

    static bool inited = false;
    if (!inited)
    {
        inited = true;
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        GLfloat ambient[] = { 0.15f,0.15f,0.15f,1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glShadeModel(GL_SMOOTH);
    }

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const float pi = 3.1415926535f;
    float yawRad = g_camYaw * (pi / 180.0f);
    float ex = 8.0f * sinf(yawRad);
    float ez = 8.0f * cosf(yawRad);
    gluLookAt(ex, 3.0f, ez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, g_light0);
    GLfloat l0diff[] = { 1.0f,0.9f,0.7f,1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l0diff);
    glLightfv(GL_LIGHT1, GL_POSITION, g_light1);
    GLfloat l1diff[] = { 0.7f,0.8f,1.0f,1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l1diff);
    glPopMatrix();

    GLfloat groundMatDiff[] = { 0.35f,0.35f,0.38f,1.0f };
    GLfloat groundMatSpec[] = { 0.05f,0.05f,0.05f,1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, groundMatDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, groundMatSpec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 8.0f);
    drawGround();

    auto drawObjA = []() {
        glPushMatrix();
        glTranslatef(-1.0f, 0.5f, 0.0f);
        drawCube();
        glPopMatrix();
        };
    auto drawObjB = []() {
        glPushMatrix();
        glTranslatef(1.75f, 0.4f, -0.5f);
        glScalef(0.8f, 0.8f, 0.8f);
        drawCube();
        glPopMatrix();
        };

    drawShadow(g_light0, drawObjA);
    drawShadow(g_light0, drawObjB);
    drawShadow(g_light1, drawObjA);
    drawShadow(g_light1, drawObjB);

    GLfloat objDiffA[] = { 0.9f,0.4f,0.4f,1.0f };
    GLfloat objSpecA[] = { 0.3f,0.3f,0.3f,1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objSpecA);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);
    drawObjA();

    GLfloat objDiffB[] = { 0.4f,0.7f,0.95f,1.0f };
    GLfloat objSpecB[] = { 0.25f,0.25f,0.25f,1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffB);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objSpecB);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 24.0f);
    drawObjB();

    glDisable(GL_LIGHTING);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.9f, 0.7f); glVertex3f(g_light0[0], g_light0[1], g_light0[2]);
    glColor3f(0.7f, 0.8f, 1.0f); glVertex3f(g_light1[0], g_light1[1], g_light1[2]);
    glEnd();
    glEnable(GL_LIGHTING);

    drawHUD();
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

    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, wc.hInstance, NULL);

    HDC hdc = GetDC(hWnd);
    initPixelFormat(hdc);
    HGLRC hglrc = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    g_hdc = hdc;
    setupHudFont(g_hdc);

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

    UnregisterClass(WINDOW_TITLE, wc.hInstance);
    return true;
}
