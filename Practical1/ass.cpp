//
//#include <Windows.h>
//#include <Windowsx.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <math.h>
//
//#pragma comment (lib, "OpenGL32.lib")
//#pragma comment (lib, "GLU32.lib")
//
//#define WINDOW_TITLE "GP ASSIGNMENT - BLAST"
//
////Step 1: Variable declaration
//GLuint textureArr[100];	//Texture array
//BITMAP BMP;				//bitmap structure
//HBITMAP hBMP = NULL;	//bitmap handle 
//
////camera
//bool zoomInStatus = true;
//bool zoomOutStatus = true;
//float lastX = 0.0f, lastY = 0.0f;
//float xRotate = 1.0f, yRotate = 1.0f;
//float zoomLevel = -7, zoomAmount = 1;
//
////Ortho
//bool isOrtho = false;
//float ONear = -5, OFar = 8;
//float ptx = 0, pty = 0, ptSpeed = 0.1;	//Translate for projection
//float prx = 0, pry = 0, prSpeed = 1.0;	//Rotate for projection
//float tx = 0, tz = 0, tSpeed = 1.0;			//translate for model view
//float orthoZoom = 11, pNear = 12, pFar = 20;
//
////circle
//float angle = 0;
//float PI = 3.1429;
//float noOfTri = 30;
//float x2 = 0, y2 = 0;
//
//
//double c(double value) {
//	return value / 255;
//}
//
//
////float angle1 = 0, angle2 = 0, angle3 = 0;
////int xx1 = 0, yy1 = 0, zz1 = 0;
////int xx2 = 0, yy2 = 0, zz2 = 0;
////int xx3 = 0, yy3 = 0, zz3 = 0;
//
//
//
//float rightArmXAngle = 0, rightArmZAngle = 0;
//float leftArmXAngle = 0, leftArmZAngle = 0;
//float rightForearmAngle = 0, rightPalmAngleUpDown = 0, rightPalmAngleLeftRight = 0;
//float leftForearmAngle = 0, leftPalmAngleUpDown = 0, leftPalmAngleLeftRight = 0;
//float lowerLegAngle = 0;
//bool handAnimationStatus = false;
//bool rightPalmAngleUpDownStatus = true, leftPalmAngleUpDownStatus = true;
//
////Texture
//int textureNo = 1;
//bool textureStatus = false;
//
//
////Scratching head animation
//float sh1 = 0, sh2 = 0, sh3 = 0, sh4 = 0, sh5 = 0;
//bool scratchBool = true;
//
////Walking animation
//float rotateBody = 0, walkingSpeed = 0;
//float leftLegUp = 0, rightLegUp = 0;
//float leftLLegUp = 0, rightLLegUp = 0;
//bool walkingAnimationStatus = false, leftLegStatus = true;
//bool leftLegUpStatus = false, rightLegUpStatus = true;
//bool leftLLegUpStatus = false, rightLLegUpStatus = true;
//
////Animation
////Wings
//bool wingAnimationStatus = false;
//float wingRot = 0, wingRotSpeed = 1;
////Jaw
//bool jawAnimationStatus = true;
//float jawRot = 0, jawRotSpeed;
////Tail
//bool tailAnimationStatus = false;
//float tailRot = 0, tailRotSpeed = 2;
////Head
//bool headLeftAnimationStatus = true, headRightAnimationStatus = true;
//float headRot = 0, headRotSpeed = 2;
//
////Weapon
//float canonRot = 0, canonRotSpeed;
//float attack, attackLength, powerBall, powerBallSize, attackRadius;
//bool weaponOn = false;
//bool shootOn = false, endShoot = true, startFire = false;
//bool leftShootOn = false, rightShootOn = false;
//
////Lighting
//float lightX = 0, lightY = 5, lightZ = 0;
//float lightSpeed = 0.5;
//
//boolean isLightOn = false;
//boolean lightStatus = true;
//
////Extra
//boolean hpIncreaseStatus = true, hpDecreaseStatus = true;
//float hpAmount = 5, hpAmountDif = 0.3;
//bool skyBoxOn = false;
//
//LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	case WM_MOUSEMOVE:
//		switch (wParam) {
//		case MK_MBUTTON:
//			int xPos = GET_X_LPARAM(lParam);
//			int yPos = GET_Y_LPARAM(lParam);
//			yRotate += xPos - lastX;
//			xRotate += yPos - lastY;
//			lastX = xPos;
//			lastY = yPos;
//			break;
//		}
//		break;
//	case WM_MBUTTONDOWN:
//		lastX = GET_X_LPARAM(lParam);
//		lastY = GET_Y_LPARAM(lParam);
//		break;
//
//	case WM_LBUTTONDOWN:
//		if (zoomInStatus)
//		{
//			zoomLevel += zoomAmount;
//			if (zoomLevel > -5)
//			{
//				zoomInStatus = false;
//			}
//			zoomOutStatus = true;
//		}
//		break;
//	case WM_RBUTTONDOWN:
//		if (zoomOutStatus)
//		{
//			zoomLevel -= zoomAmount;
//			if (zoomLevel < -9)
//			{
//				zoomOutStatus = false;
//			}
//			zoomInStatus = true;
//		}
//		break;
//
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE) PostQuitMessage(0);
//		else if (wParam == 'Q')
//		{
//			wingAnimationStatus = !wingAnimationStatus;
//		}
//		else if (wParam == 'W')
//		{
//			jawAnimationStatus = !jawAnimationStatus;
//			jawRotSpeed = 0.05;
//		}
//		else if (wParam == 'E')
//		{
//			tailAnimationStatus = !tailAnimationStatus;
//		}
//		else if (wParam == 'R')
//		{
//			if (hpIncreaseStatus)
//			{
//				hpAmount += hpAmountDif;
//				if (hpAmount > 9.9)
//				{
//					hpIncreaseStatus = false;
//				}
//				hpDecreaseStatus = true;
//			}
//
//		}
//		else if (wParam == 'T')
//		{
//			if (hpDecreaseStatus)
//			{
//				hpAmount -= hpAmountDif;
//				if (hpAmount < 0.2)
//				{
//					hpDecreaseStatus = false;
//				}
//				hpIncreaseStatus = true;
//			}
//		}
//		else if (wParam == 'Y')
//		{
//			if (headLeftAnimationStatus)
//			{
//				headRot += headRotSpeed;
//				if (headRot > 30)
//				{
//					headLeftAnimationStatus = false;
//				}
//				headRightAnimationStatus = true;
//			}
//
//		}
//		else if (wParam == 'U')
//		{
//			if (headRightAnimationStatus)
//			{
//				headRot -= headRotSpeed;
//				if (headRot < -30)
//				{
//					headRightAnimationStatus = false;
//				}
//				headLeftAnimationStatus = true;
//			}
//		}
//		else if (wParam == '5') {
//			skyBoxOn = !skyBoxOn;
//		}
//		else if (wParam == VK_UP) {
//			lightY += lightSpeed;
//		}
//		else if (wParam == VK_DOWN) {
//			lightY -= lightSpeed;
//		}
//		else if (wParam == VK_LEFT) {
//			lightX -= lightSpeed;
//		}
//		else if (wParam == VK_RIGHT) {
//			lightX += lightSpeed;
//		}
//		else if (wParam == '3') {
//			lightZ += lightSpeed;
//		}
//		else if (wParam == '4') {
//			lightZ -= lightSpeed;
//		}
//		else if (wParam == VK_SPACE) {
//			isLightOn = !isLightOn;
//		}
//		else if (wParam == VK_SHIFT) {
//			lightX = 0, lightY = 5, lightZ = 0;
//		}
//		else if (wParam == 'Z')//button Z, for right arm up along x axis
//		{
//			if (rightArmXAngle < 180)
//			{
//				rightArmXAngle += 5;
//			}
//		}
//		else if (wParam == 'X')//button X, for right arm down along x axis
//		{
//			if (rightArmXAngle > 0)
//			{
//				rightArmXAngle -= 5;
//			}
//		}
//		else if (wParam == 'C')//C button, for right arm up along z axis
//		{
//			if (rightArmZAngle < 90)
//			{
//				rightArmZAngle += 5;
//			}
//		}
//		else if (wParam == 'V')//v button, for right arm down along z axis
//		{
//			if (rightArmZAngle > 0)
//			{
//				rightArmZAngle -= 5;
//			}
//		}
//		else if (wParam == 'B')//B button, for forearm up
//		{
//			if (rightForearmAngle < 120)
//			{
//				rightForearmAngle += 5;
//			}
//		}
//		else if (wParam == 'N')//N button, for forearm down
//		{
//			if (rightForearmAngle > 0)
//			{
//				rightForearmAngle -= 5;
//			}
//		}
//		else if (wParam == 'M')//M button, for palm up
//		{
//			if (rightPalmAngleUpDownStatus)
//			{
//				if (rightPalmAngleUpDown > -45)
//				{
//					rightPalmAngleUpDown -= 5;
//				}
//				else
//				{
//					rightPalmAngleUpDownStatus = !rightPalmAngleUpDownStatus;
//				}
//			}
//			else {
//				if (rightPalmAngleUpDown < 45)
//				{
//					rightPalmAngleUpDown += 5;
//				}
//				else
//				{
//					rightPalmAngleUpDownStatus = !rightPalmAngleUpDownStatus;
//				}
//			}
//		}
//		else if (wParam == 0xBC)//button ',' , for right palm rotate left right
//		{
//			rightPalmAngleLeftRight += 5;
//		}
//		else if (wParam == '1')//1 button, for hand animaiton
//		{
//			handAnimationStatus = !handAnimationStatus;
//		}
//		else if (wParam == '2')//2 button, for walk animaiton
//		{
//			walkingAnimationStatus = !walkingAnimationStatus;
//		}
//		else if (wParam == 'A') //Stand up weapon
//		{
//			weaponOn = !weaponOn;
//		}
//		else if (wParam == 'S') //Shoot Energy Ball - Both
//		{
//			if (startFire)
//			{
//				shootOn = true;
//			}
//		}
//		else if (wParam == '8') {
//			textureStatus = !textureStatus;
//		}
//		else if (wParam == '9') {
//			textureNo = 1;
//		}
//		else if (wParam == '0') {
//			textureNo = 2;
//		}
//		else if (wParam == 0xBE) { // '.' button, reset right arm
//			rightArmXAngle = 0;
//			rightArmZAngle = 0;
//			rightForearmAngle = 0;
//			rightPalmAngleUpDown = 0;
//			rightPalmAngleLeftRight = 0;
//
//			sh1 = 0;
//			sh2 = 0;
//			sh3 = 0;
//			sh4 = 0;
//			sh5 = 0;
//			if (handAnimationStatus)
//			{
//				handAnimationStatus = !handAnimationStatus;
//			}
//		}
//		else if (wParam == 0xBF) { // '/' button, reset robot for walking animation
//			rotateBody = 0;
//			walkingSpeed = 0;
//			leftLegUp = 0;
//			leftLLegUp = 0;
//			rightArmXAngle = 0;
//			rightLegUp = 0;
//			rightLLegUp = 0;
//			leftArmXAngle = 0;
//			walkingAnimationStatus = false;
//		}
//
//		else if (wParam == 'O') {
//			isOrtho = true;
//		}
//		else if (wParam == 'P') {
//			isOrtho = false;
//		}
//		else if (wParam == 'D')//button D, for left arm up along x axis
//		{
//			if (leftArmXAngle < 180)
//			{
//				leftArmXAngle += 5;
//			}
//		}
//		else if (wParam == 'F')//button F, for left arm down along x axis
//		{
//			if (leftArmXAngle > 0)
//			{
//				leftArmXAngle -= 5;
//			}
//		}
//		else if (wParam == 'G')//G button, for left arm up along z axis
//		{
//			if (leftArmZAngle < 90)
//			{
//				leftArmZAngle += 5;
//			}
//		}
//		else if (wParam == 'H')//H button, for left arm down along z axis
//		{
//			if (leftArmZAngle > 0)
//			{
//				leftArmZAngle -= 5;
//			}
//		}
//		else if (wParam == 'J')//J button, for left forearm up
//		{
//			if (leftForearmAngle < 120)
//			{
//				leftForearmAngle += 5;
//			}
//		}
//		else if (wParam == 'K')//K button, for forearm down
//		{
//			if (leftForearmAngle > 0)
//			{
//				leftForearmAngle -= 5;
//			}
//		}
//		else if (wParam == 'L')//L button, for palm up
//		{
//			if (leftPalmAngleUpDownStatus)
//			{
//				if (leftPalmAngleUpDown > -45)
//				{
//					leftPalmAngleUpDown -= 5;
//				}
//				else
//				{
//					leftPalmAngleUpDownStatus = !leftPalmAngleUpDownStatus;
//				}
//			}
//			else {
//				if (leftPalmAngleUpDown < 45)
//				{
//					leftPalmAngleUpDown += 5;
//				}
//				else
//				{
//					leftPalmAngleUpDownStatus = !leftPalmAngleUpDownStatus;
//				}
//			}
//		}
//		else if (wParam == 0xBA)//button ';' , for left palm rotate left right
//		{
//			leftPalmAngleLeftRight += 5;
//		}
//		else if (wParam == 0xDE) { // ''' button, reset left arm
//			leftArmXAngle = 0;
//			leftArmZAngle = 0;
//			leftForearmAngle = 0;
//			leftPalmAngleUpDown = 0;
//			leftPalmAngleLeftRight = 0;
//		}
//	default:
//		break;
//	}
//
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
////--------------------------------------------------------------------
//
//bool initPixelFormat(HDC hdc)
//{
//	PIXELFORMATDESCRIPTOR pfd;
//	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
//
//	pfd.cAlphaBits = 8;
//	pfd.cColorBits = 32;
//	pfd.cDepthBits = 24;
//	pfd.cStencilBits = 0;
//
//	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
//
//	pfd.iLayerType = PFD_MAIN_PLANE;
//	pfd.iPixelType = PFD_TYPE_RGBA;
//	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//	pfd.nVersion = 1;
//
//	// choose pixel format returns the number most similar pixel format available
//	int n = ChoosePixelFormat(hdc, &pfd);
//
//	// set pixel format returns whether it sucessfully set the pixel format
//	if (SetPixelFormat(hdc, n, &pfd))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//GLuint loadTexture(LPCSTR filename) {
//	//Take from step 1
//	GLuint texture = 0;		//texture name
//
//	//Step 3: Initialize texture info
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
//		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
//		LR_LOADFROMFILE);
//	GetObject(hBMP, sizeof(BMP), &BMP);
//
//	//Step 4: Assign texture to polygon
//	if (textureStatus)
//	{
//		glEnable(GL_TEXTURE_2D);
//	}
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
//
//	//take from step 5
//	DeleteObject(hBMP);
//
//	return texture;
//}
//
//void drawLineCircle(float rx, float ry, float cDivide) {
//	glBegin(GL_LINE_STRIP);
//	for (angle = 0; angle <= (cDivide * PI); angle += (cDivide * PI) / noOfTri) {
//		x2 = 0 + rx * cos(angle);
//		y2 = 0 + ry * sin(angle);
//		glTexCoord2f(x2, y2);
//		glVertex2f(x2, y2);
//	}
//	glEnd();
//}
//
//void drawPyramid(float pyrX, float pyrY, float pyrZ) {
//	glBegin(GL_TRIANGLE_FAN);//tri fan       
//	// Front
//	glTexCoord2f(0.5, 1);
//	glVertex3f(0.0f, pyrY, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-pyrX, -pyrY, pyrZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(pyrX, -pyrY, pyrZ);
//
//	// Right
//	glTexCoord2f(0.5, 1);
//	glVertex3f(0.0f, pyrY, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(pyrX, -pyrY, pyrZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(pyrX, -pyrY, -pyrZ);
//
//	// Back
//	glTexCoord2f(0.5, 1);
//	glVertex3f(0.0f, pyrY, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(pyrX, -pyrY, -pyrZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-pyrX, -pyrY, -pyrZ);
//
//	// Left
//	glTexCoord2f(0.5, 1);
//	glVertex3f(0.0f, pyrY, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-pyrX, -pyrY, -pyrZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-pyrX, -pyrY, pyrZ);
//	glEnd();
//
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0);
//	glVertex3f(-pyrX, -pyrY, pyrZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-pyrX, -pyrY, -pyrZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(pyrX, -pyrY, -pyrZ);
//	glTexCoord2f(0, 1);
//	glVertex3f(pyrX, -pyrY, pyrZ);
//	glEnd();
//}
//
//void drawCuboid(float cubX, float cubY, float cubZ) {
//
//	glBegin(GL_QUADS);//quad
//
//	// Bottom face 
//	glTexCoord2f(0, 1);
//	glVertex3f(-cubX, -cubY, -cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(-cubX, -cubY, cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(cubX, -cubY, cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(cubX, -cubY, -cubZ);
//
//	// Left face 
//	glTexCoord2f(0, 1);
//	glVertex3f(-cubX, cubY, -cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(-cubX, cubY, cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-cubX, -cubY, cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(-cubX, -cubY, -cubZ);
//
//	// Front face
//	glTexCoord2f(0, 1);
//	glVertex3f(-cubX, -cubY, cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(-cubX, cubY, cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(cubX, cubY, cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(cubX, -cubY, cubZ);
//
//	// Right face 
//	glTexCoord2f(0, 1);
//	glVertex3f(cubX, -cubY, cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(cubX, cubY, cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(cubX, cubY, -cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(cubX, -cubY, -cubZ);
//
//	// Back face 
//	glTexCoord2f(0, 1);
//	glVertex3f(cubX, -cubY, -cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(-cubX, -cubY, -cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-cubX, cubY, -cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(cubX, cubY, -cubZ);
//
//	// Top face 
//	glTexCoord2f(0, 1);
//	glVertex3f(cubX, cubY, cubZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(-cubX, cubY, cubZ);
//	glTexCoord2f(1, 0);
//	glVertex3f(-cubX, cubY, -cubZ);
//	glTexCoord2f(0, 0);
//	glVertex3f(cubX, cubY, -cubZ);
//
//	glEnd();
//}
//
//void drawCuboidBasedZero(float cubX, float cubY, float cubZ) {
//
//	glBegin(GL_QUADS);//quad
//
//	// Bottom face 
//	glVertex3f(-cubX, -cubY, 0);
//	glVertex3f(-cubX, -cubY, cubZ);
//	glVertex3f(cubX, -cubY, cubZ);
//	glVertex3f(cubX, -cubY, 0);
//
//	// Left face 
//	glVertex3f(-cubX, cubY, 0);
//	glVertex3f(-cubX, cubY, cubZ);
//	glVertex3f(-cubX, -cubY, cubZ);
//	glVertex3f(-cubX, -cubY, 0);
//
//	// Front face
//	glVertex3f(-cubX, -cubY, cubZ);
//	glVertex3f(-cubX, cubY, cubZ);
//	glVertex3f(cubX, cubY, cubZ);
//	glVertex3f(cubX, -cubY, cubZ);
//
//	// Right face 
//	glVertex3f(cubX, -cubY, cubZ);
//	glVertex3f(cubX, cubY, cubZ);
//	glVertex3f(cubX, cubY, 0);
//	glVertex3f(cubX, -cubY, 0);
//
//	// Back face 
//	glVertex3f(cubX, -cubY, 0);
//	glVertex3f(-cubX, -cubY, 0);
//	glVertex3f(-cubX, cubY, 0);
//	glVertex3f(cubX, cubY, 0);
//
//	// Top face 
//	glVertex3f(cubX, cubY, cubZ);
//	glVertex3f(-cubX, cubY, cubZ);
//	glVertex3f(-cubX, cubY, 0);
//	glVertex3f(cubX, cubY, 0);
//
//	glEnd();
//}
//
//void drawSphere(double r) {
//	GLUquadricObj* sphere = NULL;
//	sphere = gluNewQuadric();
//	gluQuadricDrawStyle(sphere, GLU_FILL);
//	gluQuadricTexture(sphere, true);
//	gluSphere(sphere, r, 30, 30);
//	gluDeleteQuadric(sphere);
//}
//
//void drawSquare(float sqX, float sqZ) {
//	glPushMatrix();
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0);
//	glVertex3f(0, 0, 0);
//	glTexCoord2f(1, 0);
//	glVertex3f(0, 0, sqZ);
//	glTexCoord2f(1, 1);
//	glVertex3f(sqX, 0, sqZ);
//	glTexCoord2f(0, 1);
//	glVertex3f(sqX, 0, 0);
//	glEnd();
//	glPopMatrix();
//}
//
//void triangularPrism()
//{
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.5, 0, 0.5);
//	glTexCoord2f(1, 0);
//	glVertex3f(0.5, 0, -0.5);
//	glTexCoord2f(1, 1);
//	glVertex3f(-0.5, 0, -0.5);
//	glTexCoord2f(0, 1);
//	glVertex3f(-0.5, 0, 0.5);
//
//	glTexCoord2f(0, 0);
//	glVertex3f(0.5, 0, -0.5);
//	glTexCoord2f(1, 0);
//	glVertex3f(0.5, 1, -0.5);
//	glTexCoord2f(1, 1);
//	glVertex3f(-0.5, 1, -0.5);
//	glTexCoord2f(0, 1);
//	glVertex3f(-0.5, 0, -0.5);
//
//	glTexCoord2f(0, 0);
//	glVertex3f(0.5, 1, -0.5);
//	glTexCoord2f(1, 0);
//	glVertex3f(-0.5, 1, -0.5);
//	glTexCoord2f(1, 1);
//	glVertex3f(-0.5, 0, 0.5);
//	glTexCoord2f(0, 1);
//	glVertex3f(0.5, 0, 0.5);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glTexCoord2f(0.5, 1);
//	glVertex3f(0.5, 0, 0.5);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.5, 1, -0.5);
//	glTexCoord2f(1, 0);
//	glVertex3f(0.5, 0, -0.5);
//
//	glTexCoord2f(0.5, 1);
//	glVertex3f(-0.5, 0, 0.5);
//	glTexCoord2f(0, 0);
//	glVertex3f(-0.5, 1, -0.5);
//	glTexCoord2f(1, 0);
//	glVertex3f(-0.5, 0, -0.5);
//	glEnd();
//}
//
//void drawTriangularPrism(float triPx, float triPy, float triPz)
//{
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0);
//	glVertex3f(triPx, 0, triPz);
//	glTexCoord2f(1, 0);
//	glVertex3f(triPx, 0, -triPz);
//	glTexCoord2f(1, 1);
//	glVertex3f(-triPx, 0, -triPz);
//	glTexCoord2f(0, 1);
//	glVertex3f(-triPx, 0, triPz);
//
//	glTexCoord2f(0, 0);
//	glVertex3f(triPx, 0, -triPz);
//	glTexCoord2f(1, 0);
//	glVertex3f(triPx, triPy, -triPz);
//	glTexCoord2f(1, 1);
//	glVertex3f(-triPx, triPy, -triPz);
//	glTexCoord2f(0, 1);
//	glVertex3f(-triPx, 0, -triPz);
//
//	glTexCoord2f(0, 0);
//	glVertex3f(triPx, triPy, -triPz);
//	glTexCoord2f(1, 0);
//	glVertex3f(-triPx, triPy, -triPz);
//	glTexCoord2f(1, 1);
//	glVertex3f(-triPx, 0, triPz);
//	glTexCoord2f(0, 1);
//	glVertex3f(triPx, 0, triPz);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glTexCoord2f(0.5, 1);
//	glVertex3f(triPx, 0, triPz);
//	glTexCoord2f(0, 0);
//	glVertex3f(triPx, triPy, -triPz);
//	glTexCoord2f(1, 0);
//	glVertex3f(triPx, 0, -triPz);
//
//	glTexCoord2f(0.5, 1);
//	glVertex3f(-triPx, 0, triPz);
//	glTexCoord2f(0, 0);
//	glVertex3f(-triPx, triPy, -triPz);
//	glTexCoord2f(1, 0);
//	glVertex3f(-triPx, 0, -triPz);
//	glEnd();
//}
//
//void drawCircle(float rx, float ry) {
//	glBegin(GL_TRIANGLE_FAN);
//	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
//		x2 = 0 + rx * cos(angle);
//		y2 = 0 + ry * sin(angle);
//		glVertex2f(x2, y2);
//		glTexCoord2f(x2, y2);
//	}
//	glEnd();
//}
//
//void drawCylinder(float br, double tr, double h) {
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluQuadricTexture(cylinder, true);
//	gluCylinder(cylinder, br, tr, h, 30, 30);
//	gluDeleteQuadric(cylinder);
//
//	glPushMatrix();
//	drawCircle(br, br);
//	glTranslatef(0, 0, h);
//	drawCircle(tr, tr);
//	glPopMatrix();
//}
//
//void drawCylinderWithoutCover(float br, double tr, double h) {
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluQuadricTexture(cylinder, true);
//	gluCylinder(cylinder, br, tr, h, 30, 30);
//	gluDeleteQuadric(cylinder);
//}
//
//void drawCover(float rx, float ry, int side) {
//	glBegin(GL_TRIANGLE_FAN);
//	glColor3f(1, 0, 1);
//	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / side) {
//		x2 = 0 + rx * cos(angle);
//		y2 = 0 + ry * sin(angle);
//		glVertex2f(x2, y2);
//		glTexCoord2f(x2, y2);
//	}
//	glEnd();
//}
//
//void drawPolygonPrism(float br, float tr, float h, int side) {
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluQuadricTexture(cylinder, true);
//	gluCylinder(cylinder, br, tr, h, side, side);
//	gluDeleteQuadric(cylinder);
//	glPushMatrix();
//	drawCover(br, br, side);
//	glTranslatef(0, 0, h);
//	drawCover(tr, tr, side);
//	glPopMatrix();
//};
//
//void drawHexagon(float br, double tr, double h) {
//	int i;
//
//	glPushMatrix();
//
//	glRotatef(30, 0, 0, 1);
//
//	//Top
//	glPushMatrix();
//	glTranslatef(0, 0, h);
//	glScalef(tr, tr, 0);
//	glBegin(GL_POLYGON);
//	for (i = 0; i < 6; i++) {
//		glVertex2f(sin(i / 6.0 * 2 * PI), cos(i / 6.0 * 2 * PI));
//		glTexCoord2f(sin(i / 6.0 * 2 * PI) - 3, cos(i / 6.0 * 2 * PI));
//	}
//	glEnd();
//	glPopMatrix();
//
//	//Bottom
//	glPushMatrix();
//	glScalef(br, br, 0);
//	glBegin(GL_POLYGON);
//	for (i = 0; i < 6; i++) {
//		glVertex2f(sin(i / 6.0 * 2 * PI), cos(i / 6.0 * 2 * PI));
//		glTexCoord2f(sin(i / 6.0 * 2 * PI), cos(i / 6.0 * 2 * PI));
//	}
//	glEnd();
//	glPopMatrix();
//
//	//Middle
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluQuadricTexture(cylinder, true);
//	gluCylinder(cylinder, br, tr, h, 6, 6);
//	gluDeleteQuadric(cylinder);
//
//	glPopMatrix();
//}
//
//void drawOctagon(float br, double tr, double h) {
//	int i;
//
//	//Top
//	glPushMatrix();
//	glTranslatef(0, 0, h);
//	glScalef(tr, tr, 0);
//	glBegin(GL_POLYGON);
//	for (i = 0; i < 8; i++) {
//		glVertex2f(sin(i / 8.0 * 2 * PI), cos(i / 8.0 * 2 * PI));
//		glTexCoord2f(sin(i / 8.0 * 2 * PI), cos(i / 8.0 * 2 * PI));
//	}
//	glEnd();
//	glPopMatrix();
//
//	//Bottom
//	glPushMatrix();
//	glScalef(br, br, 0);
//	glBegin(GL_POLYGON);
//	for (i = 0; i < 8; i++) {
//		glVertex2f(sin(i / 8.0 * 2 * PI), cos(i / 8.0 * 2 * PI));
//		glTexCoord2f(sin(i / 8.0 * 2 * PI), cos(i / 8.0 * 2 * PI));
//	}
//	glEnd();
//	glPopMatrix();
//
//	//Middle
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluQuadricTexture(cylinder, true);
//	gluCylinder(cylinder, br, tr, h, 8, 8);
//	gluDeleteQuadric(cylinder);
//
//}
//
//void drawSphereWithoutGLU(float radX, float radY, float radZ, float piDivide)
//{
//	const float PI = 3.141592f;
//	GLfloat x, y, z, sliceA, stackA;
//	int sliceNo = 30, stackNo = 30;
//	for (sliceA = 0.0; sliceA < 2 * PI / piDivide; sliceA += PI / sliceNo)
//	{
//		glBegin(GL_TRIANGLE_STRIP);
//		for (stackA = 0.0; stackA < 2 * PI / piDivide; stackA += PI / stackNo)
//		{
//			x = radX * cos(stackA) * sin(sliceA);
//			y = radY * sin(stackA) * sin(sliceA);
//			z = radZ * cos(sliceA);
//			glTexCoord3f(x, y, z);
//			glVertex3f(x, y, z);
//			x = radX * cos(stackA) * sin(sliceA + PI / stackNo);
//			y = radY * sin(stackA) * sin(sliceA + PI / sliceNo);
//			z = radZ * cos(sliceA + PI / sliceNo);
//			glTexCoord3f(x, y, z);
//			glVertex3f(x, y, z);
//		}
//		glEnd();
//	}
//}
//
//void drawTrapezoidalPrism(float sz, float sy, float topDis, float zRatio) {
//	float x = (sz - topDis) / 2;
//	float z = sz * zRatio;
//	glLineWidth(5);
//	glBegin(GL_QUADS);
//	// Face 1: Bottom
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f(sz, 0.0f, sz);
//	glTexCoord2f(1, 0);
//	glVertex3f(sz, 0.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//
//	// Face 2: Left
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.0f, 0.0f, sz);
//
//	// Face 3: Front
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(1, 0);
//	glVertex3f((x + topDis), sy, sz - z);
//	glTexCoord2f(0, 0);
//	glVertex3f(sz, 0.0f, sz);
//
//	// Face 4: Right
//	glTexCoord2f(0, 1);
//	glVertex3f(sz, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f((x + topDis), sy, sz - z);
//	glTexCoord2f(1, 0);
//	glVertex3f((x + topDis), sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f(sz, 0.0f, 0.0f);
//
//	// Face 5: Back
//	glTexCoord2f(0, 1);
//	glVertex3f(sz, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f((x + topDis), sy, z);
//
//	// Face 6: Top
//	glTexCoord2f(0, 1);
//	glVertex3f((x + topDis), sy, sz - z);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f((x + topDis), sy, z);
//
//	glEnd();
//}
//
//void drawTrapezoidalPrism(float sz, float sy, float topDis) {
//	float x = (sz - topDis) / 2;
//	float z = sz * 0.6;
//	glBegin(GL_QUADS);
//	// Face 1: Bottom
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f(sz, 0.0f, sz);
//	glTexCoord2f(1, 0);
//	glVertex3f(sz, 0.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//
//	// Face 2: Left
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f(0.0f, 0.0f, sz);
//
//	// Face 3: Front
//	glTexCoord2f(0, 1);
//	glVertex3f(0.0f, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(1, 0);
//	glVertex3f((x + topDis), sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f(sz, 0.0f, sz);
//
//	// Face 4: Right
//	glTexCoord2f(0, 1);
//	glVertex3f(sz, 0.0f, sz);
//	glTexCoord2f(1, 1);
//	glVertex3f((x + topDis), sy, z);
//	glTexCoord2f(1, 0);
//	glVertex3f((x + topDis), sy, sz - z);
//	glTexCoord2f(0, 0);
//	glVertex3f(sz, 0.0f, 0.0f);
//
//	// Face 5: Back
//	glTexCoord2f(0, 1);
//	glVertex3f(sz, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(0, 0);
//	glVertex3f((x + topDis), sy, sz - z);
//
//	// Face 6: Top
//	glTexCoord2f(0, 1);
//	glVertex3f((x + topDis), sy, sz - z);
//	glTexCoord2f(1, 1);
//	glVertex3f(x, sy, sz - z);
//	glTexCoord2f(1, 0);
//	glVertex3f(x, sy, z);
//	glTexCoord2f(0, 0);
//	glVertex3f((x + topDis), sy, z);
//
//	glEnd();
//}
//
//void scratchingHeadAnimation() {
//	if (handAnimationStatus)
//	{
//		if (sh1 <= 0 && sh1 >= -20)
//		{
//			sh1 -= 3;
//		}
//		else {
//			sh1 -= 0;
//		}
//		if (sh1 <= -20 && sh2 < 190)
//		{
//			sh2 += 20;
//		}
//		else {
//			sh2 += 0;
//		}
//
//		if (sh2 >= 190 && sh3 > -140)
//		{
//			sh3 -= 10;
//		}
//		else {
//			sh3 -= 0;
//		}
//		if (sh3 <= -140 && sh4 < 20)
//		{
//			sh4 += 5;
//		}
//		else {
//			sh4 += 0;
//		}
//		if (scratchBool)
//		{
//			if (sh4 >= 20 && sh5 < 45) {
//				sh5 += 2;
//			}
//			else
//			{
//				scratchBool = !scratchBool;
//			}
//		}
//		else
//		{
//
//			if (sh5 > 0)
//			{
//				sh5 -= 1;
//			}
//			else
//			{
//				scratchBool = !scratchBool;
//			}
//
//
//		}
//
//
//	}
//}
//
//void walkingAnimation() {
//
//	if (walkingAnimationStatus)
//	{
//		if (leftLegStatus)
//		{
//			if (rotateBody <= 5)
//			{
//				rotateBody += 0.45;
//				walkingSpeed += 0.05;
//
//
//				if (!leftLegUpStatus)
//				{
//					if (leftLegUp >= -3)
//					{
//						leftLegUp += -0.4;
//						leftLLegUp += 0.15;
//						rightArmXAngle -= 1;
//					}
//
//
//				}
//				if (rightLegUpStatus)
//				{
//					if (rightLegUp < 15)
//					{
//						rightLegUp += 0.4;
//						rightLLegUp += -0.15;
//						leftArmXAngle += 1;
//					}
//				}
//
//				if (walkingSpeed > 9)
//				{
//					walkingSpeed += 0;
//					rotateBody += 0;
//					leftLegUp += -0;
//					leftLLegUp += 0;
//					rightArmXAngle += 0;
//					rightLegUp += 0;
//					rightLLegUp += -0;
//					leftArmXAngle += 0;
//					walkingAnimationStatus = false;
//				}
//			}
//			else
//			{
//				leftLegStatus = !leftLegStatus;
//				leftLegUpStatus = !leftLegUpStatus;
//				rightLegUpStatus = !rightLegUpStatus;
//			}
//		}
//		else
//		{
//			if (rotateBody >= -5)
//			{
//				rotateBody += -0.5;
//				walkingSpeed += 0.05;
//
//				if (leftLegUpStatus)
//				{
//					if (leftLegUp < 15)
//					{
//						leftLegUp += 0.4;
//						leftLLegUp += -0.15;
//						rightArmXAngle += 1;
//					}
//				}
//				if (!rightLegUpStatus)
//				{
//					if (rightLegUp >= 0)
//					{
//						rightLegUp += -0.4;
//						rightLLegUp += 0.15;
//						leftArmXAngle -= 1.2;
//					}
//				}
//			}
//			else
//			{
//				leftLegStatus = !leftLegStatus;
//				leftLegUpStatus = !leftLegUpStatus;
//				rightLegUpStatus = !rightLegUpStatus;
//			}
//		}
//
//
//	}
//
//}
////Author: Wilson Yau Kai Chun========================================
//void drawArmArmor(float br, double tr, double h, int slides, int stacks) {
//
//	GLUquadricObj* cylinder = NULL;
//	cylinder = gluNewQuadric();
//	gluQuadricDrawStyle(cylinder, GLU_FILL);
//	gluCylinder(cylinder, br, tr, h, slides, stacks);
//	gluDeleteQuadric(cylinder);
//	glPushMatrix();
//	drawCircle(br, br);
//	glTranslatef(0, 0, h);
//	drawCircle(tr, tr);
//	glPopMatrix();
//}
//
//void arm() {
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	//textureArr[3] = loadTexture("HandLegMetal.bmp");
//	glPushMatrix();//muscle
//	//glColor3f(1, 0, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawSphereWithoutGLU(0.18, 0.3, 0.18, 1);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();//cylinder - joint
//	glRotatef(90, 1, 0, 0);
//	glTranslatef(0, 0, -0.4);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.06, 0.06, 0.2);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//}
//
//void armJoint() {
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	drawSphereWithoutGLU(0.1, 0.1, 0.1, 1);
//
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//}
//
//void forearm() {
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();//cylinder - joint
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.06, 0.06, 0.2);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//
//	glPushMatrix();//muscle
//	glTranslatef(-0, 0, 0.1);
//	glColor3f(c(188), c(141), c(63));
//	drawCylinder(0.1, 0.1, 0.25);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//	textureArr[4] = loadTexture("Body.bmp");
//	glTranslatef(0, 0, 0.3);
//	glPushMatrix();//cylinder - joint
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.05, 0.05, 0.1);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//}
//
//void forearmJoint() {
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();//left
//	glRotatef(90, 0, 1, 0);
//	glTranslatef(-0.01, 0, -0.06);
//	glColor3f(c(125), c(84), c(66));
//	drawCylinder(0.06, 0.06, 0.01);
//	glPopMatrix();
//
//	glPushMatrix();//right
//	glRotatef(90, 0, 1, 0);
//	glTranslatef(-0.01, 0, 0.05);
//	glColor3f(c(125), c(84), c(66));
//	drawCylinder(0.06, 0.06, 0.01);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//}
//
//void palm() {
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.05, 0.05, 0.2);//cylinder - joint
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glTranslatef(0, -0.07, 0.2);
//	glColor3f(c(188), c(141), c(63));
//	drawSphereWithoutGLU(0.16, 0.18, 0.15, 2);
//	glPopMatrix();
//
//
//	//Cylinder on the inner palm
//	glPushMatrix();
//	glRotatef(90, 1, 0, 0);
//	glTranslatef(-0, 0.2, 0.07);
//	glColor3f(c(188), c(141), c(63));
//	drawCylinder(0.16, 0.16, 0.015);
//
//	glColor3f(c(128), c(128), c(128));
//	drawCylinder(0.1, 0.1, 0.02);
//
//	//glScalef(0.5, 0.5, 0.5);
//	glColor3f(c(45), c(45), c(45));
//	drawCylinder(0.06, 0.06, 0.025);
//
//	glDeleteTextures(1, &textureArr[3]);
//	glPopMatrix();
//}
//
//void paw() {
//	glPushMatrix();
//	glScalef(0.8, 1.2, 1);
//
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	drawCuboid(0.12, 0.04, 0.08);//first joint
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//	switch (textureNo) {
//	case 1:
//		textureArr[6] = loadTexture("PawMetal.bmp");
//		break;
//	case 2:
//		textureArr[6] = loadTexture("PawConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glColor3f(c(192), c(192), c(192));
//	glPushMatrix();
//	glScalef(1.5, 1, 1);
//	glTranslatef(-0.08, 0.04, -0.08);
//	drawTrapezoidalPrism(0.16, 0.12, 0.12, 0.2);//second joint
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(5, 1, 0, 0);
//	glScalef(1.5, 1, 0.8);
//	glTranslatef(-0.06, 0.16, -0.08);
//	drawTrapezoidalPrism(0.118, 0.12, 0.08, 0.2);//third joint
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(11, 1, 0, 0);
//	glTranslatef(0.0, 0.35, -0.05);
//	drawPyramid(0.06, 0.08, 0.025);//fourth joint
//	glPopMatrix();
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[6]);
//}
//
//void rightHand() {
//	glPushMatrix(); //hands
//	glRotatef(180, 1, 0, 0);
//	glRotatef(180, 0, 1, 0);
//	//glTranslatef(0, -0.8, 0);
//	//glScalef(1, 0.5, 1);
//	glLineWidth(5);
//	glColor3f(1, 0, 0);
//
//	glRotatef(rightArmXAngle, 1, 0, 0);
//	glRotatef(-rightArmZAngle, 0, 0, 1);
//
//	glRotatef(sh1, 0, 0, 1);//***1
//	glRotatef(sh3, 0, 0, 1);//***3
//	glRotatef(-10, 0, 0, 1);
//	//Arm
//	glPushMatrix();
//	arm();
//
//	//Forearm
//	glPushMatrix();
//	glRotatef(-90, 1, 0, 0);
//	glTranslatef(0, 0, 0.38);
//
//	glRotatef(rightForearmAngle, 1, 0, 0);
//	glRotatef(sh4, 0, 1, 0);//***4
//	glRotatef(sh2, 0, 0, 1);//***2
//
//	//Cylinder beside the joint
//	armJoint();
//
//
//	//Forearm (joints and muscle)
//	forearm();
//
//	//Palm part
//	glPushMatrix();
//	glRotatef(-110, 0, 0, 1);
//	glTranslatef(0, 0, 0.1);
//
//	glRotatef(rightPalmAngleUpDown, 1, 0, 0);
//	glRotatef(sh5, 1, 0, 0);
//	glRotatef(rightPalmAngleLeftRight, 0, 0, 1);
//
//	//Cylinder at the joint
//
//	forearmJoint();
//
//	//palm
//	palm();
//
//	//Paw
//	glPushMatrix();
//
//
//	//First paw - middle
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.4);
//	glTranslatef(0, 0, 0.85);
//	glRotatef(90, 1, 0, 0);
//	paw();
//	glPopMatrix();
//
//	//Second paw - left
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.3);
//	glTranslatef(-0.2, 0, 1);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(25, 0, 0, 1);
//	paw();
//	glPopMatrix();
//
//	//Third paw - right
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.3);
//	glTranslatef(0.2, 0, 1);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(-25, 0, 0, 1);
//	paw();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//
//
//	scratchingHeadAnimation();
//
//}
//
//void leftHand() {
//	glPushMatrix(); //hands
//	glRotatef(180, 1, 0, 0);
//	glRotatef(180, 0, 1, 0);
//	glLineWidth(5);
//	glColor3f(1, 0, 0);
//
//	glRotatef(leftArmXAngle, 1, 0, 0);
//	glRotatef(leftArmZAngle, 0, 0, 1);
//
//	//glRotatef(-sh1, 0, 0, 1);//***1
//	//glRotatef(-sh3, 0, 0, 1);//***3
//	glRotatef(10, 0, 0, 1);
//	//Arm
//	glPushMatrix();
//	arm();
//
//	//Forearm
//	glPushMatrix();
//	glRotatef(-90, 1, 0, 0);
//	glTranslatef(0, 0, 0.38);
//
//	glRotatef(leftForearmAngle, 1, 0, 0);
//	//glRotatef(-sh4, 0, 1, 0);//***4
//	//glRotatef(-sh2, 0, 0, 1);//***2
//
//	//Cylinder beside the joint
//	armJoint();
//
//
//	//Forearm (joints and muscle)
//	forearm();
//
//	//Palm part
//	glPushMatrix();
//	glRotatef(90, 0, 0, 1);
//	glTranslatef(0, 0, 0.1);
//
//	glRotatef(leftPalmAngleUpDown, 1, 0, 0);
//	glRotatef(leftPalmAngleLeftRight, 0, 0, 1);
//
//	//Cylinder at the joint
//
//	forearmJoint();
//
//	//palm
//	palm();
//
//	//Paw
//	glPushMatrix();
//
//
//	//First paw - middle
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.4);
//	glTranslatef(0, 0, 0.85);
//	glRotatef(90, 1, 0, 0);
//	paw();
//	glPopMatrix();
//
//	//Second paw - left
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.3);
//	glTranslatef(-0.2, 0, 1);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(25, 0, 0, 1);
//	paw();
//	glPopMatrix();
//
//	//Third paw - right
//	glPushMatrix();
//	glScalef(0.5, 0.5, 0.3);
//	glTranslatef(0.2, 0, 1);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(-25, 0, 0, 1);
//	paw();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//
//
//	//scratchingHeadAnimation();
//
//}
////---------------------------------------
//void leftUpperLeg() {
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();//Muscle
//	//glRotatef(rightPalmAngleUpDown, 1, 0, 0);
//	glTranslatef(0, -0.3, 0);
//	glRotatef(20, 0, 0, 1);
//	glColor3f(c(188), c(141), c(63));
//	drawSphereWithoutGLU(0.15, 0.2, 0.15, 1);
//
//	glPushMatrix();//Armor at upper leg
//	glRotatef(90, 1, 0, 0);
//	glColor3f(c(125), c(84), c(66));
//	drawSphereWithoutGLU(0.18, 0.18, 0.23, 1.8);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();//Cylinder joint
//	glRotatef(90, 1, 0, 0);
//	glTranslatef(0, 0, 0.18);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.04, 0.04, 0.085);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//
//}
//
//void lowerLeg() {
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();//Cylinder - joint
//	glRotatef(90, 1, 0, 0);
//	//glTranslatef(0, 0, 0.);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.04, 0.04, 0.065);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();//Sphere
//	glTranslatef(0, -0.12, 0.08);
//	glColor3f(c(188), c(141), c(63));
//	drawSphereWithoutGLU(0.14, 0.15, 0.14, 2);
//
//
//	glRotatef(90, 1, 0, 0);
//	drawCylinder(0.14, 0.14, 0.005);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//	//Leg's paws
//	switch (textureNo) {
//	case 1:
//		textureArr[6] = loadTexture("PawMetal.bmp");
//		break;
//	case 2:
//		textureArr[6] = loadTexture("PawConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glColor3f(c(192), c(192), c(192));
//	glPushMatrix();//right paw
//	glTranslatef(0.06, -0.06, 0.16);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(-40, 0, 0, 1);
//	glScalef(1, 1, 0.5);
//	drawTrapezoidalPrism(0.1, 0.2, 0.02, 0.4);
//	glPopMatrix();
//
//	glPushMatrix();//middle paw
//	glTranslatef(-0.05, -0.06, 0.18);
//	glRotatef(90, 1, 0, 0);
//	glScalef(1, 1, 0.5);
//	drawTrapezoidalPrism(0.1, 0.2, 0.02, 0.4);
//	glPopMatrix();
//
//	glPushMatrix();//left paw
//	glTranslatef(-0.1, -0.06, 0.08);
//	glRotatef(90, 1, 0, 0);
//	glRotatef(45, 0, 0, 1);
//	glScalef(1, 1, 0.5);
//	drawTrapezoidalPrism(0.1, 0.2, 0.02, 0.4);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[6]);
//}
//
//void rightUpperLeg() {
//	switch (textureNo) {
//	case 1:
//		textureArr[3] = loadTexture("HandLegMetal.bmp");
//		break;
//	case 2:
//		textureArr[3] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();//Muscle
//	glTranslatef(0, -0.3, 0);
//	glRotatef(-20, 0, 0, 1);
//	glColor3f(c(188), c(141), c(63));
//	drawSphereWithoutGLU(0.15, 0.2, 0.15, 1);
//
//	glPushMatrix();//Armor at upper leg
//	glRotatef(90, 1, 0, 0);
//	glColor3f(c(125), c(84), c(66));
//	drawSphereWithoutGLU(0.18, 0.18, 0.23, 1.8);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[3]);
//
//	textureArr[4] = loadTexture("Body.bmp");
//	glPushMatrix();//Cylinder joint
//	glRotatef(90, 1, 0, 0);
//	glTranslatef(0, 0, 0.18);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.04, 0.04, 0.085);
//	glPopMatrix();
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[4]);
//}
//
//void leftLeg() {
//	glPushMatrix();
//	glTranslatef(0, 0.5, 0);
//	glPushMatrix();
//
//	//Upper leg
//	glPushMatrix();
//
//	glRotatef(-45, 1, 0, 0);
//	glRotatef(-10, 0, 0, 1);
//	glRotatef(-leftLegUp, 1, 0, 0);//***1
//	glTranslatef(0.3, -0.2, -0.1);
//
//	leftUpperLeg();
//	glPopMatrix();
//
//	//Lower leg
//	glPushMatrix();
//	glTranslatef(0.088, -0.54, -0);
//	glRotatef(45, 1, 0, 0);
//	glRotatef(20, 0, 0, 1);
//	//glRotatef(-45, 1, 0, 0);
//	glRotatef(leftLLegUp, 1, 0, 0);
//
//	lowerLeg();
//
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//
//}
//
//void rightLeg() {
//	glPushMatrix();
//	glTranslatef(0, 0.5, 0);
//	glPushMatrix();
//
//	//Upper leg
//	glPushMatrix();
//	glRotatef(leftLegUp, 1, 0, 0);//***1
//	glRotatef(-45, 1, 0, 0);
//	glRotatef(10, 0, 0, 1);
//	glTranslatef(-0.3, -0.2, -0.1);
//
//	rightUpperLeg();
//	//Lower leg  
//	glPushMatrix();
//	glTranslatef(-0.088, -0.54, -0);
//	glRotatef(45, 1, 0, 0);
//	glRotatef(-20, 0, 0, 1);
//	glRotatef(rightLLegUp, 1, 0, 0);
//
//	lowerLeg();
//
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//
//}
//
////Author: Eugene Law Kai Le ================================================================
//void lowerJaw() {
//	//prism - lower jaw - left
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(-1.8, -1.9, -3.6);
//	glRotatef(-90, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	glRotatef(20, 1, 0, 0);
//	glScalef(1.5, 1.5, 1.5);
//	drawTriangularPrism(1.75, 0.7, 0.5);
//	glPopMatrix();
//
//	//prism - lower jaw - right
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(1.8, -1.9, -3.6);
//	glRotatef(90, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	glRotatef(20, 1, 0, 0);
//	glScalef(1.5, 1.5, 1.5);
//	drawTriangularPrism(1.75, 0.7, 0.5);
//	glPopMatrix();
//
//	//prism - lower jaw rim - front
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(0, -1.1, -1.4);
//	glRotatef(27, 0, 0, 1);
//	glRotatef(180, 0, 0, 1);
//	drawSphereWithoutGLU(1.95, 1.95, 1.95, 2.75);
//	glPopMatrix();
//
//	//sphere - lower jaw rim - front left
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(-1.35, -2.1, -1.2);
//	drawSphereWithoutGLU(0.55, 0.55, 0.55, 1);
//	glPushMatrix();
//	glTranslatef(0, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(0.2, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(0.4, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(0.45, 0.15, 0.05);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//sphere - lower jaw rim - front right
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(1.35, -2.1, -1.2);
//	drawSphereWithoutGLU(0.55, 0.55, 0.55, 1);
//	glPushMatrix();
//	glTranslatef(0, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(-0.2, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(-0.4, 0.25, 0.6);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPushMatrix();
//	glTranslatef(-0.45, 0.15, 0.05);
//	drawSphereWithoutGLU(0.4, 0.4, 0.4, 1);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//teeth - left
//	glPushMatrix();
//	glColor3f(1, 1, 1);
//	glTranslatef(-1.5, -1.2, -5);
//	glRotatef(10, 0, 0, 1);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//teeth - right
//	glPushMatrix();
//	glColor3f(1, 1, 1);
//	glTranslatef(1.5, -1.2, -5);
//	glRotatef(-10, 0, 0, 1);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
//	drawPyramid(0.2, 0.5, 0.5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//cuboid - lower jaw
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(0, -2.25, -4);
//	drawCuboid(1.5, 0.3, 3);
//	glPopMatrix();
//
//	//bottom
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(1.45, -2.6, -1);
//	glRotatef(180, 0, 0, 1);
//	glRotatef(90, 0, 1, 0);
//	drawTrapezoidalPrism(2.9, 0.7, 2.8);
//	glPushMatrix();
//	glTranslatef(2.5, 0, 0);
//	drawTrapezoidalPrism(2.9, 0.7, 2.8);
//	glPopMatrix();
//	glPopMatrix();
//
//	//prism - tongue - bottom
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glTranslatef(0, -2, -3);
//	glScalef(2, 1, 1);
//	drawTriangularPrism(0.5, 1, 2);
//	glPopMatrix();
//}
//
//void upperJaw() {
//	//Upper Jaw
//	glBegin(GL_TRIANGLES);//tri- front tooth
//	glColor3f(c(125), c(84), c(66));
//	glVertex3f(0, 0, 1);
//	glVertex3f(-1, 0, -1);
//	glVertex3f(0, -1, 1);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);//tri - front tooth
//	glColor3f(c(125), c(84), c(66));
//	glVertex3f(0, 0, 1);
//	glVertex3f(1, 0, -1);
//	glVertex3f(0, -1, 1);
//	glEnd();
//
//	glBegin(GL_QUADS);//quad - above front tooth
//	glVertex3f(0, 0, 1);
//	glVertex3f(-1, 0, -1);
//	glVertex3f(-1, 0.5, -1);
//	glVertex3f(0, 0.5, 1);
//	glEnd();
//
//	glBegin(GL_QUADS);//quad - above front tooth
//	glVertex3f(0, 0, 1);
//	glVertex3f(1, 0, -1);
//	glVertex3f(1, 0.5, -1);
//	glVertex3f(0, 0.5, 1);
//	glEnd();
//
//	//cuboid - nose 
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//
//	glTranslatef(0, 1.25, -4);
//	drawCuboid(1, 0.75, 3);
//	glPopMatrix();
//
//	//pyramid - between eyes
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(0, 3, -6);
//	drawPyramid(1, 1, 2);
//	glPopMatrix();
//
//	//nose
//	glBegin(GL_TRIANGLES);
//	glColor3f(c(125), c(84), c(66));
//	glVertex3f(1, 0.5, -1);
//	glVertex3f(0, 0.5, 1);
//	glVertex3f(1, 2, -1);
//	glEnd();
//
//	//nose
//	glBegin(GL_TRIANGLES);
//	glColor3f(c(125), c(84), c(66));
//	glVertex3f(-1, 0.5, -1);
//	glVertex3f(0, 0.5, 1);
//	glVertex3f(-1, 2, -1);
//	glEnd();
//
//	//nose
//	glBegin(GL_TRIANGLES);
//	glColor3f(c(125), c(84), c(66));
//	glVertex3f(0, 0.5, 1);
//	glVertex3f(-1, 2, -1);
//	glVertex3f(1, 2, -1);
//	glEnd();
//
//	//prism - tongue - top
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glTranslatef(0, -0.6, -3.5);
//	glRotatef(90, 1, 0, 0);
//	glScalef(2, 1, 1.2);
//	drawTriangularPrism(0.5, 1, 0.5);
//	glPopMatrix();
//
//	//cuboid - tongue - top
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glTranslatef(0, -1, -5);
//	drawCuboid(1, 1, 1.5);
//	glPopMatrix();
//
//	//prism - upper jaw - left
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(-1.3, 0, -3.85);
//	glRotatef(180, 1, 0, 0);
//	glRotatef(-90, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	glScalef(1.5, 1.5, 1.5);
//	drawTriangularPrism(1.9, 0.7, 1.2);
//	glPopMatrix();
//
//	//prism - upper jaw - right
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(1.3, 0, -3.85);
//	glRotatef(180, 1, 0, 0);
//	glRotatef(90, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	glScalef(1.5, 1.5, 1.5);
//	drawTriangularPrism(1.9, 0.7, 1.2);
//	glPopMatrix();
//
//	//cheek - left
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(-2, 0.6, -3.7);
//	drawCuboid(1, 0.9, 2.7);
//	glPopMatrix();
//
//	//cheek - right
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(2, 0.6, -3.7);
//	drawCuboid(1, 0.9, 2.7);
//	glPopMatrix();
//
//	//cheek - rings - right
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(2.8, 0.6, -4);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//cheek - rings - left
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(-2.8, 0.6, -4);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPushMatrix();
//	glTranslatef(0, 0, 0.8);
//	drawCuboid(0.7, 1.2, 0.2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//}
//
////animation - mouth
//void jawAnimation() {
//	if (!jawAnimationStatus)
//	{
//		jawRot += jawRotSpeed;
//		if (jawRot > 2) {
//			jawRotSpeed = 0;
//		}
//	}
//	else if (jawAnimation)
//	{
//		jawRot -= jawRotSpeed;
//		if (jawRot < 0) {
//			jawRotSpeed = 0;
//		}
//	}
//}
//
//void jaw() {
//	jawAnimation();
//
//	//upper & lower jaw
//	glPushMatrix();
//	glRotatef(-jawRot, 1, 0, 0);
//	glTranslatef(0, jawRot / 2, 0);
//	glScalef(1, 1, 0.7);
//	upperJaw();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -jawRot / 2, 0);
//	glRotatef(jawRot, 1, 0, 0);
//	glScalef(1, 1, 0.5);
//	lowerJaw();
//	glPopMatrix();
//}
//
////Main Head - Initialize
//void robotHead() {
//
//
//	switch (textureNo) {
//	case 1:
//		textureArr[7] = loadTexture("HeadMetal.bmp");
//		break;
//	case 2:
//		textureArr[7] = loadTexture("BodyConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glTranslatef(0, 0, 2);
//
//	//main base
//	glPushMatrix();
//	glColor3f(c(98), c(172), c(75));
//	glTranslatef(0, 1, -9);
//	glRotatef(-20, 1, 0, 0);
//	drawSphereWithoutGLU(5.5, 6, 3, 1);
//	glPopMatrix();
//
//	//eyebrow
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glTranslatef(0, 3.8, -7.3);
//	glRotatef(-10, 1, 0, 0);
//	drawCuboid(3, 0.5, 2.5);
//	glPopMatrix();
//
//	//sphere - eyes
//	glPushMatrix();
//	glColor3f(0, 0, 0);
//	glTranslatef(1.7, 2.9, -6.1);
//	drawSphere(0.6);
//	glPopMatrix();
//
//	//sphere - eyes
//	glPushMatrix();
//	glColor3f(0, 0, 0);
//	glTranslatef(-1.7, 2.9, -6.1);
//	drawSphere(0.6);
//	glPopMatrix();
//
//	//pyramid
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(1.3, 2.3, -6.5);
//	drawPyramid(2, 1, 2);
//	glPopMatrix();
//
//	//pyramid
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(-1.3, 2.3, -6.5);
//	drawPyramid(2, 1, 2);
//	glPopMatrix();
//
//	//ear - pyramid - right
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(-2.7, 5.3, -8);
//	glRotatef(-40, 0, 1, 0);
//	drawPyramid(2, 1.5, 0.5);
//	glPopMatrix();
//
//	//in ear - right
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(-2.9, 5.3, -7.8);
//	glRotatef(-40, 0, 1, 0);
//	drawPyramid(1, 0.7, 0.2);
//	glPopMatrix();
//
//	//ear - pyramid - right
//	glPushMatrix();
//	glColor3f(c(125), c(84), c(66));
//	glTranslatef(2.7, 5.3, -8);
//	glRotatef(40, 0, 1, 0);
//	drawPyramid(2, 1.5, 0.5);
//	glPopMatrix();
//
//	//in ear - right
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(2.9, 5.3, -7.8);
//	glRotatef(40, 0, 1, 0);
//	drawPyramid(1, 0.7, 0.2);
//	glPopMatrix();
//
//	glColor3f(c(192), c(192), c(192));
//
//	//under ear - left
//	glPushMatrix();
//	glTranslatef(-2.5, 1.3, -7);
//	glRotated(30, 0, 0, 1);
//	glRotatef(-48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-2, -0.5, -7);
//	glRotated(45, 0, 0, 1);
//	glRotatef(-48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-1, -2, -7);
//	glRotated(65, 0, 0, 1);
//	glRotatef(-48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	//under ear - left
//	glPushMatrix();
//	glTranslatef(2.5, 1.3, -7);
//	glRotated(-30, 0, 0, 1);
//	glRotatef(48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(2, -0.5, -7);
//	glRotated(-45, 0, 0, 1);
//	glRotatef(48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(1, -2, -7);
//	glRotated(-65, 0, 0, 1);
//	glRotatef(48, 0, 1, 0);
//	glRotatef(-90, 1, 0, 0);
//	drawPyramid(1.6, 1.5, 1.6);
//	glPopMatrix();
//
//	glPopMatrix();
//
//	jaw();
//
//	glPushMatrix();
//	glTranslatef(0, -4, -7);
//	glColor3f(c(98), c(172), c(75));
//	drawCuboid(1.5, 2, 1);
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[7]);
//}
//
//void robotWingRight() {
//	//wing right
//	glPushMatrix();
//	glTranslatef(5, 0, 0);
//	glRotated(150, 0, 1, 0);
//
//	glColor3f(c(125), c(84), c(66));
//
//	//upper main - right
//	glPushMatrix();
//	drawCylinder(3, 2, 10);
//	glPushMatrix();
//	glTranslatef(0, 0, 9.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 2, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 2, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 1, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(1, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.5);
//	glRotatef(-10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//side main - right
//	glPushMatrix();
//	glTranslatef(0, 17.5, 19.5);
//	glRotatef(65, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//
//	//outer
//	glPushMatrix();
//	glTranslatef(-0.3, 6, 20.4);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1.95, 10, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.2, 3, 22);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.2, 0, 21);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -2);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -2);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//Between 
//	glColor3f(c(125), c(84), c(66));
//
//	glPushMatrix();
//	glTranslatef(0, 0, 11.2);
//	glRotatef(85, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//
//	//inner
//	glPushMatrix();
//	glTranslatef(-0.2, -5, 9.8);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -0.7);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void robotWingLeft() {
//	glPushMatrix();
//	glTranslatef(-5, 0, 0);
//	glRotated(-150, 0, 1, 0);
//	glScalef(-1, 1, 1);
//	//wing left
//	glColor3f(c(125), c(84), c(66));
//
//	//upper main - right
//	glPushMatrix();
//	drawCylinder(3, 2, 10);
//	glPushMatrix();
//	glTranslatef(0, 0, 9.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 2, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 2, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(2, 1, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.3);
//	glRotatef(-20, 1, 0, 0);
//	drawCylinder(1, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 4.5);
//	glRotatef(-10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//side main - right
//	glPushMatrix();
//	glTranslatef(0, 17.5, 19.5);
//	glRotatef(65, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//
//	//outer
//	glPushMatrix();
//	glTranslatef(-0.3, 6, 20.4);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1.95, 10, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.2, 3, 22);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.2, 0, 21);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 8, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -2);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -2);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPushMatrix();
//	glTranslatef(-2, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 7, 2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//Between 
//	glColor3f(c(125), c(84), c(66));
//
//	glPushMatrix();
//	glTranslatef(0, 0, 11.2);
//	glRotatef(85, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0.5, 5);
//	glPushMatrix();
//	glTranslatef(0, 0, 5);
//	glRotatef(10, 1, 0, 0);
//	drawCylinder(0.5, 0, 5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//
//	//inner
//	glPushMatrix();
//	glTranslatef(-0.2, -5, 9.8);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-90, 0, 1, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -1);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, -0.7);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPushMatrix();
//	glTranslatef(-1.5, 0, 0);
//	drawSphereWithoutGLU(1.5, 1, 6, 2);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
////animation - wing
//void wingAnimation() {
//	if (wingAnimationStatus)
//	{
//		wingRot -= wingRotSpeed;
//		if (wingRot < -30 || wingRot > 0) {
//			wingRotSpeed = -wingRotSpeed;
//		}
//	}
//	else
//	{
//		wingRot = 0;
//	}
//}
//
////Main Wings - Initialize
//void wings() {
//	wingAnimation();
//
//	//left
//	glPushMatrix();
//	glTranslatef(1, 5, 0);
//	glRotatef(wingRot, 0, 1, 0);
//	glScalef(0.6, 0.5, 0.5);
//	robotWingLeft();
//	glPopMatrix();
//
//	//right
//	glPushMatrix();
//	glTranslatef(-1, 5, 0);
//	glRotatef(-wingRot, 0, 1, 0);
//	glScalef(0.6, 0.5, 0.5);
//	robotWingRight();
//	glPopMatrix();
//}
//
////animation - tail
//void tailAnimation() {
//	if (tailAnimationStatus)
//	{
//		tailRot -= tailRotSpeed;
//		if (tailRot < -7 || tailRot > 7) {
//			tailRotSpeed = -tailRotSpeed;
//		}
//
//	}
//	else
//	{
//		tailRot = 0;
//	}
//}
//
//void tailPart1() {
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(1, 0.8, 2); // 1
//
//	glColor3f(c(188), c(141), c(63));
//	//pattern 1 - top
//	glPushMatrix();
//	glTranslatef(0, 0.95, 0.9);
//	glRotatef(95.8, 1, 0, 0);
//	drawHexagon(0.6, 0.6, 0.3);
//	glPopMatrix();
//
//	//pattern 1 - bottom
//	glPushMatrix();
//	glTranslatef(0, -0.95, 0.9);
//	glRotatef(-95.8, 1, 0, 0);
//	drawHexagon(0.6, 0.6, 0.3);
//	glPopMatrix();
//
//	//pattern 1 - right
//	glPushMatrix();
//	glTranslatef(0.95, 0, 0.9);
//	glRotatef(90, 0, 0, 1);
//	glRotatef(-95.8, 1, 0, 0);
//	drawHexagon(0.6, 0.6, 0.3);
//	glPopMatrix();
//
//	//pattern 1 - left
//	glPushMatrix();
//	glTranslatef(-0.95, 0, 0.9);
//	glRotatef(-90, 0, 0, 1);
//	glRotatef(-95.8, 1, 0, 0);
//	drawHexagon(0.6, 0.6, 0.3);
//	glPopMatrix();
//
//}
//
//void tailPart2() {
//	glColor3f(c(98), c(172), c(75));
//
//	glPushMatrix();
//	glTranslatef(0, -0.1, 1.4);
//	glRotatef(-30, 1, 0, 0);
//	drawCylinder(0.8, 0.7, 2); // 2
//	glPopMatrix();
//
//	glColor3f(c(188), c(141), c(63));
//
//	glPushMatrix();
//	glTranslatef(0, 0.13, 0);
//
//	//patter 2 - top
//	glPushMatrix();
//	glTranslatef(0, 1.2, 2.2);
//	glRotatef(60, 1, 0, 0);
//	drawHexagon(0.4, 0.4, 0.3);
//	glPopMatrix();
//
//	//patter 2 - bottom
//	glPushMatrix();
//	glTranslatef(0, -0.1, 2.7);
//	glRotatef(60, 1, 0, 0);
//	drawHexagon(0.4, 0.4, 0.3);
//	glPopMatrix();
//
//	//patter 2 - right
//	glPushMatrix();
//	glTranslatef(0.5, 0.45, 2.7);
//	glRotatef(90, 0, 1, 0);
//	drawHexagon(0.4, 0.4, 0.3);
//	glPopMatrix();
//
//	//patter 2 - left
//	glPushMatrix();
//	glTranslatef(-0.8, 0.45, 2.7);
//	glRotatef(90, 0, 1, 0);
//	drawHexagon(0.4, 0.4, 0.3);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void tailPart3() {
//	glPushMatrix();
//	glTranslatef(0, 0.65, 2.96);
//	glRotatef(-60, 1, 0, 0);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(0.7, 0, 2); // 3
//	glPopMatrix();
//}
//
////Main Tail - Initialize
//void robotTail() {
//	tailAnimation();
//
//	switch (textureNo) {
//	case 1:
//		textureArr[6] = loadTexture("ShellMetal.bmp");
//		break;
//	case 2:
//		textureArr[6] = loadTexture("ShellConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glRotatef(30, 1, 0, 0);
//
//	//tail - base
//	glPushMatrix();
//	glTranslatef(0, 0, -1);
//	glColor3f(c(98), c(172), c(75));
//	drawCylinder(1.5, 1, 1);
//	glPopMatrix();
//
//	//tail - 1
//	glPushMatrix();
//	glTranslatef(0, 0, -0.1);
//	glRotatef(tailRot, 0, 1, 0);
//
//	tailPart1(); // 1
//
//	glPushMatrix();
//	glTranslatef(0, -0.02, 0.1);
//	tailPart2(); // 2
//	glPopMatrix();
//
//	tailPart3(); //  3
//
//	glPopMatrix();
//
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[6]);
//}
//
////Ground - Initialize
//void ground() {
//	glPushMatrix();
//	glTranslatef(-75, -2, -75);
//	textureArr[1] = loadTexture("dirt.bmp");
//	drawSquare(150, 150);
//	glDeleteTextures(1, &textureArr[1]);
//	glPopMatrix();
//}
//
////Stand - Initialize
//void standRIng() {
//
//	glPushMatrix();
//	glTranslatef(0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//
//	textureArr[0] = loadTexture("grass.bmp");
//	drawCylinder(25, 25, 5);
//	glDeleteTextures(1, &textureArr[0]);
//
//	glPopMatrix();
//}
//
////Info Box - Initialize
//void infoBox() {
//	glLineWidth(5);
//	glPushMatrix();
//	glTranslatef(10, 25, 0);
//
//	glColor3f(0, 0, 1);
//	//Draw 'B'
//	glPushMatrix();
//	glTranslatef(-4.8, 0, 0);
//
//	glPushMatrix();
//	glBegin(GL_LINES);
//	glVertex2f(0, -0.6);
//	glVertex2f(0, 0.6);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0.3, 0);
//	glRotatef(-90, 0, 0, 1);
//	drawLineCircle(0.3, 0.5, 1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -0.3, 0);
//	glRotatef(-90, 0, 0, 1);
//	drawLineCircle(0.3, 0.5, 1);
//	glPopMatrix();
//	glPopMatrix();
//
//	//Draw 'L'
//	glPushMatrix();
//	glTranslatef(-4.1, 0, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(0, 0.6);
//	glVertex2f(0, -0.6);
//	glVertex2f(0.5, -0.6);
//	glEnd();
//	glPopMatrix();
//
//	//Draw 'A'
//	glPushMatrix();
//	glTranslatef(-2.95, 0, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(-0.5, -0.6);
//	glVertex2f(0, 0.6);
//	glVertex2f(0.5, -0.6);
//	glVertex2f(0.25, 0);
//	glVertex2f(-0.25, 0);
//	glEnd();
//	glPopMatrix();
//
//	//Draw 'S'
//	glPushMatrix();
//	glTranslatef(-1.9, 0.25, 0);
//	glRotatef(-30, 0, 0, 1);
//
//	glPushMatrix();
//	glRotatef(90, 0, 0, 1);
//	drawLineCircle(0.3, 0.5, 1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -0.6, 0);
//	glRotatef(-90, 0, 0, 1);
//	drawLineCircle(0.3, 0.5, 1);
//	glPopMatrix();
//
//	glPopMatrix();
//
//	//Draw 'T'
//	glPushMatrix();
//	glTranslatef(-1.2, -0.05, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(-0.45, 0.6);
//	glVertex2f(0.45, 0.61);
//	glVertex2f(0, 0.61);
//	glVertex2f(0, -0.61);
//	glEnd();
//	glPopMatrix();
//
//	//Health
//	glColor3f(1, 0, 0);
//	glPushMatrix();
//	glTranslatef(-4.8, -1.6, 0);
//	glRotatef(90, 0, 1, 0);
//	drawCylinder(0.7, 0.7, 9.85);
//	glPushMatrix();
//
//	glColor3f(0, 1, 0);
//	glTranslatef(0, 0, -0.1);
//	drawCylinder(0.75, 0.75, hpAmount);
//	glPopMatrix();
//	glPopMatrix();
//
//	glColor3f(0, 0, 1);
//	//Male Symbol
//	glPushMatrix();
//	glTranslatef(-0.3, -0.3, 0);
//	drawLineCircle(0.3, 0.3, 2);
//
//	glPushMatrix();
//	glTranslatef(0.2, 0.2, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(0, 0);
//	glVertex2f(0.4, 0.4);
//	glVertex2f(0.1, 0.4);
//	glVertex2f(0.4, 0.4);
//	glVertex2f(0.4, 0.1);
//	glEnd();
//	glPopMatrix();
//	glPopMatrix();
//
//	//Level
//	//Draw 'L'
//	glPushMatrix();
//	glTranslatef(3, 0, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(0, 0.6);
//	glVertex2f(0, -0.6);
//	glVertex2f(0.5, -0.6);
//	glEnd();
//	glPopMatrix();
//
//	//Draw 'V'
//	glPushMatrix();
//	glTranslatef(3.7, 0, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(-0.3, 0.6);
//	glVertex2f(0, -0.6);
//	glVertex2f(0.3, 0.6);
//	glEnd();
//	glPopMatrix();
//
//	//Draw '.'
//	glPushMatrix();
//	glTranslatef(4.1, -0.55, 0);
//	drawCircle(0.1, 0.1);
//	glPopMatrix();
//
//	//Draw '1'
//	glPushMatrix();
//	glTranslatef(4.65, 0, 0);
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(-0.25, 0.45);
//	glVertex2f(0, 0.6);
//	glVertex2f(0, -0.6);
//	glVertex2f(-0.3, -0.6);
//	glVertex2f(0.3, -0.6);
//	glEnd();
//	glPopMatrix();
//
//	//Container
//	glColor3f(1, 0, 1);
//	glPushMatrix();
//	glTranslatef(0.2, -0.8, -0.41);
//	drawCuboid(5.4, 1.8, 0.4);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(1, 1, 1);
//}
//
////Background - initialize
//void worldSphere() {
//	glPushMatrix();
//	textureArr[2] = loadTexture("Sky.bmp");
//	drawSphere(75);
//	glDeleteTextures(1, &textureArr[2]);
//	glPopMatrix();
//}
//
////lighting
//void lighting() {
//	if (isLightOn) {
//		//enable lighting for the scene
//		glEnable(GL_LIGHTING);
//	}
//	else {
//		//disable lighting for the scene
//		glDisable(GL_LIGHTING);
//	}
//
//	float amb[] = { 1,1,1,1 };
//	float dif[] = { 1,1,1,1 };
//	float pos[] = { lightX - 2, lightY, lightZ, 0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, pos);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
//
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
//}
//
////Eugene
//
////Robot Body
//void bodyLayerOne() {
//
//	glPushMatrix();
//
//	glRotatef(-5, 1, 0, 0);
//
//	//Left - Light Purple
//	glPushMatrix();
//	glColor3f(1, 0, 1);
//	glTranslatef(3, 9.5, 5.5);
//	drawCuboid(1, 0.5, 1);
//	glPopMatrix();
//
//	//Right - Light Purple
//	glPushMatrix();
//	glColor3f(1, 0, 1);
//	glTranslatef(-3, 9.5, 5.5);
//	drawCuboid(1, 0.5, 1);
//	glPopMatrix();
//
//	//Left - Purple
//	glPushMatrix();
//	glTranslatef(-4.5, 8, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 1);
//	drawTriangularPrism(1, 2, 0.5);
//	glPopMatrix();
//
//	//Right - Purple
//	glPushMatrix();
//	glTranslatef(4.5, 8, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 1);
//	drawTriangularPrism(1, 2, 0.5);
//	glPopMatrix();
//
//	//Left - Blue
//	glPushMatrix();
//	glColor3f(0, 0, 1);
//	glTranslatef(-5.5, 6.5, 5.5);
//	drawCuboid(0.5, 1.5, 1);
//	glPopMatrix();
//
//	//Right - Blue
//	glPushMatrix();
//	glColor3f(0, 0, 1);
//	glTranslatef(5.5, 6.5, 5.5);
//	drawCuboid(0.5, 1.5, 1);
//	glPopMatrix();
//
//	//Left - Dark Purple
//	glPushMatrix();
//	glTranslatef(-6.5, 5.5, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 0.5);
//	drawTriangularPrism(1, 2.5, 0.5);
//	glPopMatrix();
//
//	//Right - Dark Purple
//	glPushMatrix();
//	glTranslatef(6.5, 5.5, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 0.5);
//	drawTriangularPrism(1, 2.5, 0.5);
//	glPopMatrix();
//
//	//Left - Dark Purple
//	glPushMatrix();
//	glTranslatef(-1.5, 9, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 0.5);
//	drawTriangularPrism(1, 1, 0.5);
//	glPopMatrix();
//
//	//Right - Dark Purple
//	glPushMatrix();
//	glTranslatef(1.5, 9, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(0.5, 0.1, 0.5);
//	drawTriangularPrism(1, 1, 0.5);
//	glPopMatrix();
//
//	//Center - Light Yellow
//	glPushMatrix();
//	glColor3f(1, 1, 0.5);
//	glTranslatef(0, 7, 5.5);
//	drawCuboid(4, 2, 1);
//	glPopMatrix();
//
//	//Left - Orange
//	glPushMatrix();
//	glColor3f(1, 0.5, 0);
//	glTranslatef(-3.5, 6.5, 5.5);
//	drawCuboid(2, 1.5, 0.99);
//	glPopMatrix();
//
//	//Right - Orange
//	glPushMatrix();
//	glColor3f(1, 0.5, 0);
//	glTranslatef(3.5, 6.5, 5.5);
//	drawCuboid(2, 1.5, 0.99);
//	glPopMatrix();
//
//	glPopMatrix();
//
//}
//
//void bodyLayerTwo() {
//
//	//Second Layer
//	glPushMatrix();
//
//	glRotatef(1, 1, 0, 0);
//
//	//Upper
//	//First Layer - Center Cuboid (Red)
//	glPushMatrix();
//
//	glScalef(1.5, 1, 1);
//	glTranslatef(0, 4, 5);
//	glColor3f(1, 0, 0);
//
//	drawCuboid(4, 2, 1);
//
//	//First Layer - Right Top PrismTriangle (Yellow)
//	glPushMatrix();
//
//	glColor3f(1, 1, 0);
//	glScalef(2, 1, 2);
//	glTranslatef(2, 2, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right Down PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(1, 0, 1);
//	glScalef(1, 4, 2);
//	glTranslatef(4, 0, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left Top PrismTriangle (Yellow)
//	glPushMatrix();
//
//	glColor3f(1, 1, 0);
//	glScalef(2, 1, 2);
//	glTranslatef(-2, 2, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left Down PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(1, 0, 1);
//	glScalef(1, 4, 2);
//	glTranslatef(-4, 0, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	//Lower
//	//First Layer - Center Cuboid (Blue)
//	glPushMatrix();
//
//	glTranslatef(0, 1, 5);
//
//	glColor3f(0, 0, 1);
//	drawCuboid(2.5, 1, 1);
//
//	glPushMatrix();
//
//	//First Layer - Left PrismTriangle (Green)
//	glPushMatrix();
//
//	glColor3f(0, 1, 0);
//	glScalef(3.5, 1, 2);
//	glTranslatef(-0.75, 0.5, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left PrismTriangle (Purple)
//	//glPushMatrix();
//
//	glColor3f(1, 0, 1);
//	glScalef(1.5, 2, 2.1); //Should be 2 for Z-axis
//	glTranslatef(-1.65, 0, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right PrismTriangle (Green)
//	glPushMatrix();
//
//	glColor3f(0, 1, 0);
//	glScalef(3.5, 1, 2);
//	glTranslatef(0.75, 0.5, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(1, 0, 1);
//	glScalef(1.5, 2, 2.1); //Should be 2 for Z-axis
//	glTranslatef(1.65, 0, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void bodyLayerThree() {
//
//	//Third Layer
//	glPushMatrix();
//
//	glRotatef(5, 1, 0, 0);
//
//	//Right - PrismTriangle (Orange)
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(4, 0, 4.5);
//	glRotatef(90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(1, 1.5, 3);
//	glPopMatrix();
//
//	//Left - PrismTriangle (Orange)
//	glPushMatrix();
//
//	glTranslatef(-4, 0, 4.5);
//	glRotatef(-90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(1, 1.5, 3);
//	glPopMatrix();
//
//	//Right - PrismTriangle (Orange)
//	glPushMatrix();
//
//	glTranslatef(3, -3, 4.5);
//	glRotatef(180, 1, 0, 0);
//	glRotatef(90, 0, 1, 0);
//	drawTriangularPrism(1, 1, 1);
//	glPopMatrix();
//
//	//Left - PrismTriangle (Orange)
//	glPushMatrix();
//
//	glTranslatef(-3, -3, 4.5);
//	glRotatef(180, 1, 0, 0);
//	glRotatef(-90, 0, 1, 0);
//	drawTriangularPrism(1, 1, 1);
//	glPopMatrix();
//
//	//Right - PrismTriangle (Orange)
//	glPushMatrix();
//
//	glTranslatef(2, -5, 4.5);
//	glRotatef(90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(1, 1, 2);
//	glPopMatrix();
//
//	//Left - PrismTriangle (Orange)
//	glPushMatrix();
//
//	glTranslatef(-2, -5, 4.5);
//	glRotatef(-90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(1, 1, 2);
//	glPopMatrix();
//
//	//Center(Upper) - Cuboid (Blue)
//	glPushMatrix();
//	glTranslatef(0, -0.5, 4.5);
//	glColor3f(c(186), c(158), c(124));
//	drawCuboid(4, 2.5, 1);
//	glPopMatrix();
//
//	//Center(Below) - Cuboid (Blue)
//	glPushMatrix();
//	glTranslatef(0, -5, 4.5);
//	glColor3f(c(186), c(158), c(124));
//	drawCuboid(2, 2, 1);
//	glPopMatrix();
//
//
//	//Right Cylinder (Outside)
//	glPushMatrix();
//	glRotatef(-5, 1, 0, 0);
//	glRotatef(-5, 0, 0, 1);
//	glTranslatef(2.9, 0.5, 4.75);
//	glColor3f(0, 0, 0);
//	drawCylinder(1.5, 1.5, 1);
//	glPopMatrix();
//
//	//Right Cylinder (Inside)
//	glPushMatrix();
//	glRotatef(-5, 1, 0, 0);
//	glRotatef(-5, 0, 0, 1);
//	glTranslatef(3, 0.4, 4.8);
//	glColor3f(c(192), c(192), c(192));
//	drawCylinder(1.1, 1.1, 1);
//	glPopMatrix();
//
//	//Left Cylinder (Outside)
//	glPushMatrix();
//	glRotatef(-5, 1, 0, 0);
//	glRotatef(5, 0, 0, 1);
//	glTranslatef(-2.9, 0.5, 4.75);
//	glColor3f(0, 0, 0);
//	drawCylinder(1.5, 1.5, 1);
//	glPopMatrix();
//
//	//Left Cylinder (Inside)
//	glPushMatrix();
//	glRotatef(-5, 1, 0, 0);
//	glRotatef(5, 0, 0, 1);
//	glTranslatef(-3, 0.4, 4.8);
//	glColor3f(c(192), c(192), c(192));
//	drawCylinder(1.1, 1.1, 1);
//	glPopMatrix();
//
//	glPopMatrix();
//
//}
//
//void leftLegConnection() {
//
//	glPushMatrix();
//
//	glTranslatef(2.5, -5, 2);
//
//	glRotatef(-15, 0, 0, 1);
//
//	glRotatef(90, 0, 1, 0);
//
//	glColor3f(0, 0, 0);
//	glColor3f(1, 0, 1);
//	drawPolygonPrism(2.5, 2.5, 2, 8);
//	glPushMatrix();
//	glColor3f(0, 0, 0);
//	drawCover(2.5, 2.5, 8);
//	glTranslatef(0, 0, 2);
//	drawCover(2.5, 2.5, 8);
//	glPopMatrix();
//
//	glPopMatrix();
//
//}
//
//void rightLegConnection() {
//	glPushMatrix();
//
//	glTranslatef(-2.5, -5, 2);
//
//	glRotatef(15, 0, 0, 1);
//
//	glRotatef(-90, 0, 1, 0);
//
//	glColor3f(0, 0, 0);
//	glColor3f(1, 0, 1);
//	drawPolygonPrism(2.5, 2.5, 2, 8);
//	glPushMatrix();
//	glColor3f(0, 0, 0);
//	drawCover(2.5, 2.5, 8);
//	glTranslatef(0, 0, 2);
//	drawCover(2.5, 2.5, 8);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void leftHandConnection() {
//	glPushMatrix();
//
//	glTranslatef(-6.5, 5, 2);
//
//	glRotatef(15, 0, 0, 1);
//
//	glRotatef(-90, 0, 1, 0);
//
//	glColor3f(1.0, 0.5, 1.0);
//	drawPolygonPrism(2.5, 2.5, 2, 8);
//	glColor3f(0, 0, 0);
//	drawPolygonPrism(2, 2, 2.05, 8);
//	glPopMatrix();
//}
//
//void rightHandConnection() {
//	glPushMatrix();
//
//	glTranslatef(6.5, 5, 2);
//
//	glRotatef(-15, 0, 0, 1);
//
//	glRotatef(90, 0, 1, 0);
//
//	glColor3f(1.0, 0.5, 1.0);
//	drawPolygonPrism(2.5, 2.5, 2, 8);
//	glColor3f(0, 0, 0);
//	drawPolygonPrism(2, 2, 2.05, 8);
//
//	glPopMatrix();
//}
//
//void bodyContaint() {
//	//Body Front Background
//
//	glPushMatrix();
//
//	glTranslatef(0, -1, 0);
//	glScalef(1.15, 1.2, 1);
//
//	//Center
//	glPushMatrix();
//	glTranslatef(0, 5.5, 2);
//	drawCuboid(8, 2.5, 2.5);
//	glPopMatrix();
//
//	//Right
//	glPushMatrix();
//	glTranslatef(3.5, -1, 2);
//	glRotatef(90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(2.5, 4.5, 4);
//	glPopMatrix();
//
//	//Left
//	glPushMatrix();
//	glTranslatef(-3.5, -1, 2);
//	glRotatef(-90, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(2.5, 4.5, 4);
//	glPopMatrix();
//
//	//Center
//	glPushMatrix();
//	glTranslatef(0, -1.5, 2);
//	drawCuboid(3.5, 4.5, 2.5);
//	glPopMatrix();
//
//	//Top
//	glPushMatrix();
//	glTranslatef(0, 9.25, 2);
//	drawCuboid(4, 1.25, 2.5);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-6, 8, 2);
//	glRotatef(-90, 0, 1, 0);
//	drawTriangularPrism(2.5, 2.5, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(6, 8, 2);
//	glRotatef(90, 0, 1, 0);
//	drawTriangularPrism(2.5, 2.5, 2);
//	glPopMatrix();
//
//
//
//	glPopMatrix();
//}
//
//void bodyBack() {
//	switch (textureNo) {
//	case 1:
//		textureArr[6] = loadTexture("ShellMetal.bmp");
//		break;
//	case 2:
//		textureArr[6] = loadTexture("ShellConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//
//	glRotatef(-10, 1, 0, 0);
//	glTranslatef(0, 3, 1);
//	//glScalef(0.9, 0.9, 0.9);
//
//	//Center - Black
//	glPushMatrix();
//	glColor3f(0, 0, 0);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glColor3f(c(188), c(141), c(63));
//
//	glPushMatrix();
//	glRotatef(-15, 1, 0, 0);
//	glTranslatef(0, 4.6, 0.6);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(15, 0, 1, 0);
//	glRotatef(-9, 1, 0, 0);
//	glTranslatef(3.75, 2.25, 0.65);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(-15, 0, 1, 0);
//	glRotatef(-9, 1, 0, 0);
//	glTranslatef(-3.75, 2.25, 0.65);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(-15, 0, 1, 0);
//	glRotatef(9, 1, 0, 0);
//	glTranslatef(-3.75, -2.25, 0.65);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(15, 0, 1, 0);
//	glRotatef(9, 1, 0, 0);
//	glTranslatef(3.75, -2.25, 0.65);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(15, 1, 0, 0);
//	glTranslatef(0, -4.6, 0.6);
//	drawHexagon(3, 3, 2);
//	glPopMatrix();
//
//	//Second Layer
//
//	glColor3f(c(192), c(192), c(192));
//
//	glPushMatrix();
//	glTranslatef(0, 7.5, -1.2);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//
//	glPushMatrix();
//	glTranslatef(-2, 6, -1.2);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-4, 5, -1.5);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-6, 3.5, -1.5);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-6, 1, -1.5);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-6, -1.5, -1.6);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-6, -4, -1.6);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-4, -5.1, -1.6);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(2, 6, -1.2);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-2, -6.5, -1.6);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -7.5, -1.2);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(4, 5, -1.5);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(6, 3.5, -1.5);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(6, 1, -1.5);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(6, -1.5, -1.6);
//	glRotatef(-60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(6, -4, -1.6);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(4, -5.1, -1.6);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(2, -6.5, -1.6);
//	glRotatef(60, 0, 0, 1);
//	drawCuboid(2, 1, 2);
//	glPopMatrix();
//
//	glPopMatrix();
//	glDeleteTextures(1, &textureArr[6]);
//}
//
//void canonDesignMuzzle() {
//	//Red - Canon - Design - Up
//	glPushMatrix();
//
//	glColor3f(1, 0, 0);
//	glTranslatef(0, 2.9, 7);
//	glRotatef(-3.576, 1, 0, 0);
//
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, -1.5);
//	glRotatef(180, 0, 1, 0);
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	drawCuboid(0.5, 0.5, 1);
//
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, 1);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 1, 1);
//
//	glPopMatrix();
//
//	glPushMatrix();
//
//	glTranslatef(0, -1, 0.25);
//	drawCuboid(0.5, 0.5, 0.75);
//
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -1, -0.5);
//	glRotatef(180, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 0.5, 0.5);
//	glPopMatrix();
//
//	glPopMatrix();
//
//	//Red - Canon - Design - Left
//	glPushMatrix();
//
//	glTranslatef(-2.9, 0, 7);
//
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glRotatef(90, 0, 0, 1);
//
//	glRotatef(-3.576, 1, 0, 0);
//
//	glPushMatrix();
//	glTranslatef(0, -0.5, -1.5);
//	glRotatef(180, 0, 1, 0);
//	drawTriangularPrism(0.5, 1, 0.5);
//	glPopMatrix();
//
//	drawCuboid(0.5, 0.5, 1);
//
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, 1);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 1, 1);
//
//	glPopMatrix();
//
//	glPushMatrix();
//
//	glTranslatef(0, -1, 0.25);
//	drawCuboid(0.5, 0.5, 0.75);
//
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -1, -0.5);
//	glRotatef(180, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 0.5, 0.5);
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//
//	//Red - Canon - Design - Down
//	glPushMatrix();
//
//	glTranslatef(0, -2.9, 7);
//
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glRotatef(180, 0, 0, 1);
//
//	glRotatef(-3.576, 1, 0, 0);
//
//	glPushMatrix();
//	glTranslatef(0, -0.5, -1.5);
//	glRotatef(180, 0, 1, 0);
//	drawTriangularPrism(0.5, 1, 0.5);
//	glPopMatrix();
//
//	drawCuboid(0.5, 0.5, 1);
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, 1);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 1, 1);
//
//	glPopMatrix();
//
//	glPushMatrix();
//
//	glTranslatef(0, -1, 0.25);
//	drawCuboid(0.5, 0.5, 0.75);
//
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -1, -0.5);
//	glRotatef(180, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 0.5, 0.5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//
//	//Red - Canon - Design - Down
//	glPushMatrix();
//
//	glTranslatef(2.9, 0, 7);
//
//	glPushMatrix();
//	glColor3f(1, 0, 0);
//	glRotatef(-90, 0, 0, 1);
//
//	glRotatef(-3.576, 1, 0, 0);
//
//	glPushMatrix();
//	glTranslatef(0, -0.5, -1.5);
//	glRotatef(180, 0, 1, 0);
//	drawTriangularPrism(0.5, 1, 0.5);
//	glPopMatrix();
//
//	drawCuboid(0.5, 0.5, 1);
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, 1);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 1, 1);
//
//	glPopMatrix();
//
//	glPushMatrix();
//
//	glTranslatef(0, -1, 0.25);
//	drawCuboid(0.5, 0.5, 0.75);
//
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -1, -0.5);
//	glRotatef(180, 0, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	drawTriangularPrism(0.5, 0.5, 0.5);
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//}
//
//void canonShell() {
//
//	glPushMatrix();
//
//	glRotatef(45, 0, 1, 0);
//	glRotatef(-45, 0, 0, 1);
//	glTranslatef(0, 3, 1.5);
//
//	drawCuboid(0.25, 2, 0.25);
//
//	glPopMatrix();
//
//	glPushMatrix();
//
//	glRotatef(-45, 0, 1, 0);
//	glRotatef(45, 0, 0, 1);
//	glTranslatef(0, 3, 1.5);
//
//	drawCuboid(0.25, 2, 0.25);
//
//	glPopMatrix();
//
//}
//
//void canonDesign() {
//
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, -0.75);
//
//	glColor3f(1, 0, 0);
//	glTranslatef(0, 2.9, 7);
//	glRotatef(-3.576, 1, 0, 0);
//
//	glPushMatrix();
//
//	glTranslatef(0, -0.5, -3.5);
//	glColor3f(1, 0, 0);
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0, -5);
//	drawCuboid(0.5, 0.5, 1);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void canonStand() {
//
//	glColor3f(1, 0, 0);
//
//	glPushMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.5, -2.5, 2);
//	glRotatef(90, 0, 1, 0);
//	drawCylinder(1, 1, 1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -6, -1.5);
//	glRotatef(-45, 1, 0, 0);
//	drawCuboidBasedZero(0.5, 0.5, 5);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-0.5, -6, -1.5);
//	glRotatef(90, 0, 1, 0);
//	drawCylinder(1, 1, 1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, -9.5, 2);
//	glRotatef(-135, 1, 0, 0);
//	drawCuboidBasedZero(0.5, 0.5, 5);
//	glPopMatrix();
//
//	glPopMatrix();
//
//}
//
//void weaponAnimation() {
//
//	if (weaponOn) {
//		if (canonRot <= 45) {
//			canonRotSpeed = 5;
//			startFire = false;
//		}
//		else {
//			canonRotSpeed = 0;
//			startFire = true;
//		}
//	}
//	else {
//		if (canonRot > 0) {
//			canonRotSpeed = -5;
//			startFire = false;
//		}
//		else {
//			canonRotSpeed = 0;
//			startFire = false;
//		}
//	}
//
//
//}
//
//void shootingAnimation() {
//
//	glPushMatrix();
//
//	glTranslatef(0, 6, 0);
//
//
//	if (shootOn) {
//		if (powerBall <= 30) {
//			powerBallSize = 5;
//			endShoot = false;
//		}
//		else {
//			powerBallSize = 0;
//			if (attack <= 1000)
//			{
//				attackLength = 100;
//				if (attackRadius <= 2) {
//					attackRadius += 0.5;
//				}
//				endShoot = false;
//			}
//			else {
//				attackLength = 0;
//				endShoot = true;
//				shootOn = false;
//			}
//		}
//	}
//	else {
//		if (powerBall > 0)
//		{
//			powerBallSize = (-5);
//		}
//		else {
//			powerBallSize = 0;
//		}
//		if (attack > 0) {
//			attackLength = (-50);
//		}
//		else {
//			attackLength = 0;
//		}
//		if (attackRadius > 0)
//		{
//			attackRadius -= 0.5;
//		}
//		else {
//			attackRadius = 0;
//		}
//
//	}
//
//
//	glPushMatrix();
//
//	glScalef(1, 1, attack);
//	attack += attackLength;
//	if (attackRadius >= 0) {
//		drawCylinder(attackRadius, attackRadius, 0.1);
//	}
//	glPopMatrix();
//
//	glPushMatrix();
//	powerBall += powerBallSize;
//	glScalef(powerBall, powerBall, powerBall);
//	drawSphereWithoutGLU(0.1, 0.1, 0.1, 1);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
//void weapon() {
//	switch (textureNo) {
//	case 1:
//		textureArr[5] = loadTexture("CannonMetal.bmp");
//		break;
//	case 2:
//		textureArr[5] = loadTexture("CannonConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//
//	glPushMatrix();
//
//	glPushMatrix();
//	glColor3f(c(192), c(192), c(192));
//	glScalef(1.25, 1.25, 1.25);
//	drawCylinder(2, 2.5, 8);
//
//	glPushMatrix();
//	drawCylinder(2, 2.5, 7.5);
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(45, 0, 0, 1);
//	canonDesignMuzzle();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0, 7.5);
//	glColor3f(1, 0.5, 0);
//	drawSphereWithoutGLU(2.2, 2.2, 2, 1);
//	glPopMatrix();
//
//	canonDesign();
//
//	glColor3f(1, 0, 0);
//	canonShell();
//	glPopMatrix();
//
//	canonStand();
//
//	glPushMatrix();
//	glTranslatef(-0.5, -9.5, 2);
//	glRotatef(90, 0, 1, 0);
//	drawCylinder(1, 1, 1);
//	glPopMatrix();
//	;
//
//	glPopMatrix();
//
//	glDeleteTextures(1, &textureArr[5]);
//}
//
//void robotBody() {
//
//	glLineWidth(2);
//
//	//Body Front
//	switch (textureNo)
//	{
//	case 1:
//		textureArr[5] = loadTexture("BodyMetal.bmp");
//		break;
//	case 2:
//		textureArr[5] = loadTexture("BodyConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//
//	glColor3f(c(98), c(172), c(75));
//	bodyContaint();
//
//	//Layer One
//	glPushMatrix();
//
//	glRotatef(-5, 1, 0, 0);
//
//	//Left - Light Purple
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(3, 9.5, 5.5);
//	drawCuboid(1, 0.5, 1);
//	glPopMatrix();
//
//	//Right - Light Purple
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(-3, 9.5, 5.5);
//	drawCuboid(1, 0.5, 1);
//	glPopMatrix();
//
//	//Left - Purple
//	glPushMatrix();
//	glTranslatef(-4.5, 8, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 2, 0.5);
//	glPopMatrix();
//
//	//Right - Purple
//	glPushMatrix();
//	glTranslatef(4.5, 8, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 2, 0.5);
//	glPopMatrix();
//
//	//Left - Blue
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(-5.5, 6.5, 5.5);
//	drawCuboid(0.5, 1.5, 1);
//	glPopMatrix();
//
//	//Right - Blue
//	glPushMatrix();
//	glColor3f(c(188), c(141), c(63));
//	glTranslatef(5.5, 6.5, 5.5);
//	drawCuboid(0.5, 1.5, 1);
//	glPopMatrix();
//
//	//Left - Dark Purple
//	glPushMatrix();
//	glTranslatef(-6.5, 5.5, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 2.5, 0.5);
//	glPopMatrix();
//
//	//Right - Dark Purple
//	glPushMatrix();
//	glTranslatef(6.5, 5.5, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 2.5, 0.5);
//	glPopMatrix();
//
//	//Left - Dark Purple
//	glPushMatrix();
//	glTranslatef(-1.5, 9, 5.5);
//	glRotatef(90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 1, 0.5);
//	glPopMatrix();
//
//	//Right - Dark Purple
//	glPushMatrix();
//	glTranslatef(1.5, 9, 5.5);
//	glRotatef(-90, 0, 1, 0);
//	glColor3f(c(188), c(141), c(63));
//	drawTriangularPrism(1, 1, 0.5);
//	glPopMatrix();
//
//	//Center - Light Yellow
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(0, 7, 5.5);
//	drawCuboid(4, 2, 1);
//	glPopMatrix();
//
//	//Left - Orange
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(-3.5, 6.5, 5.5);
//	drawCuboid(2, 1.5, 0.99);
//	glPopMatrix();
//
//	//Right - Orange
//	glPushMatrix();
//	glColor3f(c(186), c(158), c(124));
//	glTranslatef(3.5, 6.5, 5.5);
//	drawCuboid(2, 1.5, 0.99);
//	glPopMatrix();
//
//	glPopMatrix();
//
//
//	//Second Layer
//	glPushMatrix();
//
//	glRotatef(1, 1, 0, 0);
//
//	//Upper
//	//First Layer - Center Cuboid (Red)
//	glPushMatrix();
//
//	glScalef(1.5, 1, 1);
//	glTranslatef(0, 4, 5);
//	glColor3f(c(188), c(141), c(63));
//
//	drawCuboid(4, 2, 1);
//
//	//First Layer - Right Top PrismTriangle (Yellow)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(2, 1, 2);
//	glTranslatef(2, 2, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right Down PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(1, 4, 2);
//	glTranslatef(4, 0, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left Top PrismTriangle (Yellow)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(2, 1, 2);
//	glTranslatef(-2, 2, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left Down PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(1, 4, 2);
//	glTranslatef(-4, 0, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	//Lower
//	//First Layer - Center Cuboid (Blue)
//	glPushMatrix();
//
//	glTranslatef(0, 1, 5);
//
//	glColor3f(c(186), c(158), c(124));
//	drawCuboid(2.5, 1, 1);
//
//	glPushMatrix();
//
//	//First Layer - Left PrismTriangle (Green)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(3.5, 1, 2);
//	glTranslatef(-0.75, 0.5, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Left PrismTriangle (Purple)
//	//glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(1.5, 2, 2.1); //Should be 2 for Z-axis
//	glTranslatef(-1.65, 0, 0);
//	glRotatef(-90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right PrismTriangle (Green)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(3.5, 1, 2);
//	glTranslatef(0.75, 0.5, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	//First Layer - Right PrismTriangle (Purple)
//	glPushMatrix();
//
//	glColor3f(c(186), c(158), c(124));
//	glScalef(1.5, 2, 2.1); //Should be 2 for Z-axis
//	glTranslatef(1.65, 0, 0);
//	glRotatef(90, 0, 1, 0); //Rotate Y
//	glRotatef(90, 1, 0, 0); //Rotate X
//
//	drawTriangularPrism(0.5, 1, 0.5);
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	glPopMatrix();
//
//	//Layer Three
//	bodyLayerThree();
//
//	////Left Leg Connection
//	//leftLegConnection();
//
//	////Right Leg Connection
//	//rightLegConnection();
//
//	////Left Hand Connection
//	//leftHandConnection();
//
//	////Right Hand Connection
//	//rightHandConnection();
//
//	glDeleteTextures(1, &textureArr[5]);
//	//Body Back
//	glPushMatrix();
//	glRotatef(180, 0, 1, 0);
//	//glTranslatef(0, 0, 3);
//	bodyBack();
//
//	glPopMatrix();
//
//	//right hand
//	glPushMatrix();
//	glTranslatef(-11.5, 5, 3);
//	glScalef(20, 8, 20);
//	rightHand();
//	glPopMatrix();
//
//	//left hand
//	glPushMatrix();
//	glTranslatef(11.5, 5, 3);
//	glScalef(20, 8, 20);
//	leftHand();
//	glPopMatrix();
//
//
//}
//
//void projection() {
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glTranslatef(ptx, pty, 0.0);	//tx, ty for projection
//
//	glRotatef(pry, 0.0, 1.0, 0.0);
//
//	if (isOrtho) {
//		glOrtho(-10, 10, -10, 10, -10, 10);
//	}
//	else {
//		gluPerspective(80.0, 1.0, 1, 31.0);
//	}
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHT0);
//}
//
//void skyBox() {
//	//Skybox/Plane
//
//	if (skyBoxOn)
//	{
//		infoBox();
//
//		glPushMatrix();
//		glTranslatef(0, -15, 0);
//		ground();
//		standRIng();
//		worldSphere();
//		glPopMatrix();
//	}
//
//}
//
//void display()
//{
//	lighting();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(1, 1, 1, 1);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	//Camera movement
//	glTranslatef(0.0, 0.0, zoomLevel);
//
//	glRotatef(xRotate, 1.0, 0.0, 0.0);
//	glRotatef(yRotate, 0.0, 1.0, 0.0);
//
//	glScalef(0.15, 0.15, 0.15);
//
//	glPushMatrix();
//	glRotatef(rotateBody, 0, 1, 0);
//	glTranslatef(0, 0, walkingSpeed);
//
//	glPushMatrix();
//
//	//Head
//	glPushMatrix();
//	glRotatef(headRot, 0, 1, 0);
//	glPushMatrix();
//	glRotatef(15, 1, 0, 0);
//	glTranslatef(0, 15, 8);
//	glScalef(1, 0.6, 1);
//	robotHead();
//	glPopMatrix();
//	glPopMatrix();
//
//	//glTranslatef(0, -1, 0);
//
//	glPushMatrix();
//	glRotatef(10, 1, 0, 0);
//	robotBody();
//	glPopMatrix();
//
//	//Wings
//	switch (textureNo) {
//	case 1:
//		textureArr[8] = loadTexture("WingsLava.bmp");
//		break;
//	case 2:
//		textureArr[8] = loadTexture("HandLegConcrete.bmp");
//		break;
//	default:
//		break;
//	}
//	glPushMatrix();
//	glRotatef(rotateBody, 0, 1, 0);
//	glTranslatef(0, 0, walkingSpeed);
//
//	wings();
//
//	glDeleteTextures(1, &textureArr[8]);
//
//	//Tail
//	glPushMatrix();
//	glScalef(2.5, 2.5, 2.5);
//	glRotatef(180, 0, 1, 0);
//	glTranslatef(0, -2.5, 1);
//	robotTail();
//	glPopMatrix();
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(rotateBody, 0, 1, 0);
//	glTranslatef(0, 0, walkingSpeed);
//	//right leg
//	glPushMatrix();
//	glTranslatef(-3.8, -7, -4);
//	glScalef(20, 20, 20);
//	rightLeg();
//	glPopMatrix();
//
//	//left leg
//	glPushMatrix();
//	glTranslatef(3.8, -7, -4);
//	glScalef(20, 20, 20);
//	leftLeg();
//	glPopMatrix();
//	glPopMatrix();
//
//
//	//Weapon - Right
//	glPushMatrix();
//	glRotatef(rotateBody, 0, 1, 0);
//	glTranslatef(0, 0, walkingSpeed);
//	glTranslatef(-7, 8, 2);
//
//	glPushMatrix();
//	glRotatef(45, 0, 0, 1);
//	glRotatef(-45 + canonRot, 1, 0, 0);
//	canonRot += canonRotSpeed;
//	glScalef(0.8, 0.8, 0.8);
//	glTranslatef(0, 9.5, -2);
//	weapon();
//
//	glPopMatrix();
//	glPopMatrix();
//
//	//Weapon - Left
//	glPushMatrix();
//	glRotatef(rotateBody, 0, 1, 0);
//	glTranslatef(0, 0, walkingSpeed);
//	glTranslatef(7, 8, 2);
//
//	glPushMatrix();
//	glRotatef(-45, 0, 0, 1);
//	glRotatef(-45 + canonRot, 1, 0, 0);
//	canonRot += canonRotSpeed;
//	glScalef(0.8, 0.8, 0.8);
//	glTranslatef(0, 9.5, -2);
//	weapon();
//
//	glPopMatrix();
//
//	glTranslatef(-7, -8, -2);
//	switch (textureNo) {
//	case 1:
//		textureArr[9] = loadTexture("FireLaser.bmp");
//		glColor3f(1, 0, 0);
//		break;
//	case 2:
//		textureArr[9] = loadTexture("GreenLaser.bmp");
//		glColor3f(1, 1, 1);
//		break;
//	default:
//		break;
//	}
//	//Right - Energy Ball
//	glPushMatrix();
//	glScalef(0.8, 0.8, 0.8);
//	glTranslatef(15, 10, 13);
//	shootingAnimation();
//	glPopMatrix();
//
//	//Left - Energy Ball
//	glPushMatrix();
//	glScalef(0.8, 0.8, 0.8);
//	glTranslatef(-15, 10, 13);
//	shootingAnimation();
//	glPopMatrix();
//
//	glDeleteTextures(1, &textureArr[9]);
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//
//	weaponAnimation();
//	walkingAnimation();
//
//
//	skyBox();
//
//
//
//	//Step5: Remove texture info
//	glDisable(GL_TEXTURE_2D);
//
//	projection();
//}
////--------------------------------------------------------------------
//
////--------------------------------------------------------------------
//
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
//{
//	WNDCLASSEX wc;
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.hInstance = GetModuleHandle(NULL);
//	wc.lpfnWndProc = WindowProcedure;
//	wc.lpszClassName = WINDOW_TITLE;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//
//	if (!RegisterClassEx(&wc)) return false;
//
//	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
//		580, 10, 800, 800,
//		NULL, NULL, wc.hInstance, NULL);
//
//	//--------------------------------
//	//	Initialize window for OpenGL
//	//--------------------------------
//
//	HDC hdc = GetDC(hWnd);
//
//	//	initialize pixel format for the window
//	initPixelFormat(hdc);
//
//	//	get an openGL context
//	HGLRC hglrc = wglCreateContext(hdc);
//
//	//	make context current
//	if (!wglMakeCurrent(hdc, hglrc)) return false;
//
//	//--------------------------------
//	//	End initialization
//	//--------------------------------
//
//	ShowWindow(hWnd, nCmdShow);
//
//	MSG msg;
//	ZeroMemory(&msg, sizeof(msg));
//
//
//
//	while (true)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT) break;
//
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//
//		display();
//
//		SwapBuffers(hdc);
//	}
//
//
//	UnregisterClass(WINDOW_TITLE, wc.hInstance);
//
//	return true;
//}
////--------------------------------------------------------------------