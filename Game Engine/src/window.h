#pragma once

#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace engine { namespace math {
	struct vec2;
} }

namespace engine {
	class Window {
		private:
		GLFWwindow* m_window;

		static bool m_keys[MAX_KEYS];
		static bool m_buttons[MAX_BUTTONS];
		static double m_mouseX, m_mouseY;
		static double m_mouseDeltaX, m_mouseDeltaY;

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

		
		public:
		Window(int width, int height, const char* title);
		~Window();

		void close() const;
		void update() const;

		inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
		inline bool getKeyDown(int key) const { return m_keys[key]; }
		inline bool getButtonDown(int button) const { return m_buttons[button]; }
		const math::vec2& getMousePos() const;
		const math::vec2& getMousePositionChange() const;
	};
}