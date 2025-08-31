#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <stdio.h>  // Added for debugging printf
#include <crtdbg.h> 
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#define WINDOW_TITLE "OpenGL Window"

// Global rotation angle for 3D effect
float rotationAngle = 0.0f;

// Texture IDs
GLuint iceCreamTexture1;  // For mint green scoop
GLuint iceCreamTexture2;  // For vanilla scoop
GLuint coneTexture;       // For wafer cone
GLuint cherryTexture;     // For cherry

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
// BMP texture loading function with better error handling
// Fixed BMP texture loading function
GLuint loadBMPTexture(const char* filename) {
	GLuint textureID = 0;

	printf("Attempting to load: %s\n", filename);

	// Load BMP file using Windows API
	HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap) {
		printf("Failed to load %s, using placeholder\n", filename);

		// Create placeholder texture (same as before)
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		unsigned char textureData[64 * 64 * 3];

		// Different colors for different textures based on filename
		if (strstr(filename, "texture.bmp")) {
			for (int i = 0; i < 64 * 64 * 3; i += 3) {
				textureData[i] = 100; textureData[i + 1] = 255; textureData[i + 2] = 100;
			}
		}
		else if (strstr(filename, "vanilla")) {
			for (int i = 0; i < 64 * 64 * 3; i += 3) {
				textureData[i] = 255; textureData[i + 1] = 248; textureData[i + 2] = 230;
			}
		}
		else if (strstr(filename, "waffle")) {
			for (int i = 0; i < 64 * 64 * 3; i += 3) {
				textureData[i] = 160; textureData[i + 1] = 120; textureData[i + 2] = 80;
			}
		}
		else if (strstr(filename, "cherry")) {
			for (int i = 0; i < 64 * 64 * 3; i += 3) {
				textureData[i] = 255; textureData[i + 1] = 50; textureData[i + 2] = 50;
			}
		}
		else {
			for (int i = 0; i < 64 * 64 * 3; i += 3) {
				textureData[i] = 255; textureData[i + 1] = 0; textureData[i + 2] = 255;
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return textureID;
	}

	printf("Successfully loaded %s\n", filename);

	// Get bitmap info
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);

	printf("Bitmap size: %d x %d, bits per pixel: %d\n", bitmap.bmWidth, bitmap.bmHeight, bitmap.bmBitsPixel);

	// Only proceed if it's a 24-bit or 32-bit bitmap
	if (bitmap.bmBitsPixel != 24 && bitmap.bmBitsPixel != 32) {
		printf("Unsupported bitmap format: %d bits per pixel\n", bitmap.bmBitsPixel);
		DeleteObject(hBitmap);
		return 0;
	}

	// Get device context
	HDC hdc = GetDC(NULL);
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hBitmap);

	// Create BITMAPINFO structure
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = bitmap.bmWidth;
	bmpInfo.bmiHeader.biHeight = -bitmap.bmHeight; // Negative for top-down
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24; // Force 24-bit
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// FIXED: Calculate proper data size and ensure alignment
	int rowSize = ((bitmap.bmWidth * 3 + 3) & ~3); // Align to 4-byte boundary
	int dataSize = rowSize * bitmap.bmHeight;
	printf("Calculated data size: %d bytes (row size: %d)\n", dataSize, rowSize);

	// FIXED: Use aligned allocation
	unsigned char* bitmapData = new(std::nothrow) unsigned char[dataSize];
	if (!bitmapData) {
		printf("Failed to allocate memory for bitmap data\n");
		DeleteDC(memDC);
		ReleaseDC(NULL, hdc);
		DeleteObject(hBitmap);
		return 0;
	}

	// Zero the memory first
	memset(bitmapData, 0, dataSize);

	// Get bitmap bits
	int result = GetDIBits(memDC, hBitmap, 0, bitmap.bmHeight, bitmapData, &bmpInfo, DIB_RGB_COLORS);
	if (result == 0) {
		printf("Failed to get bitmap data\n");
		delete[] bitmapData;
		DeleteDC(memDC);
		ReleaseDC(NULL, hdc);
		DeleteObject(hBitmap);
		return 0;
	}

	// FIXED: Only convert pixels that exist, respect row padding
	for (int row = 0; row < bitmap.bmHeight; row++) {
		for (int col = 0; col < bitmap.bmWidth; col++) {
			int pixelIndex = row * rowSize + col * 3;
			if (pixelIndex + 2 < dataSize) { // Safety check
				// Convert BGR to RGB
				unsigned char temp = bitmapData[pixelIndex];
				bitmapData[pixelIndex] = bitmapData[pixelIndex + 2];
				bitmapData[pixelIndex + 2] = temp;
			}
		}
	}

	// Generate OpenGL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// FIXED: Use original bitmap dimensions and proper row data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.bmWidth, bitmap.bmHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Clean up
	delete[] bitmapData;
	DeleteDC(memDC);
	ReleaseDC(NULL, hdc);
	DeleteObject(hBitmap);

	printf("Created texture with ID: %d\n", textureID);
	return textureID;
}

