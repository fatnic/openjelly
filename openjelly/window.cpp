#include "window.h"

Window::Window(const char * title, int width, int height)
{
	_title = title;
	_width = width;
	_height = height;

	if (!init())
		glfwTerminate();

}

Window::~Window()
{
}

bool Window::closed()
{
	return glfwWindowShouldClose(_window);
}

void Window::close()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

bool Window::init()
{
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
	aspectRatio = (float)_width / (float)_height;

	if (!_window) {
		glfwTerminate();
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;

	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, this);

	glfwSetKeyCallback(_window, keyCallback);
	glfwSetMouseButtonCallback(_window, mouseButtonCallback);
	glfwSetCursorPosCallback(_window, cursorPositionCallback);
	glfwSetWindowSizeCallback(_window, windowResize);

	glfwSetCursorPos(_window, _width/2, _height/2);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	for (int i = 0; i < MAX_KEYS; i++)
		_keys[i] = false;

	for (int i = 0; i < MAX_BUTTONS; i++)
		_buttons[i] = false;

	std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, _width, _height);

	return true;
}

void Window::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	_mouseMoved = false;

	float currentFrame = glfwGetTime();
	delta = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	glfwPollEvents();
	glfwSwapBuffers(_window);
}

float Window::getWidth() const
{
	return (float)_width;
}

float Window::getHeight() const
{
	return (float)_height;
}

bool Window::isKeyPressed(unsigned int keycode) const
{
	if (keycode >= MAX_KEYS)
		return false;

	return _keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const
{
	if (button >= MAX_BUTTONS)
		return false;

	return _buttons[button];
}

void windowResize(GLFWwindow* window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_width = width;
	win->_height = height;
	win->aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

glm::vec2 Window::getMousePosition() const
{
	return _mousePos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	Window* win = (Window*) glfwGetWindowUserPointer(window);
	win->_keys[key] = action != GLFW_RELEASE;
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_buttons[button] = action != GLFW_RELEASE;
}
void cursorPositionCallback(GLFWwindow * window, double xpos, double ypos)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_mousePos.x = xpos;
	win->_mousePos.y = ypos;
	win->_mouseMoved = true;
}

bool Window::hasMouseMoved() const
{
	return _mouseMoved;
}


