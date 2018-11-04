#include "particleForceRegistry.h"
#include "particle.h"
#include "particleForceGenerator.h"

namespace engine { namespace physics {
	void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* pfg) {
		registry.push_back({ particle, pfg });
	}

	void ParticleForceRegistry::clear() {
		registry.clear();
	}

	void ParticleForceRegistry::updateForces(float deltaTime) {
		for (auto i = registry.begin(); i != registry.end(); i++)
			i->pfg->updateForce(i->particle, deltaTime);
	}
} }