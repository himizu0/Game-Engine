#include "math/math.h"


namespace engine { namespace physics {
	class Particle {
		private:
		math::vec3 forceAccum;

		public:
		math::vec3 position;
		math::vec3 velocity;
		math::vec3 acceleration;

		float damping;
		float inverseMass;


		Particle(math::vec3 position, math::vec3 velocity, math::vec3 acceleration);
		Particle(math::vec3 position, math::vec3 velocity, math::vec3 acceleration, float inverseMass);
		Particle(float inverseMass);
		Particle();

		void integrate(float deltaTime);
		void addForce(const math::vec3& force);
		void clearAccumulator();
	};
} }