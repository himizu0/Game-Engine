#pragma once

#include "math/math.h"

namespace engine {
	enum class Direction {
		UP, DOWN, LEFT, RIGHT
	};

	class Camera {
		private:
		math::vec3 m_position;
		math::vec3 m_front;
		math::vec3 m_up;
		float m_speed;
		float m_sensitivity;
		float m_yaw;
		float m_pitch;

		public:
		Camera();

		void updateCameraVectors();
		void processMouseEvents(float deltaX, float deltaY);
		void processKeyEvents(Direction direction, float deltaTime);

		inline const math::vec3& getPosition() const { return m_position; }
		inline const math::mat4& getView() const { return math::mat4::lookAt(m_position, m_position + m_front, m_up); }
	};
}