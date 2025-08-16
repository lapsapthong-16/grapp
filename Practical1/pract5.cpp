
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

static bool  gPerspective = true;
static bool  gSplitViewport = false;

static float gYaw = -25.0f;     // orbit yaw (deg)
static float gPitch = 20.0f;    // orbit pitch (deg)
static float gDist = 42.0f;     // camera distance

static float gBascule = 0.0f;   // 0..70 deg
static bool  gAnim = true;      // animate by default
static float gBasculeDir = +1.0f;

static RECT  gClient = { 0,0,800,600 };

// mouse interaction
static bool  gLDragging = false;
static POINT gLastMouse = { 0,0 };

static inline float deg2rad(float a) { return a * 3.1415926535f / 180.0f; }

void setPerspective(float fovY_deg, float aspect, float zNear, float zFar)
{
    float top = zNear * tanf(deg2rad(fovY_deg * 0.5f));
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, zNear, zFar);
}

void drawBox(float w, float h, float d)
{
    float x = w * 0.5f, y = h * 0.5f, z = d * 0.5f;
    glBegin(GL_QUADS);
    glVertex3f(x, -y, -z); glVertex3f(x, y, -z); glVertex3f(x, y, z); glVertex3f(x, -y, z);
    glVertex3f(-x, -y, z); glVertex3f(-x, y, z); glVertex3f(-x, y, -z); glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z); glVertex3f(-x, y, z); glVertex3f(x, y, z); glVertex3f(x, y, -z);
    glVertex3f(-x, -y, z); glVertex3f(-x, -y, -z); glVertex3f(x, -y, -z); glVertex3f(x, -y, z);
    glVertex3f(-x, -y, z); glVertex3f(x, -y, z); glVertex3f(x, y, z); glVertex3f(-x, y, z);
    glVertex3f(x, -y, -z); glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z); glVertex3f(x, y, -z);
    glEnd();
}

// XZ arch strip (for tower openings)
void drawArch(float radius, float thickness, float span, int steps, float depth)
{
    float z0 = -depth * 0.5f, z1 = depth * 0.5f;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0;i <= steps;i++) {
        float t = (float)i / steps;
        float x = -span * 0.5f + t * span;
        float a = acosf(fminf(1.0f, fmaxf(-1.0f, x / radius)));
        float yOuter = radius * sinf(a);
        float yInner = yOuter - thickness;
        glVertex3f(x, yOuter, z0); glVertex3f(x, yInner, z0);
        glVertex3f(x, yOuter, z1); glVertex3f(x, yInner, z1);
    }
    glEnd();
}

void drawCable(float yBase, float x0, float x1, float sag, int steps, float z)
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0;i <= steps;i++) {
        float t = (float)i / steps;
        float x = x0 + t * (x1 - x0);
        float m = (t - 0.5f);
        float y = yBase - sag * (1.0f - 4.0f * m * m);
        glVertex3f(x, y, z);
    }
    glEnd();
}

