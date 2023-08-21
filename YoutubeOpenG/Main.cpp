//------- Ignore this ----------
#include <filesystem>
namespace fs = std::filesystem;
//------------------------------

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "Camera.h"
#include "imageProcessing.h"
#include "EBO.h"

const unsigned int width = 1500;
const unsigned int height = 1500;

// Vertices coordinates
GLfloat Pvertices[] =
	{
		//     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,	// Bottom side
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 5.0f, 0.0f, -1.0f, 0.0f, // Bottom side
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 5.0f, 0.0f, -1.0f, 0.0f,	// Bottom side
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f,	// Bottom side

		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, -0.8f, 0.5f, 0.0f,	// Left Side
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, -0.8f, 0.5f, 0.0f, // Left Side
		0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, -0.8f, 0.5f, 0.0f,	// Left Side

		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, 0.5f, -0.8f, // Non-facing side
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.5f, -0.8f,	// Non-facing side
		0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f, 0.5f, -0.8f,	// Non-facing side

		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.8f, 0.5f, 0.0f, // Right side
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.8f, 0.5f, 0.0f,  // Right side
		0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.8f, 0.5f, 0.0f,  // Right side

		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, 0.5f, 0.8f,  // Facing side
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.5f, 0.8f, // Facing side
		0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f, 0.5f, 0.8f	  // Facing side
};
// Vertices coordinates
GLfloat vertices[] =
	{
		//     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.25f, -0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, -0.25f, 0.0f,	// Bottom side
		-0.25f, -0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.25f, 0.0f, -0.25f, 0.0f, // Bottom side
		0.25f, -0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.25f, 0.0f, -0.25f, 0.0f,	// Bottom side
		0.25f, -0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.0f, 0.0f, -0.25f, 0.0f,	// Bottom side

		-0.25f, 0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.25f, 0.0f,	// up Side
		-0.25f, 0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.25f, 0.0f, 0.25f, 0.0f, // up Side
		0.25f, 0.25f, 0.25f, 0.92f, 0.86f, 0.76f, 0.25f, 0.25f, 0.0f, 0.25f, 0.0f,	// up Side
		0.25f, 0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.25f, 0.0f, 0.0f, 0.25f, 0.0f,	// up Side


		-0.25f, -0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, -0.25f, 0.0f, 0.0f, // left side
		-0.25f, -0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.25f, -0.25f, 0.0f, 0.0f,	// left side
		-0.25f, 0.25f, 0.25f, 0.92f, 0.86f, 0.76f, 0.25f, 0.25f, -0.25f, 0.0f, 0.0f,	// left side
		-0.25f, 0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.25f, 0.0f, -0.25f, 0.0f, 0.0f,	// Left Side


		0.25f, -0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.25f, 0.0f, 0.0f, // Right side
		0.25f, 0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.0f, 0.25f, 0.0f, 0.0f,  // Right side
		0.25f, 0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.25f, 0.25f, 0.25f, 0.0f, 0.0f,  // Right side
		0.25f, -0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.0f, 0.25f, 0.25f, 0.0f, 0.0f,	// Right Side


		-0.25f, 0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.0f, 0.0f, 0.0f, 0.25f,  // Facing side
		0.25f, 0.25f, 0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.25f, 0.0f, 0.0f, 0.25f, // Facing side
		-0.25f, -0.25f, 0.25f, 0.92f, 0.86f, 0.76f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f,	  // Facing side
		0.25f, -0.25f, 0.25f, 0.92f, 0.86f, 0.76f, 0.0f, 0.25f, 0.0f, 0.0f, 0.25f,	// Facing Side
		
		-0.25f, 0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.0f, 0.0f, 0.0f, -0.25f,  // -Facing side
		0.25f, 0.25f, -0.25f, 0.83f, 0.70f, 0.44f, 0.25f, 0.25f, 0.0f, 0.0f, -0.25f, // -Facing side
		-0.25f, -0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.0f, 0.0f, 0.0f, 0.0f, -0.25f,	  // -Facing side
		0.25f, -0.25f, -0.25f, 0.92f, 0.86f, 0.76f, 0.0f, 0.25f, 0.0f, 0.0f, -0.25f,	// -Facing Side
	};
GLuint indices[] =
	{0, 1, 2, 0, 2, 3, 4, 7, 6, 4, 6, 5, 11, 10, 9, 11, 9, 8, 12, 13, 14, 12, 14, 15, 16, 17, 19, 19, 18, 16, 23, 21, 20, 20, 22, 23};

// Indices for vertices order
GLuint Pindices[] =
	{
		0, 1, 2,	// Bottom side
		0, 2, 3,	// Bottom side
		4, 6, 5,	// Left side
		7, 9, 8,	// Non-facing side
		10, 12, 11, // Right side
		13, 15, 14	// Facing side
};

GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f};

GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7};

int main()
{


/*
     const int MAX_SIZE = 100; // Numero massimo di elementi nell'array
    GLfloat vertices[MAX_SIZE];
    GLuint arraySize = 0;

    std::ifstream inputFile("vert.txt"); // Sostituisci "file.txt" con il percorso del tuo file di testo

    if (!inputFile.is_open()) {
        std::cerr << "Impossibile aprire il file." << std::endl;
        return 1;
    }

    GLfloat intValue;
    while (inputFile >> intValue && arraySize < MAX_SIZE) {
        vertices[arraySize] = intValue;
        arraySize++;
    }

    inputFile.close();

    // Ora vertices contiene i numeri interi letti dal file
    for (int i = 0; i < arraySize; i++) {
        std::cout << vertices[i] << " ";
    }


*/
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow *window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates vertices Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates vertices Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates vertices Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates vertices Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);//0.5,0.5,0.5
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));//TODO
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Gets ID of uniform called "scale"
	// GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture brickTex("textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	std::string diffusePath = "textures/planks.png";
  // Crea normal in textrues/normal_map.png"
  ImageProcessing ip;
  ip.compute_normal_map(diffusePath, 1);
  std::string normalPath = "textures/normal_map.png";

  //std::vector<Texture> textures = {Texture((diffusePath).c_str(), "diffuse", 0)};


	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");
		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.009f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		// Outputs the matrices into the vertices Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "modelrot");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		// glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the vertices Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Draw primitives, number of indices, datatype of indices, index of indices
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}