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
#include "Network/EventQueue.h"
#include "Network/Client.h"
#include "Network/Host.h"

#define SCROLL 40

using namespace std;

GLFWwindow* window = NULL;
State *game_state;
EventQueue *eq;
View *view;
int color_table[256];

ScreenCoord mouseCoord;
bool minimise, fullscreen;

ScreenCoord screen_size;

void keyboard(GLFWwindow *, int key, int scancode, int action, int mods);
void mouse(GLFWwindow *, int button, int action, int mods);
void mousePos(GLFWwindow *, double x, double y);
void reshape(GLFWwindow *, int w, int h);

void error_callback(int error, const char* description) {
	cerr << description << endl;
}

void setupWindow(bool fs) {
	minimise = false;
	fullscreen = fs;
	if (window) glfwDestroyWindow(window);

	// fullscreen
	int w, h;
	if (fs) {
		const GLFWvidmode *desktop = glfwGetVideoMode(glfwGetPrimaryMonitor());
		w = desktop->width;
		h = desktop->height;
		window = glfwCreateWindow(w, h, "Test", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		w = 1300;
		h = 700;
		window = glfwCreateWindow(w, h, "Test", NULL, NULL);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);
	glfwSetCursorPosCallback(window, mousePos);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetWindowSizeCallback(window, reshape);
	reshape(window, w, h);

	glEnable( GL_TEXTURE_RECTANGLE_NV );

	glEnable( GL_DEPTH_TEST );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.1 );

}

void keyboard(GLFWwindow *, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_Q:
		view->debug();
		break;
	case GLFW_KEY_Y:
		view->scroll(0, -SCROLL);
		break;
	case GLFW_KEY_H:
		view->scroll(0, SCROLL);
		break;
	case GLFW_KEY_G:
		view->scroll(SCROLL, 0);
		break;
	case GLFW_KEY_J:
		view->scroll(-SCROLL, 0);
		break;
	case '.':
		minimise = true;
		break;
	case GLFW_KEY_ESCAPE:
		glfwDestroyWindow(window);
		break;
	}
}

void mouse(GLFWwindow *, int button, int action, int mods) {
	// action on button up
	if (action == GLFW_RELEASE) view->click(mouseCoord, button);
}

void mousePos(GLFWwindow *, double x, double y) {
	mouseCoord.x = x;
	mouseCoord.y = screen_size.y - y;
}

void reshape(GLFWwindow *, int w, int h) {
	screen_size.x = w;
	screen_size.y = h;
	glViewport(0, 0, w, h);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, w, 0, h, -1, 10000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

int main(int argc, char *argv[]) {
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	setupWindow(false);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}

	srand( time(NULL) );
	//Data *data = new Data();

	if (argc == 1) {
		Host *h = new Host();
	}

	game_state = new State();
	eq = new EventQueue(game_state);

	if (argc == 1) {
		game_state->setClient(new Client(eq));
	}
	else {
		game_state->setClient(new Client(eq, argv[1]));
	}

	/* silly place to read colours before creating view */
	ifstream file;
	file.open("resource/colour.dat", ios::in | ios::binary);
	file.read((char *)&color_table, 1024);
	file.close();
	for (int i = 0; i < 256; ++i) {
		color_table[i] = (color_table[i] >> 8) | 0xff000000;
	}

	view = new View(game_state);
	view->size_ref(&screen_size);

	/*
	 * hopefully get the initialisation
	 */
	eq->startupWait();
	view->loadGraphics();

	cout << "loaded " << endl;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// toggle between window and fullscreen
		if (minimise) {
			setupWindow(!fullscreen); 
			view->loadGraphics();
			minimise = false;
		}

		eq->applyAll();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view->draw();

		/* Swap front and back buffers */
		glFlush();
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//glfwWaitEvents();

	}
	cout << "window closed" << endl;
	glfwTerminate();
	return 0;
}



