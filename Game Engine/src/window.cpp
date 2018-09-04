#include <iostream>
#include "window.h"
#include "math/math.h"

namespace engine {
	bool Window::m_keys[MAX_KEYS];
	bool Window::m_buttons[MAX_BUTTONS];
	double Window::m_mouseX, Window::m_mouseY;
	double Window::m_mouseDeltaX, Window::m_mouseDeltaY;

	Window::Window(int width, int height, const char* title) {

		if (!glfwInit()) {
			printf("[GLFW Error] Failed to initialize GLFW\n");
			return;
		}

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (m_window == nullptr) {
			printf("[GLFW Error] Failed to create GLFW window\n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_window, cursorPosCallback);

		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSwapInterval(0);
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		m_keys[key] = action != GLFW_RELEASE;
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		m_buttons[button] = action != GLFW_RELEASE;
	}

	void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
		m_mouseDeltaX = xpos - m_mouseX;
		m_mouseDeltaY = ypos - m_mouseY;

		m_mouseX = xpos;
		m_mouseY = ypos;
	}

	void Window::close() const {
		glfwSetWindowShouldClose(m_window, true);
	}

	void Window::update() const {
		m_mouseDeltaX = 0;
		m_mouseDeltaY = 0;

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	const math::vec2& Window::getMousePos() const {
		return { (float) m_mouseX, (float) m_mouseY };
	}

	const math::vec2& Window::getMousePositionChange() const {
		return { (float)m_mouseDeltaX, (float) m_mouseDeltaY };
	}
}