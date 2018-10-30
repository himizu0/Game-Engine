#include <iostream>
#include <Gl/glew.h>

#include "window.h"
#include "camera.h"
#include "math/math.h"
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
using namespace graphics;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
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
		Shader shaderBasic("res/shaders/basic.shader");
		Shader shaderSkybox("res/shaders/skybox.shader");
		Shader shaderDepthmap("res/shaders/depthmap.shader");

		Texture checker("res/textures/checkerboard.png", true);


		Model torus("res/models/sample2.obj", checker, checker, mat4::rotate(45, {1, 0, 0}) * mat4::scale(20));
		Model quad("res/models/quad.obj", checker, checker, mat4::translate({0, -50, 0}) * mat4::scale(20));

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

		UniformBuffer ubo(sizeof(mat4), 0);
		
		//Depthmap depthmap(SHADOW_WIDTH, SHADOW_HEIGHT);
		//FrameBuffer fboDepthmap;
		//fboDepthmap.attachDepthmap(depthmap.getID());

		std::vector<const char*> skyboxPaths;
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_rt.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_lf.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_up.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_dn.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_bk.tga");
		skyboxPaths.push_back("res/textures/skyboxCloud/miramar_ft.tga");
		Skybox skybox(skyboxPaths, &shaderSkybox);
		BatchRenderer3D renderer;
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		while (!window.shouldClose()) {
			if (window.getKeyDown(GLFW_KEY_ESCAPE))
				window.close();

			float currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			move();

			//GLCall(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
			//fboDepthmap.bind();
			//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			//mat4 projLightSpace = mat4::perspective(45, 4.0f / 3.0f, 0.1f, 10000.0f);
			//mat4 viewLightSpace = camera.getView();
			//mat4 vpLightSpace = projLightSpace * viewLightSpace;
			

			/*renderer.begin();
			renderer.submit(&torus);
			renderer.submit(&quad);
			renderer.end();
			renderer.flush(&shaderDepthmap);*/

			//fboDepthmap.unbind();


			GLCall(glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			mat4 view = camera.getView();
			mat4 proj = mat4::perspective(45, 4.0f / 3.0f, 0.1f, 10000.0f);
			mat4 vp = proj * view;

			vec3 viewPos = camera.getPosition();
			vec3 lightPos = { -100, 20, 100 };

			ubo.bind();
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), &vp);
			mat4 lightProj = mat4::orthographic(-100, 100, 1000, -100, -100, 1000);
			mat4 lightView = camera.getView();
			mat4 vpLightSpace = lightProj * lightView;
			//glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), &vpLightSpace);

			shaderBasic.use();
			shaderBasic.setUniform4f("u_color", 1, 0, 0, 1);
			vao1.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			vao2.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			shader.use();
			shader.setUniform3f("u_viewPosition", viewPos.x, viewPos.y, viewPos.z);
			shader.setUniform3f("u_light.position", lightPos.x, lightPos.y, lightPos.z);
			shader.setUniform3f("u_light.ambient", .1f, .1f, .1f);
			shader.setUniform3f("u_light.diffuse", 1, 1, 1);
			shader.setUniform3f("u_light.specular", 1, 1, 1);

			//depthmap.bind(0);
			//shader.setUniform1i("u_depthmap", 0);

			renderer.begin();
			renderer.submit(&torus);
			renderer.submit(&quad);
			renderer.end();
			renderer.flush(&shader);

			shaderSkybox.use();
			shaderSkybox.setUniformMat4f("u_skyboxvp", proj * view.wipeTranslation());
			skybox.draw();

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