#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <stdio.h>
#include <crtdbg.h>
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#define WINDOW_TITLE "OpenGL Window"

float rotationAngle = 0.0f;
GLuint iceCreamTexture1;
GLuint iceCreamTexture2;
GLuint coneTexture;
GLuint cherryTexture;

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
	return false;
}

static void bindPlaceholder(GLuint& textureID, const char* filename)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	unsigned char textureData[64 * 64 * 3];
	if (strstr(filename, "texture.bmp")) {
		for (int i = 0; i < 64 * 64 * 3; i += 3) { textureData[i] = 100; textureData[i + 1] = 255; textureData[i + 2] = 100; }
	}
	else if (strstr(filename, "vanilla")) {
		for (int i = 0; i < 64 * 64 * 3; i += 3) { textureData[i] = 255; textureData[i + 1] = 248; textureData[i + 2] = 230; }
	}
	else if (strstr(filename, "waffle")) {
		for (int i = 0; i < 64 * 64 * 3; i += 3) { textureData[i] = 160; textureData[i + 1] = 120; textureData[i + 2] = 80; }
	}
	else if (strstr(filename, "cherry")) {
		for (int i = 0; i < 64 * 64 * 3; i += 3) { textureData[i] = 255; textureData[i + 1] = 50; textureData[i + 2] = 50; }
	}
	else {
		for (int i = 0; i < 64 * 64 * 3; i += 3) { textureData[i] = 255; textureData[i + 1] = 0; textureData[i + 2] = 255; }
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

static bool convertBMPToRGB24(HBITMAP hBitmap, unsigned char*& outData, int& width, int& height, int& rowSize)
{
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	if (bitmap.bmBitsPixel != 24 && bitmap.bmBitsPixel != 32) {
		printf("Unsupported bitmap format: %d bits per pixel\n", bitmap.bmBitsPixel);
		return false;
	}
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
	HDC hdc = GetDC(NULL);
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hBitmap);
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = -height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	rowSize = ((width * 3 + 3) & ~3);
	int dataSize = rowSize * height;
	outData = new(std::nothrow) unsigned char[dataSize];
	if (!outData) {
		printf("Failed to allocate memory for bitmap data\n");
		DeleteDC(memDC);
		ReleaseDC(NULL, hdc);
		return false;
	}
	memset(outData, 0, dataSize);
	int result = GetDIBits(memDC, hBitmap, 0, height, outData, &bmpInfo, DIB_RGB_COLORS);
	DeleteDC(memDC);
	ReleaseDC(NULL, hdc);
	if (result == 0) {
		printf("Failed to get bitmap data\n");
		delete[] outData;
		outData = nullptr;
		return false;
	}
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int idx = row * rowSize + col * 3;
			unsigned char tmp = outData[idx];
			outData[idx] = outData[idx + 2];
			outData[idx + 2] = tmp;
		}
	}
	return true;
}

GLuint loadBMPTexture(const char* filename)
{
	GLuint textureID = 0;
	printf("Attempting to load: %s\n", filename);
	HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap) {
		printf("Failed to load %s, using placeholder\n", filename);
		bindPlaceholder(textureID, filename);
		return textureID;
	}
	BITMAP bmpInfoHeader;
	GetObject(hBitmap, sizeof(BITMAP), &bmpInfoHeader);
	printf("Successfully loaded %s\n", filename);
	printf("Bitmap size: %d x %d, bits per pixel: %d\n", bmpInfoHeader.bmWidth, bmpInfoHeader.bmHeight, bmpInfoHeader.bmBitsPixel);
	unsigned char* rgbData = nullptr;
	int w = 0, h = 0, rowSize = 0;
	if (!convertBMPToRGB24(hBitmap, rgbData, w, h, rowSize)) {
		DeleteObject(hBitmap);
		return 0;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	delete[] rgbData;
	DeleteObject(hBitmap);
	printf("Created texture with ID: %d\n", textureID);
	return textureID;
}

