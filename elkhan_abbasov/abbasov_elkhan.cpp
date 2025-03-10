/**********************************
 CTIS164 - Template Source Program
-----------------------------------
NAME SURNAME :
STUDENT ID :
SECTION :
HOMEWORK :
-----------------------------------
PROBLEMS :
-----------------------------------
ADDITIONAL FEATURES :
**********************************/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         0 // 0:Disable timer, 1:Enable timer
#define D2R 0.017453292
#define PI 3.141592654

// Global Variables for Template File
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // Current Window width and height

// To draw a filled circle, centered at (x,y) with radius r
void circle(int x, int y, int r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 3)
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	glEnd();
}

// To draw an empty circle, centered at (x,y) with radius r
void circle_wire(int x, int y, int r) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 3)
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	glEnd();
}

void drawText(const char* text, float x, float y, void* font) {
	glRasterPos2f(x, y);
	int len = strlen(text);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, text[i]);
	}
}

void print(int x, int y, const char* string, void* font) {
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]);
}

// Display text with variables
void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}

void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}

void drawWallpaper() {
	// Set background color
	glClearColor(166.0 / 255, 156.0 / 255, 145.0 / 255, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Set line color 
	glColor3f(71.0 / 255, 54.0 / 255, 54.0 / 255);
	glLineWidth(2);

	glBegin(GL_LINES);
	// Draw horizontal lines that scale with window height (resize immune)
	for (int y = -winHeight / 2; y <= winHeight / 2; y += 50) {
		glVertex2f(-winWidth / 2, y);
		glVertex2f(winWidth / 2, y);
	}
	glEnd();
}

void drawFlowerWithStem(float x, float stemBottom, float r, float red, float green, float blue) {
	//Stem
	glColor3f(0.0, 80.0 / 255, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(x, stemBottom); 
	glVertex2f(x, stemBottom + 20); 
	glEnd();

	// Draw Flower Head
	glColor3f(red, green, blue);
	circle(x, stemBottom + 25, r); 
}

void drawCow() {
	glColor3f(1.0, 1.0, 1.0);  // White body
	glBegin(GL_QUADS);
	glVertex2f(90, -110); 
	glVertex2f(110, -110);
	glVertex2f(110, -93); 
	glVertex2f(90, -93);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);  // Black spots

	glBegin(GL_QUADS); // spot 1
	glVertex2f(95, -105); 
	glVertex2f(98, -105);
	glVertex2f(98, -102); 
	glVertex2f(95, -102);
	glEnd();

	glBegin(GL_QUADS); // spot2
	glVertex2f(102, -100); 
	glVertex2f(105, -100);
	glVertex2f(105, -97); 
	glVertex2f(102, -97);
	glEnd(); 

	glBegin(GL_QUADS); //spot 3
	glVertex2f(99, -105);
	glVertex2f(101, -105);
	glVertex2f(101, -102);
	glVertex2f(99, -102);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);  // Head
	glBegin(GL_QUADS);
	glVertex2f(112, -107); glVertex2f(122, -107);
	glVertex2f(122, -97); glVertex2f(112, -97);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);  // Eyes
	glBegin(GL_QUADS);
	glVertex2f(114, -103); glVertex2f(116, -103);
	glVertex2f(116, -101); glVertex2f(114, -101);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(118, -103); glVertex2f(120, -103);
	glVertex2f(120, -101); glVertex2f(118, -101);
	glEnd();

	glColor3f(1.0, 0.5, 0.5); // Pink nose
	glBegin(GL_QUADS);
	glVertex2f(116, -108); 
	glVertex2f(120, -108);
	glVertex2f(120, -104); 
	glVertex2f(116, -104);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);  // Legs
	glBegin(GL_QUADS);
	glVertex2f(92, -115); glVertex2f(95, -115);
	glVertex2f(95, -110); glVertex2f(92, -110);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(108, -115); glVertex2f(110, -115);
	glVertex2f(110, -110); glVertex2f(108, -110);
	glEnd();
}

// UFO Position
float ufoX = 0;  // UFO center left/right 
float ufoY = 0; // up/down

