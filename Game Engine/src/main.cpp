#include <iostream>
#include <Gl/glew.h>

#include "window.h"
#include "camera.h"
#include "math/math.h"
#include "physics/physics.h"
#include "graphics/shader.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/buffers/uniformBuffer.h"
#include "graphics/buffers/frameBuffer.h"
#include "graphics/textures/depthmap.h"
#include "graphics/renderers2D/batchRenderer2D.h"
#include "graphics/renderers3D/batchRenderer3D.h"
#include "graphics/sprite.h"
#include "graphics/textures/texture.h"
#include "graphics/textures/cubemap.h"
#include "graphics/model.h"
#include "graphics/skybox.h"
#include "utils.h"

#include "logging.h"

using namespace engine;
using namespace math;
using namespace physics;
using namespace graphics;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200
#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

float lastTime = 0.0f;
float deltaTime = 0.0f;

Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Window");
Camera camera;

void move();

int main() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("[GLEW Error] Failed to initialize GLEW");
		return -1;
	}
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LEQUAL));
		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));
		GLCall(glEnable(GL_MULTISAMPLE));
		GLCall(glEnable(GL_FRAMEBUFFER_SRGB));

		Logging::print((const char*)glGetString(GL_VERSION));

		const float vertices[] = {
			-1.0f, -1.0f,
			-1.0f, 1.0f,
			-.8f, 1.0f,
			-.8f, -1.0f
		};

		const float vertices2[] = {
			-1.0f, -1.0f,
			-1.0f, -.8f,
			1.0f, -.8f,
			1.0f, -1.0f
		};

		const unsigned int indices[] = {
			0, 3, 2,
			0, 2, 1
		};

		Shader shader("res/shaders/blinn.shader");
		Shader shaderNormal("res/shaders/normalDisplay.shader");
		Shader shaderBasic("res/shaders/basic.shader");
		Shader shaderSkybox("res/shaders/skybox.shader");
		Shader shaderDepthmap("res/shaders/depthmap.shader");

		Texture checker("res/textures/checkerboard.png", true);
		Texture celica("res/textures/Celica.png", true);
		Texture white("res/textures/white.jpg", true);
		Texture pureWhite("res/textures/pureWhite.png", true);


		Model torus("res/models/sample2.obj", white, white, mat4::rotate(45, {1, 0, 0}) * mat4::scale(20));
		Model torus2("res/models/sample2.obj", white, white, mat4::translate({-100, 0, 0}) * mat4::scale(20));
		Model torus3("res/models/cylinder.obj", white, white, mat4::translate({-100, 0, 50}) * mat4::scale(20));
		Model quad("res/models/quad.obj", white, white, mat4::translate({0, -150, 0}) * mat4::scale(20));
		Model cylinder("res/models/cylinder.obj", white, white, mat4::identity());
		Model cylinder2("res/models/cylinder.obj", white, white, mat4::identity());
		Model head("res/models/head.obj", pureWhite, pureWhite, mat4::translate({100, 0, 0}) * mat4::scale(10));

		VertexArray vao1, vao2;

		vao1.bind();
		VertexBuffer vbo1(vertices, sizeof(vertices));
		vbo1.pushLayout<float>(2);
		vbo1.enableLayouts();
		IndexBuffer ibo1(indices, sizeof(indices));
		vao1.unbind();
		
		vao2.bind();
		VertexBuffer vbo2(vertices2, sizeof(vertices2));
		vbo2.pushLayout<float>(2);
		vbo2.enableLayouts();
		IndexBuffer ibo2(indices, sizeof(indices));
		vao2.unbind();

		std::vector<const char*> skyboxPaths;
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_rt.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_lf.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_up.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_dn.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_bk.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_ft.tga");
		Skybox skybox(skyboxPaths, &shaderSkybox);
		BatchRenderer3D renderer;

		Particle* particle = new Particle({ 0,0,0 }, { 20, 0,0 }, {0,0,0}, 1.0f);
		Particle* particle2 = new Particle({ 0,100,50 }, { 20, 0,0 }, {0,0,0}, 1.0f);

		DragGenerator* dragGenerator = new DragGenerator(2.0f, 10.0f);
		SpringGenerator* springGenerator = new SpringGenerator(particle, 1, 0);

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		while (!window.shouldClose()) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			if (window.getKeyDown(GLFW_KEY_ESCAPE))
				window.close();

			float currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			move();
	
			dragGenerator->updateForce(particle2, deltaTime);
			springGenerator->updateForce(particle2, deltaTime);
			particle->integrate(deltaTime);
			particle2->integrate(deltaTime);


			mat4 view = camera.getView();
			mat4 proj = mat4::perspective(45, 4.0f / 3.0f, 0.1f, 10000.0f);
			mat4 vp = proj * view;

			vec3 viewPos = camera.getPosition();
			vec3 lightPos = { -200 * cos((float)glfwGetTime() * .1f), 100, 100 * sin((float)glfwGetTime() * .1f)};

			cylinder.setTransform(mat4::translate(lightPos) * mat4::rotate(45 * glfwGetTime(), {1,1,1}) * mat4::scale(10));
			cylinder2.setTransform(mat4::translate({-lightPos.x, lightPos.y, -lightPos.z}) * mat4::rotate(45 * glfwGetTime(), { 1,1,1 }) * mat4::scale(10));
			torus.setTransform(mat4::rotate(45 * glfwGetTime(), {1,1,1}) * mat4::scale(20));

			torus2.setTransform(mat4::translate(particle->position) * mat4::scale(20));
			torus3.setTransform(mat4::translate(particle2->position) * mat4::scale(20));

			mat4 lightProj = mat4::orthographic(-100, 100, 100, -100, -100, 1000);
			mat4 lightView = mat4::lookAt(lightPos, { 0,0,0 }, {0,1,0});
			mat4 vpLightSpace = proj * lightView;

			/*shaderBasic.use();
			shaderBasic.setUniform4f("u_color", 1, 0, 0, 1);
			vao1.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			vao2.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);*/

			shader.use();
			shader.setUniformMat4f("u_vp", vp);

			shader.setUniform3f("u_viewPosition", viewPos.x, viewPos.y, viewPos.z);
			shader.setUniform3f("u_lights[0].position", lightPos.x, lightPos.y, lightPos.z);
			shader.setUniform3f("u_lights[0].ambient", .05f, .05f, .05f);
			shader.setUniform3f("u_lights[0].diffuse", 1, 1, 1);
			shader.setUniform3f("u_lights[0].specular", 1, 0, 0);

			shader.setUniform3f("u_lights[1].position", -lightPos.x, lightPos.y, -lightPos.z);
			shader.setUniform3f("u_lights[1].ambient", .05f, .05f, .05f);
			shader.setUniform3f("u_lights[1].diffuse", 1, 1, 1);
			shader.setUniform3f("u_lights[1].specular", 1, 0, 0);

			shader.setUniform3f("u_dirLight.direction", 1, 1, 1);
			shader.setUniform3f("u_dirLight.ambient", .05f, .05f, .05f);
			shader.setUniform3f("u_dirLight.diffuse", 1, .5f, .5f);
			shader.setUniform3f("u_dirLight.specular", 1, 0, 0);

			renderer.begin();
			renderer.submit(&torus);
			renderer.submit(&torus2);
			renderer.submit(&torus3);
			renderer.submit(&quad);
			renderer.submit(&cylinder);
			renderer.submit(&cylinder2);
			renderer.submit(&head);
			renderer.end();
			renderer.flush(&shader);

			//shaderSkybox.use();
			//shaderSkybox.setUniformMat4f("u_skyboxvp", proj * view.wipeTranslation());
			//skybox.draw();

			window.update();
		}
	}

	glfwTerminate();
	return 0;
}

void move() {
	if (window.getKeyDown(GLFW_KEY_W))
		camera.processKeyEvents(Direction::UP, deltaTime);
	if (window.getKeyDown(GLFW_KEY_S))
		camera.processKeyEvents(Direction::DOWN, deltaTime);
	if (window.getKeyDown(GLFW_KEY_A))
		camera.processKeyEvents(Direction::LEFT, deltaTime);
	if (window.getKeyDown(GLFW_KEY_D))
		camera.processKeyEvents(Direction::RIGHT, deltaTime);

	vec2 mouseChange = window.getMousePositionChange();
	camera.processMouseEvents(mouseChange.x, mouseChange.y);
	camera.updateCameraVectors();
}