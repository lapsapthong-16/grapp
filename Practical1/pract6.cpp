#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "Glu32.lib")

#define WINDOW_TITLE "OpenGL Window"

// -------------------- Globals --------------------
enum Shape { SHAPE_SPHERE, SHAPE_PYRAMID };
Shape gShape = SHAPE_SPHERE;

bool  gLightOn = true;
float gAngle = 0.0f;                      // rotation about all axes
float gLightPos[4] = { 0.0f, 0.0f, 2.0f, 1.0f }; // x,y,z,w(=1 positional)

int gWinW = 800, gWinH = 600;               // current window size

// -------------------- Math helpers --------------------
struct Vec3 { float x, y, z; };
static inline Vec3 sub(const Vec3& a, const Vec3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
static inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
static inline Vec3 normalize(const Vec3& v) {
    float m = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (m == 0) return { 0,0,0 };
    return { v.x / m, v.y / m, v.z / m };
}
static inline void emitTriWithNormal(const Vec3& A, const Vec3& B, const Vec3& C) {
    Vec3 n = normalize(cross(sub(B, A), sub(C, A)));
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(A.x, A.y, A.z);
    glVertex3f(B.x, B.y, B.z);
    glVertex3f(C.x, C.y, C.z);
}

// -------------------- Drawing --------------------
void drawSphere()
{
    static GLUquadric* quad = nullptr;
    if (!quad) quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 1.2, 40, 30);
}

void drawPyramid()
{
    const float s = 1.2f;
    const float yTop = 1.2f;
    const float yBase = -1.0f;

    Vec3 apex = { 0.0f, yTop, 0.0f };
    Vec3 bl = { -s,    yBase,  s }; // base left-front  (-x, -y, +z)
    Vec3 br = { s,    yBase,  s };
    Vec3 brb = { s,    yBase, -s };
    Vec3 blb = { -s,    yBase, -s };

    // Side faces (CCW when viewed from outside)
    glBegin(GL_TRIANGLES);
    emitTriWithNormal(apex, bl, br); // front
    emitTriWithNormal(apex, br, brb); // right
    emitTriWithNormal(apex, brb, blb); // back
    emitTriWithNormal(apex, blb, bl); // left
    glEnd();

    // Base (two triangles, facing downward)
    glBegin(GL_TRIANGLES);
    emitTriWithNormal(bl, br, brb);
    emitTriWithNormal(bl, brb, blb);
    glEnd();
}

// Light position marker (tiny sphere)
void drawLightMarker()
{
    glPushMatrix();
    glTranslatef(gLightPos[0], gLightPos[1], gLightPos[2]);
    glDisable(GL_LIGHTING);
    static GLUquadric* q = nullptr; if (!q) q = gluNewQuadric();
    glColor3f(1.f, 0.f, 0.f);
    gluSphere(q, 0.06, 12, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// -------------------- Windows / Input --------------------
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
    {
        gWinW = LOWORD(lParam);
        gWinH = HIWORD(lParam);
        if (gWinH == 0) gWinH = 1;
        glViewport(0, 0, gWinW, gWinH);
    }
    break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE: PostQuitMessage(0); break;

            // Light position controls
        case 'W': gLightPos[1] += 0.2f; break; // up
        case 'S': gLightPos[1] -= 0.2f; break; // down
        case 'A': gLightPos[0] -= 0.2f; break; // left
        case 'D': gLightPos[0] += 0.2f; break; // right
        case 'E': gLightPos[2] += 0.2f; break; // near (toward camera)
        case 'Q': gLightPos[2] -= 0.2f; break; // far  (away)

            // Rotation about all axes
        case VK_UP:   gAngle += 5.0f;  break; // clockwise-ish
        case VK_DOWN: gAngle -= 5.0f;  break; // anti-clockwise

            // Toggle light
        case VK_SPACE: gLightOn = !gLightOn; break;

            // Switch object
        case 'O': gShape = SHAPE_SPHERE;  break;
        case 'P': gShape = SHAPE_PYRAMID; break;
        }
    }
    break;

    default: break;
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
    return SetPixelFormat(hdc, n, &pfd) ? true : false;
}

// One-time GL state
void setupOnce()
{
    static bool done = false;
    if (done) return;
    done = true;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);           // optional polish
    glCullFace(GL_BACK);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);           // keep normals unit length after transforms

    // Scene/global ambient (very subtle so red diffuse dominates)
    GLfloat globalAmbient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // Two-sided lighting (nice while object rotates)
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    // Material: neutral so red diffuse reads clearly
    GLfloat matAmbient[] = { 0.18f, 0.18f, 0.18f, 1.0f };
    GLfloat matDiffuse[] = { 0.85f, 0.85f, 0.85f, 1.0f };
    GLfloat matSpecular[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    GLfloat shininess = 24.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Red diffuse light (LIGHT0) with a little specular + attenuation
    GLfloat lightDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.05f, 0.0f, 0.0f, 1.0f };
    GLfloat lightSpecular[] = { 0.25f, 0.10f, 0.10f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Initial viewport matches initial window size
    glViewport(0, 0, gWinW, gWinH);
}

//--------------------------------------------------------------------
void display()
{
    setupOnce();

    // Projection (use current aspect)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (gWinH == 0) ? 1.0 : (double)gWinW / (double)gWinH;
    gluPerspective(60.0, aspect, 0.1, 100.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);   // move scene away from camera

    // Lighting on/off and position
    if (gLightOn) { glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); }
    else { glDisable(GL_LIGHT0);  glDisable(GL_LIGHTING); }

    glLightfv(GL_LIGHT0, GL_POSITION, gLightPos); // evaluated in current modelview

    // Show a small marker where the light is
    drawLightMarker();

    // Apply rotation about all axes
    glRotatef(gAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(gAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(gAngle, 0.0f, 0.0f, 1.0f);

    // Draw selected object
    if (gShape == SHAPE_SPHERE) drawSphere();
    else                        drawPyramid();
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
        CW_USEDEFAULT, CW_USEDEFAULT, gWinW, gWinH,
        NULL, NULL, wc.hInstance, NULL);

    // Initialize window for OpenGL
    HDC hdc = GetDC(hWnd);
    if (!initPixelFormat(hdc)) return false;
    HGLRC hglrc = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, hglrc)) return false;

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
