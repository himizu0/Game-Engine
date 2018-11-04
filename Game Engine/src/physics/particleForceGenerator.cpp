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

	SpringGenerator::SpringGenerator(Particle* other, float springConstant, float restLength)
		: other(other), springConstant(springConstant), restLength(restLength) {
	}

	void SpringGenerator::updateForce(Particle* particle, float deltaTime) {
		math::vec3 differenceVector = particle->position - other->position;

		math::vec3 force = -springConstant * (magnitude(differenceVector) - restLength) * normalize(differenceVector);

		particle->addForce(force);
	}
} }