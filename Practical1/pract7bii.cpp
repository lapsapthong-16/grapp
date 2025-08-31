#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

static bool  gPerspective = true;
static bool  gSplitViewport = false;

static bool  gShowGrid = false;
static float gTime = 0.0f;

static float gYaw = -25.0f;
static float gPitch = 20.0f;
static float gDist = 42.0f;

static float gBascule = 0.0f;
static bool  gAnim = true;
static float gBasculeDir = +1.0f;

static RECT  gClient = { 0,0,800,600 };

static bool  gLDragging = false;
static POINT gLastMouse = { 0,0 };

static inline float deg2rad(float a) { return a * 3.1415926535f / 180.0f; }

void initGLStyling();
void drawGridXZ(float halfX, float halfZ, float step);

GLuint gTexTower = 0;
GLuint gTexBase = 0;
GLuint gTexTop = 0;
GLuint gTexRoad = 0;
GLuint gTexBackground = 0; // SKY (bg.bmp)
GLuint gTexWater = 0;      // WATER (water.bmp)

static void bindPlaceholder(GLuint& tid, const char* nameRGBHint)
{
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);

    unsigned char data[64 * 64 * 3];
    unsigned char r = 200, g = 200, b = 200;

    if (strstr(nameRGBHint, "tower")) { r = 200; g = 190; b = 175; }
    else if (strstr(nameRGBHint, "base")) { r = 170; g = 165; b = 160; }
    else if (strstr(nameRGBHint, "top")) { r = 210; g = 200; b = 180; }
    else if (strstr(nameRGBHint, "road")) { r = 70;  g = 75;  b = 80; }
    else if (strstr(nameRGBHint, "bg")) { r = 120; g = 170; b = 220; }
    else if (strstr(nameRGBHint, "water")) { r = 30;  g = 120; b = 170; }

    for (int i = 0; i < 64 * 64 * 3; i += 3) { data[i] = r; data[i + 1] = g; data[i + 2] = b; }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

static bool bmpToRGB24(HBITMAP hBmp, unsigned char*& out, int& w, int& h, int& rowSize)
{
    BITMAP bm; GetObject(hBmp, sizeof(BITMAP), &bm);
    if (bm.bmBitsPixel != 24 && bm.bmBitsPixel != 32) return false;
    w = bm.bmWidth; h = bm.bmHeight;

    HDC dc = GetDC(NULL);
    HDC mem = CreateCompatibleDC(dc);
    SelectObject(mem, hBmp);

    BITMAPINFO bi{}; bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = w; bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1; bi.bmiHeader.biBitCount = 24; bi.bmiHeader.biCompression = BI_RGB;

    rowSize = ((w * 3 + 3) & ~3);
    int size = rowSize * h;
    out = new unsigned char[size]();
    if (!GetDIBits(mem, hBmp, 0, h, out, &bi, DIB_RGB_COLORS)) { DeleteDC(mem); ReleaseDC(NULL, dc); delete[] out; out = nullptr; return false; }
    DeleteDC(mem); ReleaseDC(NULL, dc);

    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x) {
            int idx = y * rowSize + x * 3;
            unsigned char t = out[idx]; out[idx] = out[idx + 2]; out[idx + 2] = t;
        }
    return true;
}

static GLuint loadBMPTexture(const char* filename)
{
    GLuint tid = 0;
    HBITMAP hBmp = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (!hBmp) { bindPlaceholder(tid, filename); return tid; }

    unsigned char* rgb = nullptr; int w = 0, h = 0, row = 0;
    if (!bmpToRGB24(hBmp, rgb, w, h, row)) { DeleteObject(hBmp); return 0; }

    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, rgb);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete[] rgb; DeleteObject(hBmp);
    return tid;
}

static GLuint tryLoad(const char* a, const char* b, const char* c)
{
    GLuint t = loadBMPTexture(a); if (!t) t = loadBMPTexture(b); if (!t) t = loadBMPTexture(c); return t;
}