void initTextures() {
	printf("Initializing textures...\n");

	// Debug: Show current working directory
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);
	printf("Current working directory: %s\n", currentDir);

	// Also try to list files in current directory
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA("*.bmp", &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		printf("Found BMP files:\n");
		do {
			printf("  - %s\n", findFileData.cFileName);
		} while (FindNextFileA(hFind, &findFileData) != 0);
		FindClose(hFind);
	}
	else {
		printf("No BMP files found in current directory\n");
	}

	// Load BMP textures - try multiple possible locations
	iceCreamTexture2 = loadBMPTexture("vanilla-texture.bmp");
	if (iceCreamTexture2 == 0) iceCreamTexture2 = loadBMPTexture("../vanilla-texture.bmp");
	if (iceCreamTexture2 == 0) iceCreamTexture2 = loadBMPTexture("../../vanilla-texture.bmp");

	iceCreamTexture1 = loadBMPTexture("chocolate-texture.bmp");
	if (iceCreamTexture1 == 0) iceCreamTexture1 = loadBMPTexture("../chocolate-texture.bmp");
	if (iceCreamTexture1 == 0) iceCreamTexture1 = loadBMPTexture("../../chocolate-texture.bmp");

	coneTexture = loadBMPTexture("waffle-texture.bmp");
	if (coneTexture == 0) coneTexture = loadBMPTexture("../waffle-texture.bmp");
	if (coneTexture == 0) coneTexture = loadBMPTexture("../../waffle-texture.bmp");

	cherryTexture = loadBMPTexture("cherry-texture.bmp");
	if (cherryTexture == 0) cherryTexture = loadBMPTexture("../cherry-texture.bmp");
	if (cherryTexture == 0) cherryTexture = loadBMPTexture("../../cherry-texture.bmp");

	printf("Texture IDs - Ice Cream 1: %d, Ice Cream 2: %d, Cone: %d, Cherry: %d\n",
		iceCreamTexture1, iceCreamTexture2, coneTexture, cherryTexture);
}

void drawTexturedSphere(float radius, int slices, int stacks, GLuint texture)
{
	if (texture == 0) {
		// If no texture, draw with solid color
		GLUquadricObj* quadric = gluNewQuadric();
		gluSphere(quadric, radius, slices, stacks);
		gluDeleteQuadric(quadric);
		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Ensure texture coordinates are generated
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH); // Add smooth normals
	gluSphere(quadric, radius, slices, stacks);
	gluDeleteQuadric(quadric);

	glDisable(GL_TEXTURE_2D);
}

void drawTexturedCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, GLuint texture)
{
	if (texture == 0) {
		// If no texture, draw with solid color
		GLUquadricObj* quadric = gluNewQuadric();
		gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		gluDeleteQuadric(quadric);
		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Ensure texture coordinates are generated
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH); // Add smooth normals
	gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
	gluDeleteQuadric(quadric);

	glDisable(GL_TEXTURE_2D);
}

