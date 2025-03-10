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
	// Draw Stem (Dark Green)
	glColor3f(0.0, 80.0 / 255, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(x, stemBottom);   // Bottom of stem (controlled externally)
	glVertex2f(x, stemBottom + 20); // Fixed length stem
	glEnd();

	// Draw Flower Head
	glColor3f(red, green, blue);
	circle(x, stemBottom + 25, r); // Flower sits 5px above the stem
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

			// Add flowers with manually set heights
			drawFlowerWithStem(-230, -135, 5, 1.0, 0.5, 0.8);  // Pink (Higher)
			drawFlowerWithStem(-180, -150, 5, 1.0, 1.0, 0.0);  // Yellow (Lower)
			drawFlowerWithStem(-120, -140, 5, 0.6, 0.2, 0.8);  // Purple (Middle)
			drawFlowerWithStem(-60, -155, 5, 1.0, 0.5, 0.8);   // Pink (Lowest)
			drawFlowerWithStem(0, -145, 5, 1.0, 1.0, 0.0);     // Yellow (Middle)
			drawFlowerWithStem(60, -132, 5, 0.6, 0.2, 0.8);    // Purple (Higher)
			drawFlowerWithStem(120, -155, 5, 1.0, 0.5, 0.8);   // Pink (Lowest)
			drawFlowerWithStem(180, -140, 5, 1.0, 1.0, 0.0);   // Yellow (Middle)
			drawFlowerWithStem(230, -145, 5, 0.6, 0.2, 0.8);   // Purple (Middle)


			

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