static void initTextures()
{
    gTexTower = tryLoad("brick.bmp", "../brick.bmp", "../../brick.bmp");
    gTexBase = tryLoad("stone.bmp", "../stone.bmp", "../../stone.bmp");
    gTexTop = tryLoad("gray.bmp", "../gray.bmp", "../../gray.bmp");
    gTexRoad = tryLoad("road.bmp", "../road.bmp", "../../road.bmp");

    gTexBackground = tryLoad("bg.bmp", "../bg.bmp", "../../bg.bmp");
    glBindTexture(GL_TEXTURE_2D, gTexBackground);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F /*GL_CLAMP_TO_EDGE*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F /*GL_CLAMP_TO_EDGE*/);

    gTexWater = tryLoad("water.bmp", "../water.bmp", "../../water.bmp");
    glBindTexture(GL_TEXTURE_2D, gTexWater);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F /*GL_CLAMP_TO_EDGE*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F /*GL_CLAMP_TO_EDGE*/);
}

void drawBox(float w, float h, float d)
{
    float x = w * 0.5f, y = h * 0.5f, z = d * 0.5f;
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(x, -y, -z); glVertex3f(x, y, -z); glVertex3f(x, y, z); glVertex3f(x, -y, z);
    glNormal3f(-1, 0, 0);
    glVertex3f(-x, -y, z); glVertex3f(-x, y, z); glVertex3f(-x, y, -z); glVertex3f(-x, -y, -z);
    glNormal3f(0, 1, 0);
    glVertex3f(-x, y, -z); glVertex3f(-x, y, z); glVertex3f(x, y, z); glVertex3f(x, y, -z);
    glNormal3f(0, -1, 0);
    glVertex3f(-x, -y, z); glVertex3f(-x, -y, -z); glVertex3f(x, -y, -z); glVertex3f(x, -y, z);
    glNormal3f(0, 0, 1);
    glVertex3f(-x, -y, z); glVertex3f(x, -y, z); glVertex3f(x, y, z); glVertex3f(-x, y, z);
    glNormal3f(0, 0, -1);
    glVertex3f(x, -y, -z); glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z); glVertex3f(x, y, -z);
    glEnd();
}

void drawBoxTex(float w, float h, float d, float uScale, float vScale)
{
    float x = w * 0.5f, y = h * 0.5f, z = d * 0.5f;
    float us = uScale, vs = vScale;
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(x, -y, -z);
    glTexCoord2f(us, 0); glVertex3f(x, y, -z);
    glTexCoord2f(us, vs); glVertex3f(x, y, z);
    glTexCoord2f(0, vs); glVertex3f(x, -y, z);

    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-x, -y, z);
    glTexCoord2f(us, 0); glVertex3f(-x, y, z);
    glTexCoord2f(us, vs); glVertex3f(-x, y, -z);
    glTexCoord2f(0, vs); glVertex3f(-x, -y, -z);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-x, y, -z);
    glTexCoord2f(us, 0); glVertex3f(-x, y, z);
    glTexCoord2f(us, vs); glVertex3f(x, y, z);
    glTexCoord2f(0, vs); glVertex3f(x, y, -z);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-x, -y, z);
    glTexCoord2f(us, 0); glVertex3f(-x, -y, -z);
    glTexCoord2f(us, vs); glVertex3f(x, -y, -z);
    glTexCoord2f(0, vs); glVertex3f(x, -y, z);

    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-x, -y, z);
    glTexCoord2f(us, 0); glVertex3f(x, -y, z);
    glTexCoord2f(us, vs); glVertex3f(x, y, z);
    glTexCoord2f(0, vs); glVertex3f(-x, y, z);

    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(x, -y, -z);
    glTexCoord2f(us, 0); glVertex3f(-x, -y, -z);
    glTexCoord2f(us, vs); glVertex3f(-x, y, -z);
    glTexCoord2f(0, vs); glVertex3f(x, y, -z);
    glEnd();
}