void drawTower()
{
    glColor3f(0.75f, 0.72f, 0.65f); drawBox(6.0f, 24.0f, 8.0f);
    glPushMatrix(); glTranslatef(0, 12, 0); glColor3f(0.70f, 0.68f, 0.60f); drawBox(7.0f, 3.0f, 9.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 15.5f, 0); glColor3f(0.55f, 0.52f, 0.45f); drawBox(5.0f, 2.0f, 7.0f); glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    glColor3f(0.40f, 0.38f, 0.35f);
    glPushMatrix(); glTranslatef(0.0f, -6.0f, 4.01f); drawArch(5.0f, 1.2f, 4.0f, 24, 0.2f); glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

void drawRoadFixed(float length, float width, float thick)
{
    glColor3f(0.30f, 0.33f, 0.37f); drawBox(length, thick, width);
    glColor3f(0.20f, 0.55f, 0.75f);
    glPushMatrix(); glTranslatef(0, thick * 0.6f, width * 0.55f); drawBox(length, 0.6f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, thick * 0.6f, -width * 0.55f); drawBox(length, 0.6f, 0.2f); glPopMatrix();
}

void drawBasculeLeaf(bool leftSide, float angleDeg,
    float hingeX, float length, float width, float thick)
{
    float dir = leftSide ? -1.0f : +1.0f;

    glPushMatrix();
    glTranslatef(hingeX, 0.0f, 0.0f);          // move to hinge position
    glRotatef(-dir * angleDeg, 0.0f, 0.0f, 1.0f); // rotate around hinge
    glTranslatef(-dir * (length * 0.5f), 0.0f, 0.0f); // place box so its inner end sits at the hinge

    glColor3f(0.32f, 0.35f, 0.39f);
    drawBox(length, thick, width);

    // railings
    glColor3f(0.18f, 0.50f, 0.70f);
    glPushMatrix(); glTranslatef(0.0f, thick * 0.6f, width * 0.55f); drawBox(length, 0.6f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, thick * 0.6f, -width * 0.55f); drawBox(length, 0.6f, 0.2f); glPopMatrix();

    glPopMatrix();
}

void drawBridge()
{
    glColor3f(0.02f, 0.10f, 0.20f);
    glPushMatrix(); glTranslatef(0, -10, 0); drawBox(140.0f, 0.2f, 80.0f); glPopMatrix();

    glPushMatrix(); glTranslatef(-18.0f, 2.0f, 0.0f); drawTower(); glPopMatrix();
    glPushMatrix(); glTranslatef(18.0f, 2.0f, 0.0f); drawTower(); glPopMatrix();

    glPushMatrix(); glTranslatef(0, 14.5f, 0);
    glColor3f(0.70f, 0.74f, 0.78f); drawBox(28.0f, 1.5f, 6.0f);
    glColor3f(0.20f, 0.55f, 0.75f); drawBox(28.5f, 0.3f, 6.6f);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix(); // -18..-6
    glPushMatrix(); glTranslatef(12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix(); //  +6..+18

    glPushMatrix(); glTranslatef(0, -1, 0);
    drawBasculeLeaf(true, gBascule, -6.0f, 6.0f, 6.0f, 1.0f);  // left leaf, hinge at x = -6
    drawBasculeLeaf(false, gBascule, 6.0f, 6.0f, 6.0f, 1.0f);  // right leaf, hinge at x = +6
    glPopMatrix();

    glColor3f(0.15f, 0.65f, 0.85f);
    drawCable(10.0f, -18.0f, 18.0f, 5.0f, 40, 3.2f);
    drawCable(10.0f, -18.0f, 18.0f, 5.0f, 40, -3.2f);
}

void applyCameraAndProjection(int vpX, int vpY, int vpW, int vpH, bool perspective)
{
    glViewport(vpX, vpY, vpW, vpH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (vpH == 0) ? 1.0f : (float)vpW / (float)vpH;

    if (perspective) setPerspective(45.0f, aspect, 0.5f, 500.0f);
    else             glOrtho(-30.0f * aspect, 30.0f * aspect, -20.0f, 20.0f, -500.0f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -gDist);
    glRotatef(gPitch, 1, 0, 0);
    glRotatef(gYaw, 0, 1, 0);
    glTranslatef(0, -3, 0);
}


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_SIZE:
        gClient.right = LOWORD(lParam);
        gClient.bottom = HIWORD(lParam);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_LBUTTONDOWN:
        gLDragging = true;
        gLastMouse.x = LOWORD(lParam);
        gLastMouse.y = HIWORD(lParam);
        SetCapture(hWnd);
        return 0;

    case WM_LBUTTONUP:
        gLDragging = false;
        ReleaseCapture();
        return 0;

    case WM_MOUSEMOVE:
        if (gLDragging) {
            int x = LOWORD(lParam), y = HIWORD(lParam);
            int dx = x - gLastMouse.x, dy = y - gLastMouse.y;
            gYaw += dx * 0.4f;
            gPitch += dy * 0.4f;
            if (gPitch > 85.0f) gPitch = 85.0f;
            if (gPitch < -85.0f) gPitch = -85.0f;
            gLastMouse.x = x; gLastMouse.y = y;
        }
        return 0;

    case WM_MOUSEWHEEL:
        gDist += (GET_WHEEL_DELTA_WPARAM(wParam) > 0) ? -2.0f : 2.0f;
        if (gDist < 8.0f) gDist = 8.0f;
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE: PostQuitMessage(0); break;
        case 'P': gPerspective = true; break;
        case 'O': gPerspective = false; break;
        case 'V': gSplitViewport = !gSplitViewport; break;

            // keyboard camera
        case 'A': gYaw -= 3.0f; break;
        case 'D': gYaw += 3.0f; break;
        case 'Q': gPitch += 3.0f; if (gPitch > 85) gPitch = 85; break;
        case 'E': gPitch -= 3.0f; if (gPitch < -85) gPitch = -85; break;
        case 'W': gDist -= 2.0f; if (gDist < 8.0f) gDist = 8.0f; break;
        case 'S': gDist += 2.0f; break;

            // bascule animation / manual
        case ' ': gAnim = !gAnim; break;
        case '[': gBascule -= 3.0f; if (gBascule < 0.0f) gBascule = 0.0f; break;
        case ']': gBascule += 3.0f; if (gBascule > 70.0f) gBascule = 70.0f; break;

        case 'R':
            gPerspective = true; gSplitViewport = false;
            gYaw = -25.0f; gPitch = 20.0f; gDist = 42.0f;
            gBascule = 0.0f; gAnim = true; gBasculeDir = +1.0f;
            break;
        }
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
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

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
    // animate bascules
    if (gAnim) {
        gBascule += gBasculeDir * 0.8f; // speed
        if (gBascule > 70.0f) { gBascule = 70.0f; gBasculeDir = -1.0f; }
        if (gBascule < 0.0f) { gBascule = 0.0f; gBasculeDir = +1.0f; }
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.02f, 0.02f, 0.03f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int W = gClient.right, H = gClient.bottom;
    if (W <= 0 || H <= 0) { W = 800; H = 600; }

    if (!gSplitViewport) {
        applyCameraAndProjection(0, 0, W, H, gPerspective);
        drawBridge();
    }
    else {
        applyCameraAndProjection(0, 0, W / 2, H, true);
        drawBridge();
        applyCameraAndProjection(W / 2, 0, W - W / 2, H, false);
        drawBridge();
    }

    glFlush();
}
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