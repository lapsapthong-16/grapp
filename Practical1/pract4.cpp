
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#include <GL/glu.h>
#pragma comment(lib, "Glu32.lib")

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;

int currentMode = 1;            // 1 = Pyramid, 2 = Robot Arm
float armRotation = 0.0f;       // Whole arm rotation (LEFT/RIGHT)
float lowerArmAngle = 0.0f;     // Lower arm angle (UP/DOWN)


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

			// Switch between modes
		case '1':
			currentMode = 1;
			break;
		case '2':
			currentMode = 2;
			break;

			// Pyramid rotation keys (only in mode 1)
		case 'X':
			if (currentMode == 1) rotX += 5.0f;
			break;
		case 'Y':
			if (currentMode == 1) rotY += 5.0f;
			break;
		case 'Z':
			if (currentMode == 1) rotZ += 5.0f;
			break;

			// Robot arm controls (only in mode 2)
		case VK_LEFT:
			if (currentMode == 2) armRotation -= 5.0f;
			break;
		case VK_RIGHT:
			if (currentMode == 2) armRotation += 5.0f;
			break;
		case VK_UP:
			if (currentMode == 2) lowerArmAngle -= 5.0f;
			break;
		case VK_DOWN:
			if (currentMode == 2) lowerArmAngle += 5.0f;
			break;
		case VK_SPACE:
			if (currentMode == 2) {
				armRotation = 0.0f;
				lowerArmAngle = 0.0f;
			}
			break;
		}
		return 0;

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

void q1()
{
	glBegin(GL_LINE_LOOP); // Base square
	glVertex3f(-0.5f, 0.0f, -0.5f);
	glVertex3f(0.5f, 0.0f, -0.5f);
	glVertex3f(0.5f, 0.0f, 0.5f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glEnd();

	glBegin(GL_LINES); // 4 triangle sides
	glVertex3f(-0.5f, 0.0f, -0.5f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, -0.5f);  glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.5f);   glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);  glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
}

void drawWireCube()
{
	glBegin(GL_LINE_LOOP); // Front face
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP); // Back face
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_LINES); // Connect faces
	glVertex3f(-0.5, -0.5, 0.5); glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5); glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5); glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5); glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
}


void q2()
{
	// Draw base arm
	glPushMatrix();
	glRotatef(armRotation, 0, 1, 0);  // Rotate whole arm
	glTranslatef(-1.1f, 0, 0);        // Move to left for drawing first cube

	// Upper arm
	glPushMatrix();
	glScalef(2.0f, 0.7f, 0.7f);
	// Stretch to make rectangular "cube"
	drawWireCube();
	glPopMatrix();

	// Lower arm (child)
	glTranslatef(1.1f, 0, 0);         // Move pivot to joint position
	glRotatef(lowerArmAngle, 0, 0, 1); // Lower arm rotation
	glTranslatef(1.1f, 0, 0);         // Position lower arm

	glPushMatrix();
	glScalef(2.0f, 0.7f, 0.7f);
	// Same as upper arm
	drawWireCube();
	glPopMatrix();

	glPopMatrix();
}


void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);

	if (currentMode == 1)
	{
		// Pyramid
		glRotatef(rotX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
		glColor3f(1, 1, 1);
		q1();
	}
	else if (currentMode == 2)
	{
		glColor3f(1, 1, 1);
		q2();
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