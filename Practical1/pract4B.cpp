//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
//#pragma comment (lib, "OpenGL32.lib")
//#pragma comment (lib, "Glu32.lib")
//
//#define WINDOW_TITLE "OpenGL Window"
//
//// Global variables
//float translateX = 0.0f, translateY = 0.0f;
//float objectR = 1.0f, objectG = 1.0f, objectB = 1.0f;
//float starColorTime = 0.0f;
//float pointAngle = 0.0f;
//float boxSize = 0.1f;
//bool expanding = true;
//int current_exercise = 3; // Start with the new exercise by default
//
//// Exercise 3 (Rectangles) variables
//float rect_dx = 0.0f, rect_dy = 0.0f;
//
//// Windmill Exercise variables
//float windmill_angle = 0.0f, windmill_speed = 2.0f, bird_flap_offset = 0.0f;
//const float POV_SPEED_THRESHOLD = 30.0f;
//
//// Ice Cream Exercise variables
//float ice_cream_angle_y = 0.0f;
//GLUquadricObj* quadric = NULL;
//
//void Practical4B_IceCream(); // Forward declaration
//
//LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    switch (msg)
//    {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    case WM_KEYDOWN:
//        if (wParam == VK_ESCAPE) PostQuitMessage(0);
//
//        // --- EXERCISE MODE SWITCHING ---
//        if (wParam == '1') current_exercise = 1;
//        if (wParam == '2') current_exercise = 2;
//        if (wParam == '3') current_exercise = 3; // Switch to Ice Cream
//
//        // --- CONTROLS FOR PRACTICAL EXERCISE 3 (RECTANGLES) ---
//        if (current_exercise == 1) {
//            // (Your existing controls for exercise 1)
//        }
//
//        // --- CONTROLS FOR EXERCISE Q2 (WINDMILL) ---
//        else if (current_exercise == 2) {
//            // (Your existing controls for exercise 2)
//        }
//        break;
//
//    default:
//        break;
//    }
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//bool initPixelFormat(HDC hdc)
//{
//    PIXELFORMATDESCRIPTOR pfd;
//    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
//
//    pfd.cAlphaBits = 8;
//    pfd.cColorBits = 32;
//    pfd.cDepthBits = 24; // Depth buffer for 3D
//    pfd.cStencilBits = 0;
//    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
//    pfd.iLayerType = PFD_MAIN_PLANE;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//    pfd.nVersion = 1;
//
//    int n = ChoosePixelFormat(hdc, &pfd);
//    if (SetPixelFormat(hdc, n, &pfd))
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//// Ice Cream Functions
//void drawIceCreamCone() {
//    glPushMatrix();
//    glEnable(GL_LIGHTING);
//    glColor3f(0.8f, 0.5f, 0.2f); // Brown color for cone
//    glTranslatef(0.0f, 0.2f, 0.0f);
//    glRotatef(90.0, 1.0, 0.0, 0.0);
//    gluQuadricDrawStyle(quadric, GLU_FILL);
//    gluCylinder(quadric, 0.8, 0.0, 2.5, 20, 10);
//    glDisable(GL_LIGHTING);
//    glPopMatrix();
//}
//
//void drawIceCreamScoops() {
//    glEnable(GL_LIGHTING);
//    gluQuadricDrawStyle(quadric, GLU_FILL);
//
//    // Mint green scoop
//    glPushMatrix();
//    glColor3f(0.5f, 0.9f, 0.5f);
//    glTranslatef(0.0f, 0.5f, 0.0f);
//    gluSphere(quadric, 0.9, 30, 30);
//    glPopMatrix();
//
//    // Cookies & cream scoop
//    glPushMatrix();
//    glColor3f(0.7f, 0.7f, 0.7f);
//    glTranslatef(0.0f, 1.5f, 0.0f);
//    gluSphere(quadric, 0.8, 30, 30);
//    glPopMatrix();
//
//    glDisable(GL_LIGHTING);
//}
//
//void drawIceCreamToppings() {
//    // Chocolate stick (no lighting)
//    glPushMatrix();
//    glColor3f(0.3f, 0.15f, 0.05f);
//    glTranslatef(0.2f, 2.2f, 0.1f);
//    glRotatef(60.0, 0.0, 0.0, 1.0);
//    glScalef(0.1f, 0.8f, 0.1f);
//
//    glBegin(GL_QUADS);
//    glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
//    glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
//    glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
//    glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
//    glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
//    glEnd();
//    glPopMatrix();
//
//    // Cherry (with stem)
//    glEnable(GL_LIGHTING);
//    glPushMatrix();
//    glColor3f(1.0, 0.0, 0.0);
//    glTranslatef(-0.3f, 2.2f, 0.3f);
//    gluSphere(quadric, 0.2, 20, 20);
//    glPopMatrix();
//
//    glPushMatrix();
//    glColor3f(0.5, 0.0, 0.0);
//    glTranslatef(-0.3f, 2.4f, 0.3f);
//    glRotatef(-30, 1, 0, 0);
//    glLineWidth(3.0f);
//    glBegin(GL_LINES);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(0.1f, 0.2f, 0.0f);
//    glEnd();
//    glLineWidth(1.0f);
//    glPopMatrix();
//    glDisable(GL_LIGHTING);
//}
//
//void Practical4B_IceCream() {
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0.0, 1.5, 8.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
//
//    glEnable(GL_LIGHT0);
//    GLfloat light_pos[] = { 2.0, 5.0, 5.0, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
//
//    glPushMatrix();
//    glRotatef(ice_cream_angle_y, 0.0, 1.0, 0.0);
//
//    drawIceCreamCone();
//    drawIceCreamScoops();
//    drawIceCreamToppings();
//
//    glPopMatrix();
//}
//
//void display()
//{
//    // Common setup for all frames
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    // --- Update animation variables ---
//    windmill_angle += windmill_speed;
//    ice_cream_angle_y += 0.5f; // Continuously rotate the ice cream
//    if (ice_cream_angle_y > 360) ice_cream_angle_y -= 360;
//
//    // --- Select which exercise to draw ---
//    if (current_exercise == 3) {
//        // 3D rendering setup
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background for the 3D model
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color AND depth buffers
//        glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
//        Practical4B_IceCream();
//    }
//    else {
//        // 2D rendering setup
//        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Original white background
//        glClear(GL_COLOR_BUFFER_BIT); // Only clear color buffer for 2D
//        glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D
//
//        // Reset matrices for 2D orthographic view
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//    }
//}
//
//
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
//{
//    // (Your existing WinMain function...)
//    srand(time(NULL));
//    WNDCLASSEX wc;
//    ZeroMemory(&wc, sizeof(WNDCLASSEX));
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.hInstance = GetModuleHandle(NULL);
//    wc.lpfnWndProc = WindowProcedure;
//    wc.lpszClassName = WINDOW_TITLE;
//    wc.style = CS_HREDRAW | CS_VREDRAW;
//    if (!RegisterClassEx(&wc)) return false;
//    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//        NULL, NULL, wc.hInstance, NULL);
//
//    HDC hdc = GetDC(hWnd);
//    initPixelFormat(hdc);
//    HGLRC hglrc = wglCreateContext(hdc);
//    if (!wglMakeCurrent(hdc, hglrc)) return false;
//
//    quadric = gluNewQuadric();
//    if (quadric == NULL) {
//        return false;
//    }
//
//    ShowWindow(hWnd, nCmdShow);
//
//    MSG msg;
//    ZeroMemory(&msg, sizeof(msg));
//    while (true)
//    {
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT) break;
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        display();
//
//        SwapBuffers(hdc);
//    }
//
//    gluDeleteQuadric(quadric);
//
//    UnregisterClass(WINDOW_TITLE, wc.hInstance);
//
//    return true;
//}