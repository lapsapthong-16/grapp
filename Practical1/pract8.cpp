#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

// =====================
// Globals / helpers
// =====================
float g_light0[4] = { -2.0f, 5.0f, 3.0f, 1.0f }; // movable with ← →
float g_light1[4] = { 2.0f, 5.0f, -3.0f, 1.0f }; // movable with , .
float g_camYaw = 20.0f;   // just a tiny angle to see depth

// Simple cube (size=1) centered at origin
void drawCube()
{
    glBegin(GL_QUADS);
    // +X
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(0.5f, -0.5f, 0.5f);
    // -X
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    // +Y
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(0.5f, 0.5f, -0.5f);
    // -Y
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    // +Z
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);   glVertex3f(-0.5f, 0.5f, 0.5f);
    // -Z
    glNormal3f(0, 0, -1);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
}

// Ground plane y=0
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

// Build planar shadow matrix for plane P and light L
// plane: (A,B,C,D)  (we use (0,1,0,0) => y=0)
// light: (Lx,Ly,Lz,Lw)  (point light => Lw=1)
void makeShadowMatrix(float out[16], const float L[4], const float P[4])
{
    float dot = P[0] * L[0] + P[1] * L[1] + P[2] * L[2] + P[3] * L[3];

    // Column-major for OpenGL
    out[0] = dot - L[0] * P[0];  out[4] = -L[0] * P[1];  out[8] = -L[0] * P[2];  out[12] = -L[0] * P[3];
    out[1] = -L[1] * P[0];  out[5] = dot - L[1] * P[1];  out[9] = -L[1] * P[2];  out[13] = -L[1] * P[3];
    out[2] = -L[2] * P[0];  out[6] = -L[2] * P[1];  out[10] = dot - L[2] * P[2];  out[14] = -L[2] * P[3];
    out[3] = -L[3] * P[0];  out[7] = -L[3] * P[1];  out[11] = -L[3] * P[2];  out[15] = dot - L[3] * P[3];
}

// Draw object’s shadow onto y=0 for a given light
template <typename DrawFunc>
void drawShadow(const float light[4], DrawFunc drawObject)
{
    const float plane[4] = { 0,1,0,0 }; // y=0
    float M[16];
    makeShadowMatrix(M, light, plane);

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);

    // avoid z-fighting with the floor
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    glMultMatrixf(M);     // squish current world to the plane
    drawObject();         // draw the object geometry (already in world space)
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

// =====================
// Win32 provided code
// =====================
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

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

    if (SetPixelFormat(hdc, n, &pfd)) return true;
    else return false;
}
//--------------------------------------------------------------------

// =====================
// Rendering
// =====================
void display()
{
    // --- input (don’t touch WindowProcedure: just poll here) ---
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)  g_light0[0] -= 0.05f; // Q1
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)  g_light0[0] += 0.05f;
    if (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) g_light1[0] -= 0.05f; // Q2 (second light)
    if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) g_light1[0] += 0.05f;

    // --- one-time GL setup ---
    static bool inited = false;
    if (!inited)
    {
        inited = true;
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);

        GLfloat ambient[] = { 0.15f, 0.15f, 0.15f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glShadeModel(GL_SMOOTH);
    }

    // --- camera/projection each frame ---
    glViewport(0, 0, 800, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // simple perspective
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // camera at (0,3,8) looking at (0,0,0)
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    glRotatef(g_camYaw, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --- lights (positions in world space) ---
    glPushMatrix();
    // (no additional transform; current is world)
    glLightfv(GL_LIGHT0, GL_POSITION, g_light0);
    GLfloat l0diff[] = { 1.0f, 0.9f, 0.7f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l0diff);

    glLightfv(GL_LIGHT1, GL_POSITION, g_light1);
    GLfloat l1diff[] = { 0.7f, 0.8f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l1diff);
    glPopMatrix();

    // --- draw ground ---
    GLfloat groundMatDiff[] = { 0.35f, 0.35f, 0.38f, 1.0f };
    GLfloat groundMatSpec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, groundMatDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, groundMatSpec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 8.0f);

    drawGround();

    // ----------- SHADOWS -----------
    // object A (cube at (-1, 0.5, 0))
    auto drawObjA = []() {
        glPushMatrix();
        glTranslatef(-1.0f, 0.5f, 0.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        drawCube();
        glPopMatrix();
        };
    // object B (second cube at (1.75, 1.0, -0.5))  // Q3
    auto drawObjB = []() {
        glPushMatrix();
        glTranslatef(1.75f, 1.0f, -0.5f);
        glScalef(0.8f, 0.8f, 0.8f);
        drawCube();
        glPopMatrix();
        };

    // Draw shadows for both objects from both lights (Q1+Q2+Q3)
    drawShadow(g_light0, drawObjA);
    drawShadow(g_light0, drawObjB);
    drawShadow(g_light1, drawObjA);
    drawShadow(g_light1, drawObjB);

    // ----------- OBJECTS (lit) -----------
    GLfloat objDiffA[] = { 0.9f, 0.4f, 0.4f, 1.0f };
    GLfloat objSpecA[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objSpecA);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);
    drawObjA();

    GLfloat objDiffB[] = { 0.4f, 0.7f, 0.95f, 1.0f };
    GLfloat objSpecB[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffB);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objSpecB);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 24.0f);
    drawObjB();

    // visualize light bulbs as small unlit points
    glDisable(GL_LIGHTING);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.9f, 0.7f); glVertex3f(g_light0[0], g_light0[1], g_light0[2]);
    glColor3f(0.7f, 0.8f, 1.0f); glVertex3f(g_light1[0], g_light1[1], g_light1[2]);
    glEnd();
    glEnable(GL_LIGHTING);
}
//--------------------------------------------------------------------

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

    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, wc.hInstance, NULL);

    //--------------------------------
    //	Initialize window for OpenGL
    //--------------------------------

    HDC hdc = GetDC(hWnd);

    //	initialize pixel format for the window
    initPixelFormat(hdc);

    //	get an openGL context
    HGLRC hglrc = wglCreateContext(hdc);

    //	make context current
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    //--------------------------------
    //	End initialization
    //--------------------------------

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

    UnregisterClass(WINDOW_TITLE, wc.hInstance);

    return true;
}
//--------------------------------------------------------------------
