#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

class Window {
private:
	const char* _title;
	int _width, _height;
	float _lastFrame = 0.0f;
	bool init();
	bool _closed;
	bool _mouseMoved;
	bool _keys[MAX_KEYS];
	bool _buttons[MAX_BUTTONS];
	glm::vec2 _mousePos;
	friend static void windowResize(GLFWwindow* window, int width, int height);
	friend static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
public:
	Window(const char* title, int width, int height);
	~Window();
	GLFWwindow* _window;
	bool closed();
	void close();
	void clear();
	void update();
	int getWidth() const;
	int getHeight() const;
	glm::vec2 getMousePosition() const;
	bool isKeyPressed(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;
	bool hasMouseMoved() const;
	float delta = 0.0f;
};
