#include "particleForceGenerator.h"
#include "particle.h"

namespace engine { namespace physics {
	DragGenerator::DragGenerator(float k1, float k2)
		: k1(k1), k2(k2) {
	}

	void DragGenerator::updateForce(Particle* particle, float deltaTime) {
		math::vec3 normalVelocity = math::normalize(particle->velocity);
		float speed = math::magnitude(normalVelocity);

		math::vec3 force = -normalVelocity * (k1 * speed + k2 * speed * speed);

		particle->addForce(force);
	}
} }