void drawArch(float radius, float thickness, float span, int steps, float depth)
{
    float z0 = -depth * 0.5f, z1 = depth * 0.5f;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= steps; i++) {
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

static inline float cableY(float t, float yBase, float sag) { float m = t - 0.5f; return yBase - sag * (1.0f - 4.0f * m * m); }
void drawHangers(float, float, float, float, float, float, float) {}

void drawBeamBox(float x0, float x1, float y0, float y1, float z0, float z1)
{
    glPushMatrix();
    glTranslatef((x0 + x1) * 0.5f, (y0 + y1) * 0.5f, (z0 + z1) * 0.5f);
    drawBox(fabsf(x1 - x0), fabsf(y1 - y0), fabsf(z1 - z0));
    glPopMatrix();
}

void drawDeckGirders(float x0, float x1, float deckY, float deckWidth)
{
    float girderH = 1.2f;
    float zIn = deckWidth * 0.52f;
    float zOut = deckWidth * 0.60f;

    glColor3f(0.20f, 0.24f, 0.28f);
    drawBeamBox(x0, x1, deckY, deckY + girderH, zIn, zOut);
    drawBeamBox(x0, x1, deckY, deckY + girderH, -zOut, -zIn);

    float step = 3.0f;
    for (float x = x0; x <= x1 + 0.001f; x += step) {
        drawBeamBox(x - 0.10f, x + 0.10f, deckY, deckY + girderH, zIn, zOut);
        drawBeamBox(x - 0.10f, x + 0.10f, deckY, deckY + girderH, -zOut, -zIn);
    }
}

void drawDashedCenterLine(float len, float, float y, float dash, float gap)
{
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.95f, 0.95f, 0.70f);
    float halfW = 0.06f;
    float x = -len * 0.5f;
    while (x < len * 0.5f) {
        float x0 = x, x1 = fminf(x + dash, len * 0.5f);
        glVertex3f(x0, y + 0.01f, -halfW); glVertex3f(x1, y + 0.01f, -halfW);
        glVertex3f(x1, y + 0.01f, +halfW); glVertex3f(x0, y + 0.01f, +halfW);
        x += dash + gap;
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawExpansionJoint(float width, float y)
{
    glDisable(GL_LIGHTING);
    glColor3f(0.05f, 0.05f, 0.06f);
    glBegin(GL_QUADS);
    float t = 0.06f;
    glVertex3f(-t, y + 0.005f, -width * 0.5f); glVertex3f(+t, y + 0.005f, -width * 0.5f);
    glVertex3f(+t, y + 0.005f, width * 0.5f); glVertex3f(-t, y + 0.005f, width * 0.5f);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawTower()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gTexTower);
    glColor3f(1, 1, 1);
    drawBoxTex(6.0f, 24.0f, 8.0f, 2.0f, 2.5f);

    glBindTexture(GL_TEXTURE_2D, gTexTop);
    drawBoxTex(7.2f, 2.6f, 9.2f, 1.5f, 0.5f);
    drawBoxTex(7.6f, 0.3f, 9.6f, 1.0f, 0.2f);
    drawBoxTex(5.0f, 2.0f, 7.0f, 1.2f, 0.6f);
    drawBoxTex(5.6f, 0.35f, 7.6f, 1.2f, 0.2f);
    drawBoxTex(4.0f, 0.9f, 5.0f, 1.0f, 0.4f);

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glColor3f(0.40f, 0.38f, 0.35f);
    glPushMatrix(); glTranslatef(0.0f, -6.0f, 4.01f); drawArch(5.0f, 1.2f, 4.0f, 24, 0.2f); glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawPier(float x, float y, float z, float w, float h, float d)
{
    glPushMatrix(); glTranslatef(x, y, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexBase);
    glColor3f(1, 1, 1);
    drawBoxTex(w, h, d, 1.8f, 1.8f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawRoadFixed(float length, float width, float thick)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexRoad);
    glColor3f(1, 1, 1);
    drawBoxTex(length, thick, width, length * 0.15f, width * 0.15f);
    glDisable(GL_TEXTURE_2D);

    drawDashedCenterLine(length, 0.0f, +thick * 0.5f, 0.8f, 0.5f);
}

void drawBasculeLeaf(bool leftSide, float angleDeg, float hingeX, float length, float width, float thick)
{
    float dir = leftSide ? -1.0f : +1.0f;

    glPushMatrix();
    glTranslatef(hingeX, 0.0f, 0.0f);
    glRotatef(-dir * angleDeg, 0.0f, 0.0f, 1.0f);
    glTranslatef(-dir * (length * 0.5f), 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexRoad);
    glColor3f(1, 1, 1);
    drawBoxTex(length, thick, width, length * 0.15f, width * 0.15f);
    glDisable(GL_TEXTURE_2D);

    drawDashedCenterLine(length, 0.0f, +thick * 0.5f, 0.8f, 0.5f);
    drawDeckGirders(-length * 0.5f, +length * 0.5f, +thick * 0.5f, width);

    glPopMatrix();
}

void drawWater(float x, float z, float w, float d)
{
    const float y = -9.95f;

    GLboolean wasCull = glIsEnabled(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);              // avoid hiding the top face

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexWater);
    glColor3f(1, 1, 1);

    float x0 = x - w * 0.5f, x1 = x + w * 0.5f;
    float z0 = z - d * 0.5f, z1 = z + d * 0.5f;

    glBegin(GL_TRIANGLES);
    // CCW when viewed from above (+Y normal)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y, z0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y, z1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y, z1);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y, z0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y, z1);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y, z0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    if (wasCull) glEnable(GL_CULL_FACE);
}

void drawLampPost()
{
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.18f, 0.18f, 0.20f);
    glPushMatrix(); drawBox(0.12f, 3.2f, 0.12f); glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.95f, 0.85f);
    glPushMatrix(); glTranslatef(0.0f, 1.8f, 0.0f); drawBox(0.30f, 0.30f, 0.30f); glPopMatrix();
    glEnable(GL_LIGHTING);
}

