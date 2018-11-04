#include "particle.h"
#include "physicsUtility.h"

namespace engine { namespace physics {
	Particle::Particle(math::vec3 position, math::vec3 velocity, math::vec3 acceleration) 
		: position(position), velocity(velocity), acceleration(acceleration), forceAccum({0,0,0}), inverseMass(1.0f) {
	}

	Particle::Particle(math::vec3 position, math::vec3 velocity, math::vec3 acceleration, float inverseMass)
		: position(position), velocity(velocity), acceleration(acceleration), forceAccum({ 0,0,0 }), inverseMass(inverseMass) {
	}

	Particle::Particle(float inverseMass)
		: position({ 0,0,0 }), velocity({ 0,0,0 }), acceleration({ 0,-g,0 }), forceAccum({ 0,0,0 }), inverseMass(inverseMass) {
	}

	Particle::Particle()
		: position({ 0,0,0 }), velocity({ 0,0,0 }), acceleration({ 0,-g,0 }), forceAccum({ 0,0,0 }), inverseMass(1.0f) {
	}

	void Particle::integrate(float deltaTime) {
		position += velocity * deltaTime + .5f * acceleration * deltaTime * deltaTime;

		math::vec3 effectiveAcceleration = acceleration;
		effectiveAcceleration += forceAccum * inverseMass;
		velocity += effectiveAcceleration * deltaTime;

		clearAccumulator();
	}

	void Particle::addForce(const math::vec3& force) {
		forceAccum += force;
	}

	void Particle::clearAccumulator() {
		forceAccum = { 0,0,0 };
	}
} }