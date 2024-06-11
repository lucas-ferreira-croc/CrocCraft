#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <vector>

#include "texture/Texture.h"
#include "display/Display.h"
#include "shader/Shader.h"
#include "mesh/Mesh.h"

const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1920;

std::vector<std::unique_ptr<Shader>> shaders;
std::unique_ptr<Mesh> mesh;
std::unique_ptr<Display> display;
std::shared_ptr<Texture> texture_default;



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

	texture_default = std::make_shared<Texture>("C:\\dev\\CrocCraft\\CroCraft\\CroCraft\\assets\\textures\\dirt_and_grass.png");
	texture_default->load_textureA();
	
	float vertices[] = {
	   1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
	   1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom left
	   -1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};	

	mesh = std::make_unique<Mesh>();
	mesh->create_mesh(vertices, indices, 20, 6);
}

void render()
{
	display->clear();
	display->clear_color(0.0f, 0.0f, 0.0f, 1.0f);

	shaders[0]->bind();
		glm::mat4 model(1.0f);
		shaders[0]->set_mat4("model", model);
		texture_default->use();
		mesh->render();
	shaders[0]->unbind();
	
	display->swap_buffers();
}

int main()
{
	setup();
	//////////////////////////////////////////////////////////////////////////////

	while(!display->should_close())
	{	
		render();
		/*glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/

		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}