void drawAlien() {
	// Head
	glColor3f(0.2, 0.8, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 10, ufoY + 2);
	glVertex2f(ufoX + 10, ufoY + 2);
	glVertex2f(ufoX + 10, ufoY + 12);
	glVertex2f(ufoX - 10, ufoY + 12);
	glEnd();

	// Dark Green
	glColor3f(0.1, 0.6, 0.1);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 10, ufoY + 2);
	glVertex2f(ufoX - 7, ufoY + 2);
	glVertex2f(ufoX - 7, ufoY + 12);
	glVertex2f(ufoX - 10, ufoY + 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(ufoX + 7, ufoY + 2);
	glVertex2f(ufoX + 10, ufoY + 2);
	glVertex2f(ufoX + 10, ufoY + 12);
	glVertex2f(ufoX + 7, ufoY + 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(ufoX - 7, ufoY + 11);  
	glVertex2f(ufoX + 7, ufoY + 11);  
	glVertex2f(ufoX + 7, ufoY + 14);  
	glVertex2f(ufoX - 7, ufoY + 14);  
	glEnd();

	// Eyes 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 6, ufoY + 5);
	glVertex2f(ufoX - 3, ufoY + 5);
	glVertex2f(ufoX - 3, ufoY + 9);
	glVertex2f(ufoX - 6, ufoY + 9);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(ufoX + 3, ufoY + 5);
	glVertex2f(ufoX + 6, ufoY + 5);
	glVertex2f(ufoX + 6, ufoY + 9);
	glVertex2f(ufoX + 3, ufoY + 9);
	glEnd();

	// White Eye 
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 5, ufoY + 8);
	glVertex2f(ufoX - 4, ufoY + 8);
	glVertex2f(ufoX - 4, ufoY + 7);
	glVertex2f(ufoX - 5, ufoY + 7);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(ufoX + 4, ufoY + 8);
	glVertex2f(ufoX + 5, ufoY + 8);
	glVertex2f(ufoX + 5, ufoY + 7);
	glVertex2f(ufoX + 4, ufoY + 7);
	glEnd();

	// Mouth
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 3, ufoY + 3);
	glVertex2f(ufoX + 3, ufoY + 3);
	glVertex2f(ufoX + 3, ufoY + 4);
	glVertex2f(ufoX - 3, ufoY + 4);
	glEnd();
}

// Draw UFO 
void drawUFO() {
	
	// Top Dome
	glColor3f(0.6, 0.9, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(ufoX - 30, ufoY);
		glVertex2f(ufoX + 30, ufoY);
		glVertex2f(ufoX + 15, ufoY + 15);
		glVertex2f(ufoX - 15, ufoY + 15);
	glEnd();

	drawAlien();

	// Main Body
	glColor3f(0.5, 0.7, 0.9);
	glBegin(GL_QUADS);
		glVertex2f(ufoX - 40, ufoY);
		glVertex2f(ufoX + 40, ufoY);
		glVertex2f(ufoX + 50, ufoY - 10);
		glVertex2f(ufoX - 50, ufoY - 10);
	glEnd();

	// Yellow Lights
	glColor3f(1.0, 1.0, 0.0);
	for (int i = -30; i <= 30; i += 15) {
		glBegin(GL_QUADS);
		glVertex2f(ufoX + i - 3, ufoY - 3);
		glVertex2f(ufoX + i + 3, ufoY - 3);
		glVertex2f(ufoX + i + 3, ufoY - 6);
		glVertex2f(ufoX + i - 3, ufoY - 6);
		glEnd();
	}

	// Bottom Gray
	glColor3f(0.2, 0.3, 0.4);
	glBegin(GL_QUADS);
	glVertex2f(ufoX - 30, ufoY - 10);
	glVertex2f(ufoX + 30, ufoY - 10);
	glVertex2f(ufoX + 20, ufoY - 15);
	glVertex2f(ufoX - 20, ufoY - 15);
	glEnd();

	
}


void drawStars() {
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2); 

	glBegin(GL_POINTS);
	glVertex2f(-250, 30);
	glVertex2f(-200, 5);
	glVertex2f(-150, 37);
	glVertex2f(-100, 18);
	glVertex2f(-50, 15);
	glVertex2f(0, 31);
	glVertex2f(50, 18);
	glVertex2f(100, 24);
	glVertex2f(150, 29);
	glVertex2f(200, 5);
	glVertex2f(250, 22);
	glVertex2f(-225, -9);
	glVertex2f(225, 9);
	glVertex2f(175, 23);
	glVertex2f(-230, -35);
	glVertex2f(-180, -25);
	glVertex2f(-130, -40);
	glVertex2f(-80, -30);
	glVertex2f(-30, -45);
	glVertex2f(20, -35);
	glVertex2f(70, -50);
	glVertex2f(120, -38);
	glVertex2f(170, -42);
	glVertex2f(220, -33);
	glVertex2f(250, -55);
	glVertex2f(-200, -60);
	glVertex2f(-150, -50);
	glVertex2f(-100, -65);
	glVertex2f(-50, -55);
	glVertex2f(0, -70);
	glVertex2f(50, -60);
	glVertex2f(100, -75);
	glVertex2f(150, -65);
	glVertex2f(200, -80);
	glEnd();
}







