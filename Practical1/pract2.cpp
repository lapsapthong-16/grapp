
#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 2"

// global variables
int qNo = 0; // Question number
float objPosX = 0.0f; // Object position X
float objPosY = 0.0f; // Object position Y

float objColorR = 1.0f; // Initial color white (r,g,b)
float objColorG = 1.0f;
float objColorB = 1.0f;


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

		case VK_LEFT:
			objPosX -= 0.1f; // Move left
			break;

		case VK_RIGHT:
			objPosX += 0.1f; // Move right
			break;

		case VK_UP:
			objPosY += 0.1f; // Move up
			break;

		case VK_DOWN:
			objPosY -= 0.1f; // Move down
			break;

		case 'R':
			objColorR = 1.0f; objColorG = 0.0f; objColorB = 0.0f; // Red
			break;

		case 'G':
			objColorR = 0.0f; objColorG = 1.0f; objColorB = 0.0f; // Green
			break;

		case 'B':
			objColorR = 0.0f; objColorG = 0.0f; objColorB = 1.0f; // Blue
			break;

		case VK_SPACE:
			objPosX = 0.0f; objPosY = 0.0f; // Reset position
			objColorR = 1.0f; objColorG = 1.0f; objColorB = 1.0f; // Reset color white
			break;

		case '0':
			qNo = 0;
			break;
		case '1':
			qNo = 1;
			break;
		case '2':
			qNo = 2;
			break;
		case '3':
			qNo = 3;
			break;
		case '4':
			qNo = 4;
			break;
		case '5':
			qNo = 5;
			break;
		case '6':
			qNo = 6;
			break;
		case '7':
			qNo = 7;
			break;
		}
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

void demo() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Background black
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); // Reset matrix
	glTranslatef(objPosX, objPosY, 0.0f); // Apply position

	glColor3f(objColorR, objColorG, objColorB); // Set color

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glEnd();
}

void translateDemo1() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color and depth buffers

	glTranslatef(0.0001f, 0.0, 0.0); // Move the origin to the right
	glBegin(GL_TRIANGLES); // Start drawing triangles
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd(); // End drawing triangles
}

void translateDemo2() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color and depth buffers

	glLoadIdentity(); // Load the identity matrix
	glTranslatef(0.4, 0.0, 0.0); // Move the origin to the right
	glBegin(GL_TRIANGLES); // Start drawing triangles
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd(); // End drawing triangles
}

void rotateDemo1() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color and depth buffers
	glRotatef(0.01, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES); // Start drawing triangles
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

void rotateDemo2() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color and depth buffers

	glLoadIdentity(); // Load the identity matrix
	glRotatef(90, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES); // Start drawing triangles
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

#include <math.h>  // For sin and cos

void q2() {
	static float colorPhase = 0.0f;
	colorPhase += 0.01f;

	if (colorPhase > 2 * 3.14159f)
		colorPhase -= 2 * 3.14159f;

	float r = (sinf(colorPhase) + 1.0f) / 2.0f;
	float g = (sinf(colorPhase + 2.0f) + 1.0f) / 2.0f;
	float b = (sinf(colorPhase + 4.0f) + 1.0f) / 2.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(r, g, b);

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(0.0f, 0.0f);


	const int points = 10;          // 5 points * 2 (outer + inner)
	const float outerRadius = 0.5f;
	const float innerRadius = 0.2f;

	for (int i = 0; i <= points; ++i) {
		float angle = i * (2.0f * 3.14159f) / points - 3.14159f / 2; // start pointing up

		float radius = (i % 2 == 0) ? outerRadius : innerRadius;

		float x = cosf(angle) * radius;
		float y = sinf(angle) * radius;

		glVertex2f(x, y);
	}

	glEnd();
}

void q3() {
	static float angle = 0.0f;
	static float radius = 0.5f;
	angle += 0.01f; // Controls speed & direction (positive = anticlockwise)

	float x = cosf(angle) * radius;
	float y = sinf(angle) * radius;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // Red point
	glPointSize(10.0f); // Bigger point

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void q4() {
	static float size = 0.05f;
	if (size < 1.0f) size += 0.01f;

	float halfSize = size / 2.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // Red box

	glBegin(GL_QUADS);
	glVertex2f(-halfSize, -halfSize);
	glVertex2f(halfSize, -halfSize);
	glVertex2f(halfSize, halfSize);
	glVertex2f(-halfSize, halfSize);
	glEnd();
}

void display()
{
	switch (qNo)
	{
	case 0:
		demo();
		break;
	case 1:
		translateDemo1();
		break;
	case 2:
		translateDemo2();
		break;
	case 3:
		rotateDemo1();
		break;
	case 4:
		rotateDemo2();
		break;
	case 5:
		q2();
		break;
	case 6:
		q3();
		break;
	case 7:
		q4();
		break;
	default:
		break;
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
		950, 10, 300, 300,
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