#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"Texture.h"

int main()
{
	// Vertices coordinates
	
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};
	
	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Lower left triangle
		0, 3, 2, // Lower right triangle
	};

	int w = 800;
	int h = 800;
	float startTime = 0.0;
	float currentTime = 0.0;
	float color = 0.0;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// using glfw 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// for compatibiities etc

	GLFWwindow* window = glfwCreateWindow(w, h, "I made this", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, w, h);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//texture
	Texture susImage("im.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	susImage.texUnit(shaderProgram, "tex0", 0);

	startTime = float(glfwGetTime());
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//glfwSwapBuffers(window);
		currentTime = float(glfwGetTime());
		if (currentTime - startTime >= 1.0)
		{
			startTime = currentTime;
			currentTime += 0.1;
			color += 0.1;
			glClearColor(float(sin(color)), float(cos(color)), float(tan(color)), 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			shaderProgram.Activate();
			glUniform1f(uniID, 0.5f);
			susImage.Bind();
			// Bind the VAO so OpenGL knows to use it
			VAO1.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	susImage.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}