// To display onto window using OpenGL commands
void display() {
	// Clear window to black
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Wallpaper & lines
	drawWallpaper();

	//Draw Label (with text)

		//Circle
			glColor3f(0, 0, 0);
			circle(0, 250, 10);  // radius 50
		//Strings
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
				glVertex2f(0, 250);
				glVertex2f(-250, 200);
				glVertex2f(0, 250);
				glVertex2f(250, 200);
			glEnd();

			// Frame 1 (Outer)
			glColor3f(91.0 / 255, 52.0 / 255, 13.0 / 255);
			glBegin(GL_QUADS);
				glVertex2f(-250, 200);
				glVertex2f(250, 200);
				glVertex2f(250, 150);
				glVertex2f(-250, 150);
			glEnd();

			// Outline for Frame 1
			glColor3f(0, 0, 0); 
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-250, 200);
				glVertex2f(250, 200);
				glVertex2f(250, 150);
				glVertex2f(-250, 150);
			glEnd();

			// Frame 2 (Inner)
			glColor3f(120.0 / 255, 80.0 / 255, 40.0 / 255);
			glBegin(GL_QUADS);
				glVertex2f(-240, 190);
				glVertex2f(240, 190);
				glVertex2f(240, 160);
				glVertex2f(-240, 160);
			glEnd();

			// Outline for Frame 2
			glColor3f(0, 0, 0); 
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-240, 190);
				glVertex2f(240, 190);
				glVertex2f(240, 160);
				glVertex2f(-240, 160);
			glEnd();

			// Text
			glColor3f(1.0, 1.0, 1.0);
			vprint(-135, 170, GLUT_BITMAP_9_BY_15, "Press Space Button to See Aliens :)");

			// Window 1
			glColor3f(61.0 / 255, 35.0 / 255, 9.0 / 255);
			glBegin(GL_QUADS);
				glVertex2f(-300, -200);
				glVertex2f(300, -200);
				glVertex2f(300, 100);
				glVertex2f(-300, 100);
			glEnd();

			// Outline for Window 1
			glColor3f(0, 0, 0); 
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-300, -200);
				glVertex2f(300, -200);
				glVertex2f(300, 100);
				glVertex2f(-300, 100);
			glEnd();

			// Window 2
			glColor3f(120.0 / 255, 80.0 / 255, 40.0 / 255);
			glBegin(GL_QUADS);
				glVertex2f(-275, -175);
				glVertex2f(275, -175);
				glVertex2f(275, 75);
				glVertex2f(-275, 75);
			glEnd();

			// Outline for Window 2
			glColor3f(0, 0, 0); 
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-275, -175);
				glVertex2f(275, -175);
				glVertex2f(275, 75);
				glVertex2f(-275, 75);
			glEnd();

			//Outline for Main Objects
			glColor3f(0, 0, 0);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-260, -160);
				glVertex2f(260, -160);
				glVertex2f(260, 60);
				glVertex2f(-260, 60);
			glEnd();

			// Dark Night Theme Gradient Background
			glBegin(GL_QUADS);
				glColor3f(20.0 / 255, 20.0 / 255, 90.0 / 255);  // Top
				glVertex2f(-260, 60);
				glVertex2f(260, 60);

				glColor3f(19.0 / 255, 19.0 / 255, 26.0 / 255);  // Bottom
				glVertex2f(260, -160);
				glVertex2f(-260, -160);
			glEnd();

			//Outline for  dark night
			glColor3f(0, 0, 0); 
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-260, 60);   
				glVertex2f(260, 60);    
				glVertex2f(260, -160);  
				glVertex2f(-260, -160); 
			glEnd();

			// Grass
			glColor3f(0, 111.0 / 255, 0);
			glBegin(GL_QUADS);
				glVertex2f(-259, -160); 
				glVertex2f(259, -160);  
				glVertex2f(259, -105);  
				glVertex2f(-259, -105); 
			glEnd();

			//Grass outline
			glColor3f(0, 0, 0); 
			glLineWidth(2);
			glBegin(GL_LINES);
			// Bottom 
			glVertex2f(-259, -160);
			glVertex2f(259, -160);
			// Top 
			glVertex2f(-259, -105);
			glVertex2f(259, -105);
			glEnd();

			// Add flowers 
			drawFlowerWithStem(-230, -135, 5, 1.0, 0.5, 0.8);  
			drawFlowerWithStem(-180, -150, 5, 1.0, 1.0, 0.0);  
			drawFlowerWithStem(-120, -140, 5, 0.6, 0.2, 0.8);  
			drawFlowerWithStem(-60, -155, 5, 1.0, 0.5, 0.8);   
			drawFlowerWithStem(0, -145, 5, 1.0, 1.0, 0.0);     
			drawFlowerWithStem(60, -132, 5, 0.6, 0.2, 0.8);    
			drawFlowerWithStem(120, -155, 5, 1.0, 0.5, 0.8);   
			drawFlowerWithStem(180, -140, 5, 1.0, 1.0, 0.0);   
			drawFlowerWithStem(230, -145, 5, 0.6, 0.2, 0.8);   

			// Cow 
			drawCow();

			// UFO & Alien
			drawUFO();

			//Stars
			drawStars();




			glutSwapBuffers();

}

// Key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y) {
	// Exit when ESC is pressed
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
	// Exit when ESC is pressed
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	case GLUT_KEY_LEFT:
		left = true;
		break;
	case GLUT_KEY_RIGHT:
		right = true;
		break;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case GLUT_KEY_LEFT:
		left = false;
		break;
	case GLUT_KEY_RIGHT:
		right = false;
		break;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// When a click occurs in the window, It provides which button
// Buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// States  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // Refresh window.
}

void onMoveDown(int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}
#endif

void Init() {
	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2 - 50
	);
	glutCreateWindow("Abbasov Elkhan");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// Keyboard Events
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	// Mouse Events
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// Timer Event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();
	glutMainLoop();
	return 0;
}