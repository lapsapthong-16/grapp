#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "Glu32.lib")

#define WINDOW_TITLE "OpenGL Window"

// -------------------- Globals & Helpers --------------------
enum Shape { SHAPE_SPHERE, SHAPE_PYRAMID };
Shape gShape = SHAPE_SPHERE;

bool  gLightOn = true;
float gAngle = 0.0f;              // rotation about all axes
float gLightPos[4] = { 0.0f, 0.0f, 2.0f, 1.0f }; // x,y,z,w(=1 positional)

void drawSphere()
{
    static GLUquadric* quad = nullptr;
    if (!quad) quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 1.2, 40, 30);
}

void drawPyramid()
{
    // A 4-sided pyramid centered at origin, base on y = -1, apex at y = 1.2
    glBegin(GL_TRIANGLES);
    // Front face (normal approx)
    glNormal3f(0.0f, 0.6f, 0.8f);
    glVertex3f(0.0f, 1.2f, 0.0f); // apex
    glVertex3f(-1.2f, -1.0f, 1.2f);
    glVertex3f(1.2f, -1.0f, 1.2f);

    // Right face
    glNormal3f(0.8f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.2f, 0.0f);
    glVertex3f(1.2f, -1.0f, 1.2f);
    glVertex3f(1.2f, -1.0f, -1.2f);

    // Back face
    glNormal3f(0.0f, 0.6f, -0.8f);
    glVertex3f(0.0f, 1.2f, 0.0f);
    glVertex3f(1.2f, -1.0f, -1.2f);
    glVertex3f(-1.2f, -1.0f, -1.2f);

    // Left face
    glNormal3f(-0.8f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.2f, 0.0f);
    glVertex3f(-1.2f, -1.0f, -1.2f);
    glVertex3f(-1.2f, -1.0f, 1.2f);
    glEnd();

    // Base (two triangles, facing downward)
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.2f, -1.0f, 1.2f);
    glVertex3f(1.2f, -1.0f, 1.2f);
    glVertex3f(1.2f, -1.0f, -1.2f);

    glVertex3f(-1.2f, -1.0f, 1.2f);
    glVertex3f(1.2f, -1.0f, -1.2f);
    glVertex3f(-1.2f, -1.0f, -1.2f);
    glEnd();
}

// -------------------- Windows / Input --------------------
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
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
//--------------------------------------------------------------------

void setupOnce()
{
    static bool done = false;
    if (done) return;
    done = true;

    glEnable(GL_DEPTH_TEST);

    // Material: neutral grey/white so red diffuse light shows clearly
    GLfloat matDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat shininess = 16.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Red diffuse light (LIGHT0)
    GLfloat lightDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.05f, 0.0f, 0.0f, 1.0f };
    GLfloat lightSpecular[] = { 0.2f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void display()
{
    setupOnce();

    // Basic fixed viewport/projection (800x600)
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ModelView setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera at origin looking down -Z, move scene away a bit
    glTranslatef(0.0f, 0.0f, -6.0f);

    // Lighting on/off & position
    if (gLightOn) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
    glLightfv(GL_LIGHT0, GL_POSITION, gLightPos); // uses current modelview

    // Draw a small marker for light position (emissive so it's visible)
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glVertex3f(gLightPos[0], gLightPos[1], gLightPos[2]);
    glEnd();
    glPopAttrib();

    // Apply rotation about all axes
    glRotatef(gAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(gAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(gAngle, 0.0f, 0.0f, 1.0f);

    // Draw selected shape
    if (gShape == SHAPE_SPHERE) {
        drawSphere();
    }
    else {
        drawPyramid();
    }
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