static GLuint tryLoadBMP(const char* a, const char* b, const char* c)
{
	GLuint t = loadBMPTexture(a);
	if (t == 0) t = loadBMPTexture(b);
	if (t == 0) t = loadBMPTexture(c);
	return t;
}

void initTextures()
{
	printf("Initializing textures...\n");
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);
	printf("Current working directory: %s\n", currentDir);
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA("*.bmp", &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		printf("Found BMP files:\n");
		do { printf("  - %s\n", findFileData.cFileName); } while (FindNextFileA(hFind, &findFileData) != 0);
		FindClose(hFind);
	}
	else {
		printf("No BMP files found in current directory\n");
	}
	iceCreamTexture2 = tryLoadBMP("yam.bmp", "../yam.bmp", "../../yam.bmp");
	iceCreamTexture1 = tryLoadBMP("chocolate.bmp", "../chocolate.bmp", "../../chocolate.bmp");
	coneTexture = tryLoadBMP("waffle.bmp", "../waffle.bmp", "../../waffle.bmp");
	cherryTexture = tryLoadBMP("cherry.bmp", "../cherry.bmp", "../../cherry.bmp");
	printf("Texture IDs - Ice Cream 1: %d, Ice Cream 2: %d, Cone: %d, Cherry: %d\n", iceCreamTexture1, iceCreamTexture2, coneTexture, cherryTexture);
}

static void drawQuadricSphere(float radius, int slices, int stacks, bool withTex, bool withNormals)
{
	GLUquadricObj* q = gluNewQuadric();
	if (withTex) gluQuadricTexture(q, GL_TRUE);
	if (withNormals) gluQuadricNormals(q, GLU_SMOOTH);
	gluSphere(q, radius, slices, stacks);
	gluDeleteQuadric(q);
}

static void drawQuadricCylinder(float baseR, float topR, float height, int slices, int stacks, bool withTex, bool withNormals)
{
	GLUquadricObj* q = gluNewQuadric();
	if (withTex) gluQuadricTexture(q, GL_TRUE);
	if (withNormals) gluQuadricNormals(q, GLU_SMOOTH);
	gluCylinder(q, baseR, topR, height, slices, stacks);
	gluDeleteQuadric(q);
}

void drawTexturedSphere(float radius, int slices, int stacks, GLuint texture)
{
	if (texture == 0) { drawQuadricSphere(radius, slices, stacks, false, false); return; }
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	drawQuadricSphere(radius, slices, stacks, true, true);
	glDisable(GL_TEXTURE_2D);
}

void drawTexturedCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, GLuint texture)
{
	if (texture == 0) { drawQuadricCylinder(baseRadius, topRadius, height, slices, stacks, false, false); return; }
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	drawQuadricCylinder(baseRadius, topRadius, height, slices, stacks, true, true);
	glDisable(GL_TEXTURE_2D);
}

void drawSphere(float radius, int slices, int stacks)
{
	drawQuadricSphere(radius, slices, stacks, false, false);
}

void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks)
{
	drawQuadricCylinder(baseRadius, topRadius, height, slices, stacks, false, false);
}

void drawWaferCone()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.55f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	drawTexturedCylinder(0.0f, 0.25f, 0.8f, 16, 8, coneTexture);
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.4f, 0.2f, 0.1f);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 8; i++) {
		float angle = 2.0f * 3.14159f * (float)i / 8.0f;
		float x1 = 0.26f * (float)cos(angle);
		float z1 = 0.26f * (float)sin(angle);
		glVertex3f(x1, 0.25f, z1);
		glVertex3f(0.0f, -0.55f, 0.0f);
	}
	for (float y = 0.15f; y >= -0.45f; y -= 0.15f) {
		float t = (0.25f - y) / 0.8f;
		float radius = 0.26f * (1.0f - t);
		for (int i = 0; i < 16; i++) {
			float a1 = 2.0f * 3.14159f * (float)i / 16.0f;
			float a2 = 2.0f * 3.14159f * (float)(i + 1) / 16.0f;
			glVertex3f(radius * (float)cos(a1), y, radius * (float)sin(a1));
			glVertex3f(radius * (float)cos(a2), y, radius * (float)sin(a2));
		}
	}
	glEnd();
}