void drawSphere(float radius, int slices, int stacks)
{
	GLUquadricObj* quadric = gluNewQuadric();
	gluSphere(quadric, radius, slices, stacks);
	gluDeleteQuadric(quadric);
}

void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks)
{
	GLUquadricObj* quadric = gluNewQuadric();
	gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
	gluDeleteQuadric(quadric);
}

void drawWaferCone()
{
	// White color to let texture show through completely
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.55f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	// Draw textured cone
	drawTexturedCylinder(0.0f, 0.25f, 0.8f, 16, 8, coneTexture);

	glPopMatrix();

	// Draw wafer pattern ON the cone surface (optional - you might want to remove this to see texture better)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D); // Make sure texture is disabled for lines
	glColor3f(0.4f, 0.2f, 0.1f); // Darker brown lines
	glLineWidth(1.0f); // Thinner lines

	// Draw wafer grid pattern
	glBegin(GL_LINES);

	// Vertical lines on cone surface
	for (int i = 0; i < 8; i++) { // Fewer lines
		float angle = 2.0f * 3.14159f * (float)i / 8.0f;
		float x1 = 0.26f * (float)cos(angle);
		float z1 = 0.26f * (float)sin(angle);
		float x2 = 0.0f;
		float z2 = 0.0f;

		glVertex3f(x1, 0.25f, z1);
		glVertex3f(x2, -0.55f, z2);
	}

	// Horizontal circular lines on cone surface
	for (float y = 0.15f; y >= -0.45f; y -= 0.15f) { // Fewer lines
		float t = (0.25f - y) / 0.8f;
		float radius = 0.26f * (1.0f - t);

		for (int i = 0; i < 16; i++) { // Fewer segments
			float angle1 = 2.0f * 3.14159f * (float)i / 16.0f;
			float angle2 = 2.0f * 3.14159f * (float)(i + 1) / 16.0f;

			glVertex3f(radius * (float)cos(angle1), y, radius * (float)sin(angle1));
			glVertex3f(radius * (float)cos(angle2), y, radius * (float)sin(angle2));
		}
	}

	glEnd();
}

void drawIceCreamScoops()
{
	glPushMatrix();

	// Rotate around y-axis for 3D effect
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

	// First scoop (bottom) - with texture
	glColor3f(1.0f, 1.0f, 1.0f); // Pure white to let texture show through
	glPushMatrix();
	glTranslatef(0.0f, 0.35f, 0.0f);
	drawTexturedSphere(0.22f, 20, 20, iceCreamTexture1);
	glPopMatrix();

	// Second scoop (top) - with texture
	glColor3f(1.0f, 1.0f, 1.0f); // Pure white to let texture show through
	glPushMatrix();
	glTranslatef(0.0f, 0.6f, 0.0f);
	drawTexturedSphere(0.2f, 20, 20, iceCreamTexture2);
	glPopMatrix();

	glPopMatrix();
}

