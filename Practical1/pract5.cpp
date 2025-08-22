//#include <Windows.h>
//#include <gl/GL.h>
//#include <math.h>
//
//#pragma comment (lib, "OpenGL32.lib")
//
//#define WINDOW_TITLE "OpenGL Window"
//
//static bool  gPerspective = true;
//static bool  gSplitViewport = false;
//
//static bool  gShowGrid = false;   // toggle with 'G'
//static float gTime = 0.0f;    // seconds since start (for water anim)
//
//static float gYaw = -25.0f;     // orbit yaw (deg)
//static float gPitch = 20.0f;    // orbit pitch (deg)
//static float gDist = 42.0f;     // camera distance
//
//static float gBascule = 0.0f;   // 0..70 deg
//static bool  gAnim = true;      // animate by default
//static float gBasculeDir = +1.0f;
//
//static RECT  gClient = { 0,0,800,600 };
//
//// mouse interaction
//static bool  gLDragging = false;
//static POINT gLastMouse = { 0,0 };
//
//static inline float deg2rad(float a) { return a * 3.1415926535f / 180.0f; }
//
//void initGLStyling();
//void drawGridXZ(float halfX, float halfZ, float step);
//
//// new features
//static inline float cableY(float t, float yBase, float sag);
//void drawHangers(float yBase, float x0, float x1, float sag, float z, float deckY, float spacing);
//void drawBeamBox(float x0, float x1, float y0, float y1, float z0, float z1);
//void drawDeckGirders(float x0, float x1, float deckY, float deckWidth);
//void drawDashedCenterLine(float len, float z, float y, float dash, float gap);
//void drawExpansionJoint(float width, float y);
//void drawLampPost();
//void placeLamps(float x0, float x1, float deckY, float z);
//void drawTowerDecor();
//void drawTower();
//void drawPier(float x, float y, float z, float w, float h, float d);
//void drawWater(float x, float z, float w, float d);
//
//// ---------------- Projection ----------------
//void setPerspective(float fovY_deg, float aspect, float zNear, float zFar)
//{
//    float top = zNear * tanf(deg2rad(fovY_deg * 0.5f));
//    float bottom = -top;
//    float right = top * aspect;
//    float left = -right;
//    glFrustum(left, right, bottom, top, zNear, zFar);
//}
//
//// ---------------- Geometry ----------------
//void drawBox(float w, float h, float d)
//{
//    float x = w * 0.5f, y = h * 0.5f, z = d * 0.5f;
//    glBegin(GL_QUADS);
//    // +X
//    glNormal3f(1, 0, 0);
//    glVertex3f(x, -y, -z); glVertex3f(x, y, -z); glVertex3f(x, y, z); glVertex3f(x, -y, z);
//    // -X
//    glNormal3f(-1, 0, 0);
//    glVertex3f(-x, -y, z); glVertex3f(-x, y, z); glVertex3f(-x, y, -z); glVertex3f(-x, -y, -z);
//    // +Y
//    glNormal3f(0, 1, 0);
//    glVertex3f(-x, y, -z); glVertex3f(-x, y, z); glVertex3f(x, y, z); glVertex3f(x, y, -z);
//    // -Y
//    glNormal3f(0, -1, 0);
//    glVertex3f(-x, -y, z); glVertex3f(-x, -y, -z); glVertex3f(x, -y, -z); glVertex3f(x, -y, z);
//    // +Z
//    glNormal3f(0, 0, 1);
//    glVertex3f(-x, -y, z); glVertex3f(x, -y, z); glVertex3f(x, y, z); glVertex3f(-x, y, z);
//    // -Z
//    glNormal3f(0, 0, -1);
//    glVertex3f(x, -y, -z); glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z); glVertex3f(x, y, -z);
//    glEnd();
//}
//
//// XZ arch strip (for tower openings)
//void drawArch(float radius, float thickness, float span, int steps, float depth)
//{
//    float z0 = -depth * 0.5f, z1 = depth * 0.5f;
//    glBegin(GL_QUAD_STRIP);
//    for (int i = 0; i <= steps; i++) {
//        float t = (float)i / steps;
//        float x = -span * 0.5f + t * span;
//        float a = acosf(fminf(1.0f, fmaxf(-1.0f, x / radius)));
//        float yOuter = radius * sinf(a);
//        float yInner = yOuter - thickness;
//        glVertex3f(x, yOuter, z0); glVertex3f(x, yInner, z0);
//        glVertex3f(x, yOuter, z1); glVertex3f(x, yInner, z1);
//    }
//    glEnd();
//}
//
//// ---------------- NEW DETAILING ----------------
//static inline float cableY(float t, float yBase, float sag) {
//    float m = t - 0.5f;
//    return yBase - sag * (1.0f - 4.0f * m * m);
//}
//
//void drawHangers(float yBase, float x0, float x1, float sag, float z, float deckY, float spacing)
//{
//    glDisable(GL_LIGHTING);
//    glLineWidth(3.0f);
//    glColor4f(0.13f, 0.55f, 0.78f, 0.95f);
//
//    glBegin(GL_LINES);
//    for (float x = x0; x <= x1 + 0.001f; x += spacing) {
//        float t = (x - x0) / (x1 - x0);
//        float y = cableY(t, yBase, sag);
//        glVertex3f(x, y, z);
//        glVertex3f(x, deckY, z);
//    }
//    glEnd();
//
//    glEnable(GL_LIGHTING);
//}
//
//void drawBeamBox(float x0, float x1, float y0, float y1, float z0, float z1)
//{
//    glPushMatrix();
//    glTranslatef((x0 + x1) * 0.5f, (y0 + y1) * 0.5f, (z0 + z1) * 0.5f);
//    drawBox(fabsf(x1 - x0), fabsf(y1 - y0), fabsf(z1 - z0));
//    glPopMatrix();
//}
//
//void drawDeckGirders(float x0, float x1, float deckY, float deckWidth)
//{
//    float girderH = 1.2f;
//    float girderT = 0.20f;
//    float zIn = deckWidth * 0.52f;
//    float zOut = deckWidth * 0.60f;
//
//    // longitudinal side girders
//    glColor3f(0.20f, 0.24f, 0.28f);
//    drawBeamBox(x0, x1, deckY, deckY + girderH, zIn, zOut);
//    drawBeamBox(x0, x1, deckY, deckY + girderH, -zOut, -zIn);
//
//    // posts every bay
//    float step = 3.0f;
//    for (float x = x0; x <= x1 + 0.001f; x += step) {
//        drawBeamBox(x - 0.10f, x + 0.10f, deckY, deckY + girderH, zIn, zOut);
//        drawBeamBox(x - 0.10f, x + 0.10f, deckY, deckY + girderH, -zOut, -zIn);
//    }
//
//    // diagonals (hinted)
//    glColor3f(0.16f, 0.18f, 0.21f);
//    for (float x = x0; x < x1 - step; x += step * 2.0f) {
//        // small end caps
//        drawBeamBox(x, x + 0.15f, deckY, deckY + girderH, zIn, zOut);
//        drawBeamBox(x + step - 0.15f, x + step, deckY, deckY + girderH, zIn, zOut);
//
//        // diagonals left/right (approximation with thin boxes)
//        drawBeamBox(x, x + 0.20f, deckY, deckY + girderH, zIn, zIn + girderT);
//        drawBeamBox(x + step - 0.20f, x + step, deckY, deckY + girderH, zOut - girderT, zOut);
//
//        drawBeamBox(x, x + 0.20f, deckY, deckY + girderH, -zOut, -zOut + girderT);
//        drawBeamBox(x + step - 0.20f, x + step, deckY, deckY + girderH, -zIn - girderT, -zIn);
//    }
//}
//
//void drawDashedCenterLine(float len, float z, float y, float dash, float gap)
//{
//    glDisable(GL_LIGHTING);
//    glBegin(GL_QUADS);
//    glColor3f(0.95f, 0.95f, 0.70f);
//    float halfW = 0.06f;
//    float x = -len * 0.5f;
//    while (x < len * 0.5f) {
//        float x0 = x, x1 = fminf(x + dash, len * 0.5f);
//        glVertex3f(x0, y + 0.01f, z - halfW); glVertex3f(x1, y + 0.01f, z - halfW);
//        glVertex3f(x1, y + 0.01f, z + halfW); glVertex3f(x0, y + 0.01f, z + halfW);
//        x += dash + gap;
//    }
//    glEnd();
//    glEnable(GL_LIGHTING);
//}
//
//void drawExpansionJoint(float width, float y)
//{
//    glDisable(GL_LIGHTING);
//    glColor3f(0.05f, 0.05f, 0.06f);
//    glBegin(GL_QUADS);
//    float t = 0.06f;
//    glVertex3f(-t, y + 0.005f, -width * 0.5f); glVertex3f(+t, y + 0.005f, -width * 0.5f);
//    glVertex3f(+t, y + 0.005f, width * 0.5f); glVertex3f(-t, y + 0.005f, width * 0.5f);
//    glEnd();
//    glEnable(GL_LIGHTING);
//}
//
//void drawTowerDecor()
//{
//    // reuse same palette as drawTower
//    const float STONE_L[3] = { 0.88f, 0.85f, 0.79f };
//    const float STONE_M[3] = { 0.78f, 0.74f, 0.68f };
//    const float STONE_D[3] = { 0.62f, 0.58f, 0.53f };
//    const float BRONZE[3] = { 0.35f, 0.30f, 0.23f };
//
//    drawTower(); // build the base tower first
//
//    // cornice ring (slightly wider than capital)
//    glPushMatrix(); glTranslatef(0, 13.2f, 0);
//    glColor3fv(STONE_M);          drawBox(8.2f, 0.6f, 10.2f);
//    glPopMatrix();
//
//    // thin highlight line on the ring
//    glPushMatrix(); glTranslatef(0, 13.55f, 0);
//    glColor3fv(BRONZE);           drawBox(8.4f, 0.15f, 10.4f);
//    glPopMatrix();
//
//    // vertical pilasters again (front/back), lighter than grooves
//    glColor3fv(STONE_D);
//    for (int i = 0; i < 3; ++i) {
//        float off = -2.0f + i * 2.0f;
//        glPushMatrix(); glTranslatef(off, 0.0f, 4.1f); drawBox(0.40f, 24.0f, 0.2f); glPopMatrix();
//        glPushMatrix(); glTranslatef(off, 0.0f, -4.1f); drawBox(0.40f, 24.0f, 0.2f); glPopMatrix();
//    }
//}
//
//void drawLampPost()
//{
//    glColor3f(0.18f, 0.18f, 0.20f);
//    glPushMatrix(); drawBox(0.12f, 3.2f, 0.12f); glPopMatrix();
//
//    glDisable(GL_LIGHTING);
//    glColor4f(1.0f, 0.95f, 0.85f, 1.0f);
//    glPushMatrix(); glTranslatef(0.0f, 1.8f, 0.0f); drawBox(0.30f, 0.30f, 0.30f); glPopMatrix();
//    glEnable(GL_LIGHTING);
//}
//
//void placeLamps(float x0, float x1, float deckY, float z)
//{
//    for (float x = x0; x <= x1 + 0.001f; x += 4.0f) {
//        glPushMatrix();
//        glTranslatef(x, deckY + 1.6f, z);
//        drawLampPost();
//        glPopMatrix();
//    }
//}
//
//void drawTower()
//{
//    // ===== Palette =====
//    const float STONE_L[3] = { 0.88f, 0.85f, 0.79f };   // light stone
//    const float STONE_M[3] = { 0.78f, 0.74f, 0.68f };   // mid stone
//    const float STONE_D[3] = { 0.62f, 0.58f, 0.53f };   // dark stone (grooves)
//    const float BRONZE[3] = { 0.35f, 0.30f, 0.23f };   // bronze trim
//    const float COPPER[3] = { 0.34f, 0.62f, 0.54f };   // patina copper
//
//    // --- plinth shadow band (subtle color break near base) ---
//    glPushMatrix(); glTranslatef(0.0f, -10.8f, 0.0f);
//    glColor3fv(STONE_D);          drawBox(6.6f, 1.2f, 8.6f);
//    glPopMatrix();
//
//    // --- main shaft ---
//    glColor3fv(STONE_L);          drawBox(6.0f, 24.0f, 8.0f);
//
//    // --- vertical grooves (front & back) for depth ---
//    glColor3fv(STONE_D);
//    for (int i = 0; i < 3; ++i) {
//        float off = -2.0f + i * 2.0f;   // -2, 0, +2
//        glPushMatrix(); glTranslatef(off, 0.0f, 4.05f); drawBox(0.35f, 24.0f, 0.2f); glPopMatrix();
//        glPushMatrix(); glTranslatef(off, 0.0f, -4.05f); drawBox(0.35f, 24.0f, 0.2f); glPopMatrix();
//    }
//
//    // --- capital band (stone) ---
//    glPushMatrix(); glTranslatef(0, 12, 0);
//    glColor3fv(STONE_M);          drawBox(7.2f, 2.6f, 9.2f);
//    glPopMatrix();
//
//    // --- bronze cornice line under the cap ---
//    glPushMatrix(); glTranslatef(0, 14.1f, 0);
//    glColor3fv(BRONZE);           drawBox(7.6f, 0.3f, 9.6f);
//    glPopMatrix();
//
//    // --- stone cap ---
//    glPushMatrix(); glTranslatef(0, 14.5f, 0);
//    glColor3fv(STONE_L);          drawBox(5.0f, 2.0f, 7.0f);
//    glPopMatrix();
//
//    // --- thin copper coping above the cap (color pop!) ---
//    glPushMatrix(); glTranslatef(0, 15.7f, 0);
//    glColor3fv(COPPER);           drawBox(5.6f, 0.35f, 7.6f);
//    glPopMatrix();
//
//    // --- small bronze top block to finish the silhouette ---
//    glPushMatrix(); glTranslatef(0, 16.25f, 0);
//    glColor3fv(BRONZE);           drawBox(4.0f, 0.9f, 5.0f);
//    glPopMatrix();
//
//    // --- decorative arch (unchanged) ---
//    glDisable(GL_LIGHTING);
//    glColor3f(0.40f, 0.38f, 0.35f);
//    glPushMatrix(); glTranslatef(0.0f, -6.0f, 4.01f); drawArch(5.0f, 1.2f, 4.0f, 24, 0.2f); glPopMatrix();
//    glEnable(GL_LIGHTING);
//}
//
//void drawPier(float x, float y, float z, float w, float h, float d)
//{
//    glPushMatrix(); glTranslatef(x, y, z);
//    glColor3f(0.74f, 0.71f, 0.66f);  // body (lighter stone)
//    drawBox(w, h, d);
//    glColor3f(0.68f, 0.65f, 0.60f);  // cap
//    drawBox(w * 1.1f, 0.4f, d * 1.1f);
//    glPopMatrix();
//}
//
//void drawWater(float x, float z, float w, float d)
//{
//    // animated ripples using a light mesh
//    const int nx = 48, nz = 24; // keep modest for perf
//    const float amp = 0.10f;    // wave height
//    const float y0 = -9.95f;
//
//    glDisable(GL_LIGHTING);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    glColor4f(0.30f, 0.65f, 0.90f, 0.90f);
//
//    float x0 = x - w * 0.5f, z0 = z - d * 0.5f;
//    float dx = w / nx, dz = d / nz;
//
//    for (int j = 0; j < nz; ++j) {
//        float zA = z0 + j * dz;
//        float zB = z0 + (j + 1) * dz;
//
//        glBegin(GL_TRIANGLE_STRIP);
//        for (int i = 0; i <= nx; ++i) {
//            float xx = x0 + i * dx;
//            float yA = y0 + sinf(xx * 0.25f + gTime * 0.8f) * amp + cosf(zA * 0.30f + gTime * 0.6f) * amp * 0.5f;
//            float yB = y0 + sinf(xx * 0.25f + gTime * 0.8f) * amp + cosf(zB * 0.30f + gTime * 0.6f) * amp * 0.5f;
//
//            glVertex3f(xx, yA, zA);
//            glVertex3f(xx, yB, zB);
//        }
//        glEnd();
//    }
//
//    glDisable(GL_BLEND);
//    glEnable(GL_LIGHTING);
//}
//
//// road pieces
//void drawRoadFixed(float length, float width, float thick)
//{
//    glColor3f(0.23f, 0.28f, 0.32f);
//    drawBox(length, thick, width);
//    glColor3f(0.20f, 0.55f, 0.75f);
//
//    drawDashedCenterLine(length, 0.0f, +thick * 0.5f, 0.8f, 0.5f);
//}
//
//void drawBasculeLeaf(bool leftSide, float angleDeg,
//    float hingeX, float length, float width, float thick)
//{
//    float dir = leftSide ? -1.0f : +1.0f;
//
//    glPushMatrix();
//    glTranslatef(hingeX, 0.0f, 0.0f);              // move to hinge position
//    glRotatef(-dir * angleDeg, 0.0f, 0.0f, 1.0f);  // rotate around hinge
//    glTranslatef(-dir * (length * 0.5f), 0.0f, 0.0f); // place box so inner end sits at hinge
//
//    // deck
//    glColor3f(0.32f, 0.35f, 0.39f);
//    drawBox(length, thick, width);
//
//    // (rails removed)
//
//    // lane markings for the leaf
//    drawDashedCenterLine(length, 0.0f, +thick * 0.5f, 0.8f, 0.5f);
//
//    // stiffening girders for the leaf (local space)
//    drawDeckGirders(-length * 0.5f, +length * 0.5f, +thick * 0.5f, width);
//
//    glPopMatrix();
//}
//
//void drawBridge()
//{
//    if (gShowGrid) {
//        glPushMatrix();
//        glTranslatef(0, -9.89f, 0);
//        drawGridXZ(80.0f, 80.0f, 4.0f);
//        glPopMatrix();
//    }
//
//    drawWater(0, 0, 160.0f, 80.0f);  // wider so it fills the view
//
//    // PIERS sitting in the water
//    drawPier(-18.0f, -4.0f, 0.0f, 10.0f, 12.0f, 12.0f);
//    drawPier(18.0f, -4.0f, 0.0f, 10.0f, 12.0f, 12.0f);
//
//    // towers with decor
//    glPushMatrix(); glTranslatef(-18.0f, 2.0f, 0.0f); drawTowerDecor(); glPopMatrix();
//    glPushMatrix(); glTranslatef(18.0f, 2.0f, 0.0f); drawTowerDecor(); glPopMatrix();
//
//    // top cross member
//    glPushMatrix(); glTranslatef(0, 14.5f, 0);
//    glColor3f(0.70f, 0.74f, 0.78f); drawBox(28.0f, 1.5f, 6.0f);
//    glColor3f(0.20f, 0.55f, 0.75f); drawBox(28.5f, 0.3f, 6.6f);
//    glPopMatrix();
//
//    // fixed road sections
//    glPushMatrix(); glTranslatef(-12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix(); // -18..-6
//    glPushMatrix(); glTranslatef(12.0f, -1.0f, 0.0f); drawRoadFixed(12.0f, 6.0f, 1.0f); glPopMatrix();  //  +6..+18
//
//    // expansion joints at hinge interfaces (world space)
//    glPushMatrix(); glTranslatef(-6.0f, -0.5f, 0.0f); drawExpansionJoint(6.0f, 0.0f); glPopMatrix();
//    glPushMatrix(); glTranslatef(6.0f, -0.5f, 0.0f); drawExpansionJoint(6.0f, 0.0f); glPopMatrix();
//
//    // bascule leaves
//    glPushMatrix(); glTranslatef(0, -1, 0);
//    drawBasculeLeaf(true, gBascule, -6.0f, 6.0f, 6.0f, 1.0f);
//    drawBasculeLeaf(false, gBascule, 6.0f, 6.0f, 6.0f, 1.0f);
//    glPopMatrix();
//
//    // hangers from cables to deck
//    float deckTopY = -0.5f; // fixed/bascule top in world space when closed
//
//    // deck girders for fixed spans (world space)
//    drawDeckGirders(-18.0f, -6.0f, deckTopY, 6.0f);
//    drawDeckGirders(6.0f, 18.0f, deckTopY, 6.0f);
//
//    // lamps
//    placeLamps(-18.0f, -6.0f, deckTopY, 3.6f);
//    placeLamps(6.0f, 18.0f, deckTopY, 3.6f);
//    placeLamps(-18.0f, -6.0f, deckTopY, -3.6f);
//    placeLamps(6.0f, 18.0f, deckTopY, -3.6f);
//}
//
//// ---------------- Camera/Projection ----------------
//void applyCameraAndProjection(int vpX, int vpY, int vpW, int vpH, bool perspective)
//{
//    glViewport(vpX, vpY, vpW, vpH);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    float aspect = (vpH == 0) ? 1.0f : (float)vpW / (float)vpH;
//
//    if (perspective) setPerspective(55.0f, aspect, 0.5f, 500.0f); // slightly wider FOV for presence
//    else             glOrtho(-30.0f * aspect, 30.0f * aspect, -20.0f, 20.0f, -500.0f, 500.0f);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0, 0, -gDist);
//    glRotatef(gPitch, 1, 0, 0);
//    glRotatef(gYaw, 0, 1, 0);
//    glTranslatef(0, -3, 0);
//}
//
//// ---------------- Win32 WndProc ----------------
//LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    switch (msg)
//    {
//    case WM_SIZE:
//        gClient.right = LOWORD(lParam);
//        gClient.bottom = HIWORD(lParam);
//        return 0;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//
//    case WM_LBUTTONDOWN:
//        gLDragging = true;
//        gLastMouse.x = LOWORD(lParam);
//        gLastMouse.y = HIWORD(lParam);
//        SetCapture(hWnd);
//        return 0;
//
//    case WM_LBUTTONUP:
//        gLDragging = false;
//        ReleaseCapture();
//        return 0;
//
//    case WM_MOUSEMOVE:
//        if (gLDragging) {
//            int x = LOWORD(lParam), y = HIWORD(lParam);
//            int dx = x - gLastMouse.x, dy = y - gLastMouse.y;
//            gYaw += dx * 0.4f;
//            gPitch += dy * 0.4f;
//            if (gPitch > 85.0f) gPitch = 85.0f;
//            if (gPitch < -85.0f) gPitch = -85.0f;
//            gLastMouse.x = x; gLastMouse.y = y;
//        }
//        return 0;
//
//    case WM_MOUSEWHEEL:
//        gDist += (GET_WHEEL_DELTA_WPARAM(wParam) > 0) ? -2.0f : 2.0f;
//        if (gDist < 8.0f) gDist = 8.0f;
//        return 0;
//
//    case WM_KEYDOWN:
//        switch (wParam)
//        {
//        case VK_ESCAPE: PostQuitMessage(0); break;
//        case 'P': gPerspective = true; break;
//        case 'O': gPerspective = false; break;
//        case 'V': gSplitViewport = !gSplitViewport; break;
//
//            // keyboard camera
//        case 'A': gYaw -= 3.0f; break;
//        case 'D': gYaw += 3.0f; break;
//        case 'Q': gPitch += 3.0f; if (gPitch > 85) gPitch = 85; break;
//        case 'E': gPitch -= 3.0f; if (gPitch < -85) gPitch = -85; break;
//        case 'W': gDist -= 2.0f; if (gDist < 8.0f) gDist = 8.0f; break;
//        case 'S': gDist += 2.0f; break;
//        case 'G': gShowGrid = !gShowGrid; break;
//
//            // bascule animation / manual
//        case ' ': gAnim = !gAnim; break;
//        case '[': gBascule -= 3.0f; if (gBascule < 0.0f) gBascule = 0.0f; break;
//        case ']': gBascule += 3.0f; if (gBascule > 70.0f) gBascule = 70.0f; break;
//
//        case 'R':
//            gPerspective = true; gSplitViewport = false;
//            gYaw = -25.0f; gPitch = 20.0f; gDist = 42.0f;
//            gBascule = 0.0f; gAnim = true; gBasculeDir = +1.0f;
//            break;
//        }
//        return 0;
//    }
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//// ---------------- Pixel Format ----------------
//bool initPixelFormat(HDC hdc)
//{
//    PIXELFORMATDESCRIPTOR pfd;
//    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
//
//    pfd.cAlphaBits = 8;
//    pfd.cColorBits = 32;
//    pfd.cDepthBits = 24;
//    pfd.cStencilBits = 0;
//
//    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
//
//    pfd.iLayerType = PFD_MAIN_PLANE;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//    pfd.nVersion = 1;
//
//    int n = ChoosePixelFormat(hdc, &pfd);
//    if (SetPixelFormat(hdc, n, &pfd))
//        return true;
//    else
//        return false;
//}
//
//// ---------------- Visual styling init ----------------
//void initGLStyling()
//{
//    glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_SMOOTH);
//
//    // AA lines for cables
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//
//    // Face culling for consistent winding
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);
//
//    // Basic lighting; glColor controls material (ambient+diffuse)
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//    GLfloat ambient[] = { 0.18f, 0.18f, 0.20f, 1.0f };
//    GLfloat diffuse[] = { 0.85f, 0.80f, 0.75f, 1.0f };
//    GLfloat specular[] = { 0.18f, 0.18f, 0.18f, 1.0f }; // a touch more specular for steel pop
//    GLfloat pos[] = { -0.4f, 0.8f, 0.45f, 0.0f }; // directional
//
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, pos);
//
//    // Subtle fog (depth cue)
//    glEnable(GL_FOG);
//    glFogi(GL_FOG_MODE, GL_EXP2);
//    GLfloat fogColor[4] = { 0.78f, 0.90f, 1.00f, 1.0f };
//    glFogfv(GL_FOG_COLOR, fogColor);
//    glFogf(GL_FOG_DENSITY, 0.006f);
//    glHint(GL_FOG_HINT, GL_NICEST);
//
//
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//}
//
//// ---------------- Grid helper ----------------
//void drawGridXZ(float halfX, float halfZ, float step)
//{
//    glDisable(GL_LIGHTING);
//    glColor4f(1, 1, 1, 0.08f);
//    glLineWidth(1.0f);
//    glBegin(GL_LINES);
//    for (float x = -halfX; x <= halfX; x += step) {
//        glVertex3f(x, 0, -halfZ); glVertex3f(x, 0, halfZ);
//    }
//    for (float z = -halfZ; z <= halfZ; z += step) {
//        glVertex3f(-halfX, 0, z); glVertex3f(halfX, 0, z);
//    }
//    glEnd();
//    glEnable(GL_LIGHTING);
//}
//
//void drawBackground()
//{
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_LIGHTING);
//
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//
//    glBegin(GL_QUADS);
//    // horizon – lighter
//    glColor3f(0.78f, 0.90f, 1.00f);
//    glVertex2f(-1, -1); glVertex2f(1, -1);
//    // zenith – soft blue
//    glColor3f(0.62f, 0.82f, 0.98f);
//    glVertex2f(1, 1); glVertex2f(-1, 1);
//    glEnd();
//
//    glPopMatrix();
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//
//    glEnable(GL_LIGHTING);
//    glEnable(GL_DEPTH_TEST);
//}
//
//// ---------------- Display ----------------
//void display()
//{
//    static DWORD t0 = GetTickCount();
//    DWORD tNow = GetTickCount();
//    gTime = (tNow - t0) * 0.001f; // seconds
//
//    // animate bascules
//    if (gAnim) {
//        gBascule += gBasculeDir * 0.8f; // speed
//        if (gBascule > 70.0f) { gBascule = 70.0f; gBasculeDir = -1.0f; }
//        if (gBascule < 0.0f) { gBascule = 0.0f; gBasculeDir = +1.0f; }
//    }
//
//    glClearColor(0.65f, 0.80f, 0.95f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    drawBackground();
//
//    int W = gClient.right, H = gClient.bottom;
//    if (W <= 0 || H <= 0) { W = 800; H = 600; }
//
//    if (!gSplitViewport) {
//        applyCameraAndProjection(0, 0, W, H, gPerspective);
//        drawBridge();
//    }
//    else {
//        applyCameraAndProjection(0, 0, W / 2, H, true);
//        drawBridge();
//        applyCameraAndProjection(W / 2, 0, W - W / 2, H, false);
//        drawBridge();
//    }
//
//    glFlush();
//}
//
//// ---------------- WinMain ----------------
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
//{
//    WNDCLASSEX wc;
//    ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.hInstance = GetModuleHandle(NULL);
//    wc.lpfnWndProc = WindowProcedure;
//    wc.lpszClassName = WINDOW_TITLE;
//    wc.style = CS_HREDRAW | CS_VREDRAW;
//
//    if (!RegisterClassEx(&wc)) return false;
//
//    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//        NULL, NULL, wc.hInstance, NULL);
//
//    // Initialize window for OpenGL
//    HDC hdc = GetDC(hWnd);
//    initPixelFormat(hdc);
//
//    HGLRC hglrc = wglCreateContext(hdc);
//    if (!wglMakeCurrent(hdc, hglrc)) return false;
//
//    // visual styling init
//    initGLStyling();
//
//    ShowWindow(hWnd, nCmdShow);
//
//    MSG msg;
//    ZeroMemory(&msg, sizeof(msg));
//
//    while (true)
//    {
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT) break;
//
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//
//        display();
//        SwapBuffers(hdc);
//    }
//
//    UnregisterClass(WINDOW_TITLE, wc.hInstance);
//
//    return true;
//}
