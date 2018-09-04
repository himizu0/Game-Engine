#include <iostream>
#include <Gl/glew.h>

#include "window.h"
#include "camera.h"
#include "math/math.h"
#include "graphics/shader.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/renderers2D/batchRenderer2D.h"
#include "graphics/renderers3D/batchRenderer3D.h"
#include "graphics/sprite.h"
#include "graphics/texture.h"
#include "graphics/model.h"

using namespace engine;
using namespace math;
using namespace graphics;

#define print(x) std::cout << x << '\n';

float lastTime = 0.0f;
float deltaTime = 0.0f;

Window window(900, 600, "Hello Window");
Camera camera;

void move();

int main() {

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("[GLEW Error] Failed to initialize GLEW");
		return -1;
	}

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	printf("%s\n", glGetString(GL_VERSION));

	Shader shader3D("res/shaders/phong.shader");
	Shader shader2D("res/shaders/batch2D.shader");

	Texture texture1("res/textures/Summer Celica.png");
	Texture texture2("res/textures/Awesome Face.png");
	Texture texture3("res/textures/Celica.png");
	Texture textureChecker("res/textures/checkerboard.png");

	BatchRenderer3D renderer3D(&shader3D);
	Model* cylinder = new Model("res/models/cylinder.obj", texture1, texture1, math::mat4::rotate(0, { 1, 1, 1 }) * math::mat4::scale({ 20, 20, 20 }));
	Model* lightSource = new Model("res/models/cylinder.obj", texture2, texture2);
	Model* torus = new Model("res/models/sample2.obj", textureChecker, textureChecker, math::mat4::translate({-150, -30, 30}) * math::mat4::scale({ 20, 20, 20 }));
	//Model* pneuma = new Model("res/models/pneuma.obj", textureChecker, textureChecker);
	//Model* pneuma2 = new Model("res/models/pneuma.obj", texture1, texture1, mat4::rotate(45, { 1,1,1 }));

	const mat4& proj = mat4::perspective(45.0f, 1.5f, 0.1f, 10000.0f);

	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	while (!window.shouldClose()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (window.getKeyDown(GLFW_KEY_ESCAPE))
			window.close();

		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		move();

		shader3D.use();
		shader3D.setUniform3f("u_viewPosition", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

		vec3 lightPos = vec3(-100 + 50 * cos(glfwGetTime()), 20 + 50 * sin(glfwGetTime()), 100);
		lightSource->setTransform(math::mat4::translate(lightPos) * math::mat4::scale({ 20, 20, 20 }));
		shader3D.setUniform3f("u_light.position", lightPos.x, lightPos.y, lightPos.z);
		shader3D.setUniform3f("u_light.ambient", 0.1f, 0.1f, 0.1f);
		shader3D.setUniform3f("u_light.diffuse", 1, 1, 1);
		shader3D.setUniform3f("u_light.specular", 1, 1, 1);

		mat4 view = camera.getView();
		mat4 vp = proj * view;
		shader3D.setUniformMat4f("u_vp", vp);


		renderer3D.begin();
		renderer3D.submit(cylinder);
		renderer3D.submit(torus);
		//renderer3D.submit(pneuma);
		//renderer3D.submit(pneuma2);
		renderer3D.submit(lightSource);
		renderer3D.end();
		renderer3D.flush();
		printf("\n");

		window.update();
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