void drawToppings()
{
	glPushMatrix();

	// Rotate toppings with ice cream
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

	// Cherry on top with texture
	glColor3f(1.0f, 1.0f, 1.0f); // Pure white to let texture show through
	glPushMatrix();
	glTranslatef(0.1f, 0.78f, 0.0f);
	drawTexturedSphere(0.04f, 10, 10, cherryTexture);
	glPopMatrix();

	// Cherry stem - Brown cylinder (no texture)
	glColor3f(0.4f, 0.2f, 0.0f);
	glPushMatrix();
	glTranslatef(0.1f, 0.82f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	drawCylinder(0.005f, 0.005f, 0.08f, 4, 2);
	glPopMatrix();

	// Chocolate chips on scoops - Small dark spheres (no texture)
	glColor3f(0.3f, 0.15f, 0.05f);

	// Chips on top scoop
	glPushMatrix();
	glTranslatef(-0.12f, 0.6f, 0.08f);
	drawSphere(0.02f, 8, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15f, 0.57f, -0.04f);
	drawSphere(0.02f, 8, 8);
	glPopMatrix();

	// Chips on bottom scoop
	glPushMatrix();
	glTranslatef(-0.08f, 0.38f, -0.12f);
	drawSphere(0.02f, 8, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.32f, 0.15f);
	drawSphere(0.02f, 8, 8);
	glPopMatrix();

	// Sprinkles - Small colored cylinders (no texture)
	glLineWidth(2.0f);

	// Create sprinkles in a circular pattern around both scoops
	for (int i = 0; i < 24; i++) {
		float angle = 2.0f * 3.14159f * (float)i / 24.0f;
		float randomOffset = (float)(i % 3) * 0.3f;

		// Sprinkles on bottom scoop (mint green one)
		if (i % 2 == 0) {
			float radius = 0.18f + (float)(i % 3) * 0.02f;
			float x = radius * (float)cos(angle);
			float z = radius * (float)sin(angle);
			float y = 0.35f + randomOffset * 0.1f;

			// Vary colors
			if (i % 5 == 0) glColor3f(1.0f, 0.4f, 0.7f); // Pink
			else if (i % 5 == 1) glColor3f(1.0f, 1.0f, 0.2f); // Yellow
			else if (i % 5 == 2) glColor3f(0.2f, 0.4f, 1.0f); // Blue
			else if (i % 5 == 3) glColor3f(0.2f, 1.0f, 0.3f); // Green
			else glColor3f(1.0f, 0.6f, 0.1f); // Orange

			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef((float)(i * 23), 0.3f + (float)(i % 3) * 0.2f, 0.8f, 0.1f + (float)(i % 2) * 0.3f);
			drawCylinder(0.008f, 0.008f, 0.04f, 6, 2);
			glPopMatrix();
		}

		// Sprinkles on top scoop (vanilla one)
		if (i % 3 != 0) {
			float radius = 0.16f + (float)(i % 2) * 0.02f;
			float x = radius * (float)cos(angle + 0.5f);
			float z = radius * (float)sin(angle + 0.5f);
			float y = 0.6f + randomOffset * 0.08f;

			// Vary colors
			if (i % 6 == 0) glColor3f(0.8f, 0.2f, 1.0f); // Purple
			else if (i % 6 == 1) glColor3f(1.0f, 0.4f, 0.7f); // Pink
			else if (i % 6 == 2) glColor3f(0.2f, 1.0f, 0.3f); // Green
			else if (i % 6 == 3) glColor3f(1.0f, 1.0f, 0.2f); // Yellow
			else if (i % 6 == 4) glColor3f(0.2f, 0.4f, 1.0f); // Blue
			else glColor3f(1.0f, 0.2f, 0.2f); // Red

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
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

		// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable depth testing for 3D effect
	glEnable(GL_DEPTH_TEST);

	// Enable lighting for better 3D appearance
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set up lighting
	GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // Increased ambient
	GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	// Set up the projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 10.0f);

	// Set up the view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.5f, 2.5f,    // Camera position
		0.0f, 0.0f, 0.0f,    // Look at point
		0.0f, 1.0f, 0.0f);   // Up vector

	// Disable lighting for cone (to show texture and grid lines)
	glDisable(GL_LIGHTING);

	// Draw the wafer cone (base) with rotation and texture
	glPushMatrix();
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	drawWaferCone();
	glPopMatrix();

	// Enable lighting for ice cream scoops and toppings
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Draw ice cream scoops with rotation and textures
	drawIceCreamScoops();

	// Draw toppings with textures
	drawToppings();

	// Update rotation angle for continuous rotation
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0f) {
		rotationAngle = 0.0f;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

//--------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	// Disable debug heap checking to prevent breakpoints
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

	// Create console window for debug output
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

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

	// Initialize textures
	initTextures();

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