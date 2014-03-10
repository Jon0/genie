/*
 * main.cpp
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "def.h"
#include "Model/State.h"
#include "Data/Data.h"
#include "Graphics/View.h"
#include "Model/Tile.h"


#define SCROLL 40

using namespace std;

GLuint g_mainWnd;
State *game_state;
View *view;
int color_table[256];

int mode;

ScreenCoord screen_size;

void error_callback(int error, const char* description) {
	cerr << description << endl;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		view->debug();
		break;
	case 'p':
		mode = 1;
		break;
	case 'y':
		view->scroll(0, -SCROLL);
		break;
	case 'h':
		view->scroll(0, SCROLL);
		break;
	case 'g':
		view->scroll(SCROLL, 0);
		break;
	case 'j':
		view->scroll(-SCROLL, 0);
		break;
	case '.':
		//glutFullScreen();
		break;
	case ',':
		//glutReshapeWindow(800, 600);
		//glutPositionWindow(0,0);
		break;
	}
}

void mouse(int button, int state, int x, int y) {
	ScreenCoord sc;
	sc.x = x;
	sc.y = screen_size.y - y;

	// action on button up
	if (state == 1) view->click(sc, button);
}

void reshape(int w, int h) {
	screen_size.x = w;
	screen_size.y = h;
	glViewport(0, 0, w, h);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, w, 0, h, -1, 10000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void drawCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game_state->update();
	//if (mode == 0) 
	view->draw();
	//else view->test();
	//glutSwapBuffers();
}

void idle() {
	//glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(1300, 700, "Test", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}

	srand( time(NULL) );
	//Data *data = new Data();

	/* silly place to read colours */
	ifstream file;
	file.open("resource/colour.dat", ios::in | ios::binary);
	file.read((char *)&color_table, 1024);
	file.close();
	for (int i = 0; i < 256; ++i) {
		color_table[i] = (color_table[i] >> 8) | 0xff000000;
	}

	game_state = new State();
	view = new View(game_state);
	view->size_ref(&screen_size);
	mode = 0;

	glEnable( GL_TEXTURE_RECTANGLE_NV );

	glEnable( GL_DEPTH_TEST );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.1 );

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	reshape(1300, 700);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		drawCallback();

		/* Swap front and back buffers */
		glFlush();
		glfwSwapBuffers(window);

		/* Poll for and process events */
		//glfwPollEvents();
		glfwWaitEvents();
	}

	glfwTerminate();

	return 0;
}



