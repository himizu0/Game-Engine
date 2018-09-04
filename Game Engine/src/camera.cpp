#include <iostream>
#include "camera.h"

namespace engine {
	Camera::Camera()
		:m_position({ 0, 0, 100 }), m_front({ 0, 0, -1 }), m_up({ 0, 1, 0 }),
		m_speed(100), m_sensitivity(0.1f), m_yaw(0), m_pitch(0) {}

	void Camera::updateCameraVectors() {
		math::vec3 front(0,0,0);

		const float rp = math::toRadians(m_pitch);
		const float ry = math::toRadians(m_yaw);

		front.x = cos(rp) * cos(ry);
		front.y = sin(rp);
		front.z = cos(rp) * sin(ry);

		m_front = normalize(front);
	}

	void Camera::processMouseEvents(float deltaX, float deltaY) {
		m_yaw += m_sensitivity * deltaX;
		m_pitch += m_sensitivity * deltaY;

		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}

	void Camera::processKeyEvents(Direction direction, float deltaTime) {
		if (direction == Direction::UP)
			m_position += deltaTime * m_speed * normalize(math::vec3(m_front.x, 0.0f, m_front.z));
		if (direction == Direction::DOWN)
			m_position -= deltaTime * m_speed * normalize(math::vec3(m_front.x, 0.0f, m_front.z));
		if (direction == Direction::LEFT)
			m_position += deltaTime * m_speed * normalize(math::cross(m_up, m_front));
		if (direction == Direction::RIGHT)
			m_position -= deltaTime * m_speed * normalize(cross(m_up, m_front));
	}
}