void drawIceCreamScoops()
{
	glPushMatrix();
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.35f, 0.0f);
	drawTexturedSphere(0.22f, 20, 20, iceCreamTexture1);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.6f, 0.0f);
	drawTexturedSphere(0.2f, 20, 20, iceCreamTexture2);
	glPopMatrix();
	glPopMatrix();
}

void drawToppings()
{
	glPushMatrix();
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.1f, 0.78f, 0.0f);
	drawTexturedSphere(0.04f, 10, 10, cherryTexture);
	glPopMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glPushMatrix();
	glTranslatef(0.1f, 0.82f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	drawCylinder(0.005f, 0.005f, 0.08f, 4, 2);
	glPopMatrix();
	glColor3f(0.3f, 0.15f, 0.05f);
	glPushMatrix(); glTranslatef(-0.12f, 0.6f, 0.08f); drawSphere(0.02f, 8, 8); glPopMatrix();
	glPushMatrix(); glTranslatef(0.15f, 0.57f, -0.04f); drawSphere(0.02f, 8, 8); glPopMatrix();
	glPushMatrix(); glTranslatef(-0.08f, 0.38f, -0.12f); drawSphere(0.02f, 8, 8); glPopMatrix();
	glPushMatrix(); glTranslatef(0.1f, 0.32f, 0.15f); drawSphere(0.02f, 8, 8); glPopMatrix();
	glLineWidth(2.0f);
	for (int i = 0; i < 24; i++) {
		float angle = 2.0f * 3.14159f * (float)i / 24.0f;
		float randomOffset = (float)(i % 3) * 0.3f;
		if (i % 2 == 0) {
			float radius = 0.18f + (float)(i % 3) * 0.02f;
			float x = radius * (float)cos(angle);
			float z = radius * (float)sin(angle);
			float y = 0.35f + randomOffset * 0.1f;
			if (i % 5 == 0) glColor3f(1.0f, 0.4f, 0.7f);
			else if (i % 5 == 1) glColor3f(1.0f, 1.0f, 0.2f);
			else if (i % 5 == 2) glColor3f(0.2f, 0.4f, 1.0f);
			else if (i % 5 == 3) glColor3f(0.2f, 1.0f, 0.3f);
			else glColor3f(1.0f, 0.6f, 0.1f);
			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef((float)(i * 23), 0.3f + (float)(i % 3) * 0.2f, 0.8f, 0.1f + (float)(i % 2) * 0.3f);
			drawCylinder(0.008f, 0.008f, 0.04f, 6, 2);
			glPopMatrix();
		}
		if (i % 3 != 0) {
			float radius = 0.16f + (float)(i % 2) * 0.02f;
			float x = radius * (float)cos(angle + 0.5f);
			float z = radius * (float)sin(angle + 0.5f);
			float y = 0.6f + randomOffset * 0.08f;
			if (i % 6 == 0) glColor3f(0.8f, 0.2f, 1.0f);
			else if (i % 6 == 1) glColor3f(1.0f, 0.4f, 0.7f);
			else if (i % 6 == 2) glColor3f(0.2f, 1.0f, 0.3f);
			else if (i % 6 == 3) glColor3f(1.0f, 1.0f, 0.2f);
			else if (i % 6 == 4) glColor3f(0.2f, 0.4f, 1.0f);
			else glColor3f(1.0f, 0.2f, 0.2f);
			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef((float)(i * 31), 0.7f - (float)(i % 2) * 0.4f, 0.2f, 0.6f + (float)(i % 3) * 0.2f);
			drawCylinder(0.008f, 0.008f, 0.04f, 6, 2);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.5f, 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	drawWaferCone();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	drawIceCreamScoops();
	drawToppings();
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0f) rotationAngle = 0.0f;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(0);
#endif
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wc)) return false;
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);
	HDC hdc = GetDC(hWnd);
	initPixelFormat(hdc);
	HGLRC hglrc = wglCreateContext(hdc);
	if (!wglMakeCurrent(hdc, hglrc)) return false;
	initTextures();
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
