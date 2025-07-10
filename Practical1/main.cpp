
#include <Windows.h>
#include <gl/GL.h>
#include<math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNo = 1; //question no
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == '1')
			qNo = 1;
		else if (wParam == '2')
			qNo = 2;
		else if (wParam == '3')
			qNo = 3;
		else if (wParam == '4')
			qNo = 4;
		else if (wParam == '5')
			qNo = 5;
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

void p1_q1() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0f);
	glLineWidth(5.0f);
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
}

void p1_q2() {
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5.0f);
	glLineWidth(5.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(-1.0f, 0.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
}

void p1_q3() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0f);
	glLineWidth(5.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.1f, 1.0f);
	glVertex2f(0.1f, 1.0f);
	glVertex2f(0.1f, -1.0f);
	glVertex2f(-0.1f, -1.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-1.0f, 0.1f);
	glVertex2f(1.0f, 0.1f);
	glVertex2f(1.0f, -0.1f);
	glVertex2f(-1.0f, -0.1f);
	glEnd();
}

void p1_q4() {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(-1.2f, 0.8f);
	glVertex2f(-0.8f, 1.2f);
	glVertex2f(1.2f, -0.8f);
	glVertex2f(0.8f, -1.2f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-1.2f, -0.8);
	glVertex2f(-0.8f, -1.2f);
	glVertex2f(1.2f, 0.8f);
	glVertex2f(0.8f, 1.2f);
	glEnd();
}

int counter = 0;
bool smile = true;
void p1_q5()
{
	float radius = 0.7;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.5f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = radius * .8 * cos(theta);
		float y = radius * .8 * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = 0.6 * .8 * cos(theta);
		float y = 0.6 * .8 * sin(theta);
		glVertex2f(x, y - 0.2F);
	}
	glEnd();

	float r2 = 0.2;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r2 * .8 * cos(theta);
		float y = r2 * .8 * sin(theta);
		glVertex2f(x - 0.16f, y + 0.28f);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r2 * .8 * cos(theta);
		float y = r2 * .8 * sin(theta);
		glVertex2f(x + 0.16f, y + 0.28f);
	}
	glEnd();

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r2 * .8 * cos(theta);
		float y = r2 * .8 * sin(theta);
		glVertex2f(x - 0.16f, y + 0.28f);
	}
	glEnd();
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r2 * .8 * cos(theta);
		float y = r2 * .8 * sin(theta);
		glVertex2f(x + 0.16f, y + 0.28f);
	}
	glEnd();



	float r3 = 0.05;
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r3 * .8 * cos(theta);
		float y = r3 * .8 * sin(theta);
		glVertex2f(x + 0.16f, y + 0.25f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r3 * .8 * cos(theta);
		float y = r3 * .8 * sin(theta);
		glVertex2f(x - 0.16f, y + 0.25f);
	}
	glEnd();

	float r4 = 0.02;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r4 * .8 * cos(theta);
		float y = r4 * .8 * sin(theta);
		glVertex2f(x - 0.16f, y + 0.23f);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r4 * .8 * cos(theta);
		float y = r4 * .8 * sin(theta);
		glVertex2f(x + 0.16f, y + 0.23f);
	}
	glEnd();

	float r5 = 0.08;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r5 * .8 * cos(theta);
		float y = r5 * .8 * sin(theta);
		glVertex2f(x, y + 0.12f);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = r4 * .8 * cos(theta);
		float y = r4 * .8 * sin(theta);
		glVertex2f(x - 0.03f, y + 0.15f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.005f, 0.05f);
	glVertex2f(-0.005f, -0.15f);
	glVertex2f(0.005f, -0.15f);
	glVertex2f(0.005f, 0.05f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.25f, 0.1f);
	glVertex2f(-0.25f, 0.08f);
	glVertex2f(-0.05F, 0.05f);
	glVertex2f(-0.05f, 0.03f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.25f, 0.1f);
	glVertex2f(0.25f, 0.08f);
	glVertex2f(0.05F, 0.05f);
	glVertex2f(0.05f, 0.03f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.25f, -0.01f);
	glVertex2f(-0.25f, 0.01f);
	glVertex2f(-0.05F, 0.01f);
	glVertex2f(-0.05f, -0.01f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.25f, -0.01f);
	glVertex2f(0.25f, 0.01f);
	glVertex2f(0.05F, 0.01f);
	glVertex2f(0.05f, -0.01f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.25f, -0.1f);
	glVertex2f(-0.25f, -0.08f);
	glVertex2f(-0.05F, -0.05f);
	glVertex2f(-0.05f, -0.03f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.25f, -0.1f);
	glVertex2f(0.25f, -0.08f);
	glVertex2f(0.05F, -0.05f);
	glVertex2f(0.05f, -0.03f);
	glEnd();

	counter++;

	if (counter >= 60)
	{
		smile = !smile;
		counter = 0;
	}
	if (smile) {
		glLineWidth(6.0f);
		glBegin(GL_POLYGON);
	}
	else {
		glLineWidth(6.0f);
		glBegin(GL_LINE_STRIP);
	}
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 240; i < 305; i++)
	{
		float theta = 2.0f * 3.14159 * i / 360;
		float x = 0.7 * .8 * cos(theta);
		float y = 0.7 * .8 * sin(theta);
		glVertex2f(x, y + 0.3f);
	}
	glEnd();
}

void display()
{
	//--------------
	// Practical 1
	// -------------
	switch (qNo) {
	case 1:
		p1_q1();
		break;
	case 2:
		p1_q2();
		break;
	case 3:
		p1_q3();
		break;
	case 4:
		p1_q4();
		break;
	case 5:
		p1_q5();
		break;
	default:
		p1_q4();

	}
	glFlush();

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