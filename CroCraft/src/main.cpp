#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "texture/Texture.h"
#include "display/Display.h"
#include "shader/Shader.h"
#include "mesh/Mesh.h"

const int WINDOW_WIDTH = 1920 / 2, WINDOW_HEIGHT = 1920 / 2;

std::vector<std::unique_ptr<Shader>> shaders;
std::unique_ptr<Mesh> mesh;
std::unique_ptr<Display> display;
std::shared_ptr<Texture> texture_default;

glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

void create_shaders()
{
	shaders.push_back(std::make_unique<Shader>());
	shaders[0]->create_from_file(
		"C:\\dev\\CrocCraft\\CroCraft\\CroCraft\\assets\\shaders\\vertex.glsl",
		"C:\\dev\\CrocCraft\\CroCraft\\CroCraft\\assets\\shaders\\fragment.glsl"
	);
}

void setup()
{	
	display = std::make_unique<Display>(WINDOW_WIDTH, WINDOW_HEIGHT);

	create_shaders();

	texture_default = std::make_shared<Texture>("C:\\dev\\CrocCraft\\CroCraft\\CroCraft\\assets\\textures\\parappa_block.png");
	texture_default->load_textureA();
	
	float vertices[] = {
		1.0f,  1.0f,  1.0f,  0.5f, 0.5f, // top right
		1.0f, -1.0f,  1.0f,  0.5f, 0.0f, // bottom right
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom left
		-1.0f,  1.0f,  1.0f,  0.0f, 0.5f, // top left ,
		1.0f,  1.0f, -1.0f,  0.5f, 0.5f,
		1.0f, -1.0f, -1.0f,  0.5f, 0.0f, 
		-1.0f, -1.0f, -1.0f,  0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.5f, 0.5f,

		// right face
		// 0 vertex for right face
		1.0f,  1.0f,  1.0f,  0.0f, 0.5f,	 
		// 1 vertex for right face
		1.0f, -1.0f,  1.0f,  0.0f, 0.0f,	

		// back face
		// 6 vertex for back face
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
		// 7 vertex for back face
		-1.0f,  1.0f, -1.0f,  0.0f, 0.5f,

		// upper face
		// 0 vertex for upper face
		1.0f,  1.0f,  1.0f,  1.0f, 0.5f,

		// 3 vertex for upper face
		-1.0f,  1.0f,  1.0f,  0.5f, 0.5f,

		// 4 vertex for upper face
		1.0f,  1.0f, -1.0f,  1.0f, 1.0f,

		// 7 vertex for upper face
		-1.0f,  1.0f, -1.0f,  0.5f, 1.0f,

		// down face
		// 1 vertex for down face
		1.0f, -1.0f,  1.0f,  0.5f, 0.5f, 
		// 2 vertex for down face
		-1.0f, -1.0f,  1.0f,  0.0f, 0.5f,
		// 5 vertex for down face
		1.0f, -1.0f, -1.0f,  0.5f, 1.0f,
		// 6 vertex for down face
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f
	};
	


	unsigned int indices[] = {

		// front face
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle,

		//right face
		8, 9, 5,
		8, 4, 5,

		//back face
		4, 5,  11, // fifith tri 
		5, 10, 11,  // sixth tri

		// left face
		3, 6, 2,   // seventh
		3, 6, 7,   // eighth tri
		
		// up face
		12, 15, 14, 
		12, 13, 15,

		// down face
		16, 17, 19,
		16, 19, 18

	};	

	
	mesh = std::make_unique<Mesh>();
	mesh->create_mesh(vertices, indices, 100, 36);

	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
}

void render()
{	

	display->clear();
	display->clear_color(0.0f, 0.0f, 0.0f, 1.0f);

	shaders[0]->bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() *  glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(.5f, .5f, .5f));
		shaders[0]->set_mat4("model", model);
		shaders[0]->set_mat4("view", view);
		shaders[0]->set_mat4("projection", projection);
		texture_default->use();
		mesh->render();
	shaders[0]->unbind();
	
	display->swap_buffers();
}

int main()
{
	setup();

	while(!display->should_close())
	{	
		render();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