void placeLamps(float x0, float x1, float deckY, float z)
{
    for (float x = x0; x <= x1 + 0.001f; x += 4.0f) {
        glPushMatrix();
        glTranslatef(x, deckY + 1.6f, z);
        drawLampPost();
        glPopMatrix();
    }
}

void drawTowerDecor()
{
    drawTower();

    glDisable(GL_TEXTURE_2D);
    glColor3f(0.62f, 0.58f, 0.53f);
    for (int i = 0; i < 3; ++i) {
        float off = -2.0f + i * 2.0f;
        glPushMatrix(); glTranslatef(off, 0.0f, 4.05f);  drawBox(0.35f, 24.0f, 0.2f); glPopMatrix();
        glPushMatrix(); glTranslatef(off, 0.0f, -4.05f); drawBox(0.35f, 24.0f, 0.2f); glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexTop);
    glColor3f(1, 1, 1);
    glPushMatrix(); glTranslatef(0, 12.0f, 0);  drawBoxTex(7.2f, 2.6f, 9.2f, 1.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 14.1f, 0); drawBoxTex(7.6f, 0.3f, 9.6f, 1.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 14.5f, 0); drawBoxTex(5.0f, 2.0f, 7.0f, 1.2f, 0.6f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 15.7f, 0); drawBoxTex(5.6f, 0.35f, 7.6f, 1.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 16.25f, 0);drawBoxTex(4.0f, 0.9f, 5.0f, 1.0f, 0.4f); glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glColor3f(0.40f, 0.38f, 0.35f);
    glPushMatrix(); glTranslatef(0.0f, -6.0f, 4.01f); drawArch(5.0f, 1.2f, 4.0f, 24, 0.2f); glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawBridge()
{
    if (gShowGrid) { glPushMatrix(); glTranslatef(0, -9.89f, 0); drawGridXZ(80.0f, 80.0f, 4.0f); glPopMatrix(); }

    drawWater(0, 0, 160.0f, 80.0f);

    drawPier(-18.0f, -4.0f, 0.0f, 10.0f, 12.0f, 12.0f);
    drawPier(18.0f, -4.0f, 0.0f, 10.0f, 12.0f, 12.0f);

    glPushMatrix(); glTranslatef(-18.0f, 2.0f, 0.0f); drawTowerDecor(); glPopMatrix();
    glPushMatrix(); glTranslatef(18.0f, 2.0f, 0.0f); drawTowerDecor(); glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexTop);
    glColor3f(1, 1, 1);
    glPushMatrix(); glTranslatef(0, 14.5f, 0);
    drawBoxTex(28.0f, 1.5f, 6.0f, 2.0f, 0.6f);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix(); glTranslatef(-12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix();

    glPushMatrix(); glTranslatef(-6.0f, -0.5f, 0.0f); drawExpansionJoint(6.0f, 0.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(6.0f, -0.5f, 0.0f); drawExpansionJoint(6.0f, 0.0f); glPopMatrix();

    glPushMatrix(); glTranslatef(0, -1, 0);
    drawBasculeLeaf(true, gBascule, -6.0f, 6.0f, 6.0f, 1.0f);
    drawBasculeLeaf(false, gBascule, 6.0f, 6.0f, 6.0f, 1.0f);
    glPopMatrix();

    float deckTopY = -0.5f;
    drawDeckGirders(-18.0f, -6.0f, deckTopY, 6.0f);
    drawDeckGirders(6.0f, 18.0f, deckTopY, 6.0f);

    placeLamps(-18.0f, -6.0f, deckTopY, 3.6f);
    placeLamps(6.0f, 18.0f, deckTopY, 3.6f);
    placeLamps(-18.0f, -6.0f, deckTopY, -3.6f);
    placeLamps(6.0f, 18.0f, deckTopY, -3.6f);
}

void applyCameraAndProjection(int vpX, int vpY, int vpW, int vpH, bool perspective)
{
    glViewport(vpX, vpY, vpW, vpH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (vpH == 0) ? 1.0f : (float)vpW / (float)vpH;

    if (perspective) {
        float zNear = 0.5f, zFar = 500.0f;
        float t = zNear * tanf(deg2rad(55.0f * 0.5f));
        float r = t * aspect;
        glFrustum(-r, r, -t, t, zNear, zFar);
    }
    else {
        glOrtho(-30.0f * aspect, 30.0f * aspect, -20.0f, 20.0f, -500.0f, 500.0f);
    }

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
    case WM_SIZE: gClient.right = LOWORD(lParam); gClient.bottom = HIWORD(lParam); return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;

    case WM_LBUTTONDOWN: gLDragging = true; gLastMouse.x = LOWORD(lParam); gLastMouse.y = HIWORD(lParam); SetCapture(hWnd); return 0;
    case WM_LBUTTONUP:   gLDragging = false; ReleaseCapture(); return 0;
    case WM_MOUSEMOVE:
        if (gLDragging) {
            int x = LOWORD(lParam), y = HIWORD(lParam);
            int dx = x - gLastMouse.x, dy = y - gLastMouse.y;
            gYaw += dx * 0.4f; gPitch += dy * 0.4f;
            if (gPitch > 85.0f) gPitch = 85.0f; if (gPitch < -85.0f) gPitch = -85.0f;
            gLastMouse.x = x; gLastMouse.y = y;
        } return 0;
    case WM_MOUSEWHEEL: gDist += (GET_WHEEL_DELTA_WPARAM(wParam) > 0) ? -2.0f : 2.0f; if (gDist < 8.0f) gDist = 8.0f; return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE: PostQuitMessage(0); break;
        case 'P': gPerspective = true; break;
        case 'O': gPerspective = false; break;
        case 'V': gSplitViewport = !gSplitViewport; break;
        case 'A': gYaw -= 3.0f; break;
        case 'D': gYaw += 3.0f; break;
        case 'Q': gPitch += 3.0f; if (gPitch > 85) gPitch = 85; break;
        case 'E': gPitch -= 3.0f; if (gPitch < -85) gPitch = -85; break;
        case 'W': gDist -= 2.0f; if (gDist < 8.0f) gDist = 8.0f; break;
        case 'S': gDist += 2.0f; break;
        case 'G': gShowGrid = !gShowGrid; break;
        case ' ': gAnim = !gAnim; break;
        case '[': gBascule -= 3.0f; if (gBascule < 0.0f) gBascule = 0.0f; break;
        case ']': gBascule += 3.0f; if (gBascule > 70.0f) gBascule = 70.0f; break;
        case 'R':
            gPerspective = true; gSplitViewport = false;
            gYaw = -25.0f; gPitch = 20.0f; gDist = 42.0f;
            gBascule = 0.0f; gAnim = true; gBasculeDir = +1.0f; break;
        } return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd{}; pfd.cAlphaBits = 8; pfd.cColorBits = 32; pfd.cDepthBits = 24; pfd.cStencilBits = 0;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iLayerType = PFD_MAIN_PLANE; pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); pfd.nVersion = 1;
    int n = ChoosePixelFormat(hdc, &pfd); return SetPixelFormat(hdc, n, &pfd) ? true : false;
}

void initGLStyling()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH); glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_CULL_FACE); glCullFace(GL_BACK); glFrontFace(GL_CCW);
    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL); glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat ambient[] = { 0.18f, 0.18f, 0.20f, 1.0f };
    GLfloat diffuse[] = { 0.85f, 0.80f, 0.75f, 1.0f };
    GLfloat specular[] = { 0.18f, 0.18f, 0.18f, 1.0f };
    GLfloat pos[] = { -0.4f, 0.8f, 0.45f, 0.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_FOG); glFogi(GL_FOG_MODE, GL_EXP2);
    GLfloat fogColor[4] = { 0.78f, 0.90f, 1.00f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor); glFogf(GL_FOG_DENSITY, 0.006f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void drawGridXZ(float halfX, float halfZ, float step)
{
    glDisable(GL_LIGHTING);
    glColor4f(1, 1, 1, 0.08f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (float x = -halfX; x <= halfX; x += step) { glVertex3f(x, 0, -halfZ); glVertex3f(x, 0, halfZ); }
    for (float z = -halfZ; z <= halfZ; z += step) { glVertex3f(-halfX, 0, z); glVertex3f(halfX, 0, z); }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawBackground()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);  glPushMatrix(); glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexBackground);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1, -1);
    glTexCoord2f(1, 0); glVertex2f(1, -1);
    glTexCoord2f(1, 1); glVertex2f(1, 1);
    glTexCoord2f(0, 1); glVertex2f(-1, 1);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

