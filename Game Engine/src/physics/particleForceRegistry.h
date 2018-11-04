#pragma once
#include <vector>

namespace engine { namespace physics {
	class ParticleForceGenerator;
	class Particle;

	class ParticleForceRegistry {
		protected:
		struct Registration {
			Particle* particle;
			ParticleForceGenerator* pfg;

			friend bool operator==(const Registration& left, const Registration& right) {
				return left.particle == right.particle && left.pfg == right.pfg;
			}
		};

		std::vector<Registration> registry;


		public:
		void add(Particle* particle, ParticleForceGenerator* pfg);
		void clear();
		void updateForces(float deltaTime);
	};
} }