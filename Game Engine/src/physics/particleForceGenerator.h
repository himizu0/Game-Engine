#pragma once

namespace engine { namespace physics {
	class Particle;

	class ParticleForceGenerator {
		public:
		virtual void updateForce(Particle* particle, float deltaTime) = 0;
	};

	class DragGenerator : public ParticleForceGenerator {
		private:
		float k1;
		float k2;


		public:
		DragGenerator(float k1, float k2);
		void updateForce(Particle* particle, float deltaTime) override;
	};
} }