// ---------------- Display ----------------
void display()
{
    static DWORD t0 = GetTickCount();
    DWORD tNow = GetTickCount();
    gTime = (tNow - t0) * 0.001f;

    if (gAnim) {
        gBascule += gBasculeDir * 0.8f;
        if (gBascule > 70.0f) { gBascule = 70.0f; gBasculeDir = -1.0f; }
        if (gBascule < 0.0f) { gBascule = 0.0f;  gBasculeDir = +1.0f; }
    }

    glClearColor(0.65f, 0.80f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBackground();

    int W = gClient.right, H = gClient.bottom;
    if (W <= 0 || H <= 0) { W = 800; H = 600; }

    if (!gSplitViewport) {
        applyCameraAndProjection(0, 0, W, H, gPerspective);
        drawBridge();
    }
    else {
        applyCameraAndProjection(0, 0, W / 2, H, true);  drawBridge();
        applyCameraAndProjection(W / 2, 0, W - W / 2, H, false); drawBridge();
    }

    glFlush();
}

// ---------------- WinMain ----------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSEX wc{}; wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = WINDOW_TITLE;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    if (!RegisterClassEx(&wc)) return false;

    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, wc.hInstance, NULL);

    HDC hdc = GetDC(hWnd);
    initPixelFormat(hdc);
    HGLRC hglrc = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    initGLStyling();
    initTextures();

    ShowWindow(hWnd, nCmdShow);

    MSG msg{};
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
