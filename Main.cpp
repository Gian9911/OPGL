

#include"Model.h"

// if you see OUTLINE in comments it means that it is needed for outlining the model, not necessary
const unsigned int width = 1910;
const unsigned int height = 1600;


int main()
{
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
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);





	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	//Shader outliningProgram("outlining.vert", "outlining.frag"); OUTLINING

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);





	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	//OUTLINING glEnable(GL_STENCIL_TEST); OUTLINING
	//OUTLINING glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Original code from the tutorial
	 Model model("models/bunny/scene.gltf");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// OUTLINING add after gl_depth_buffer_bit | GL_STENCIL_BUFFER_BIT

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(10.0f, 0.1f, 100.0f);

		// Draw a model
		//OUTLINING glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//OUTLINING glStencilMask(0xFF);
		model.Draw(shaderProgram, camera);

		//OUTLINING glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//OUTLINING glStencilMask(0xFF);
		//OUTLINING glDisable(GL_DEPTH_TEST);
		//OUTLINING outliningProgram.Activate();
		//OUTLINING glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
		//OUTLINING model.Draw(outliningProgram, camera);

		//OUTLINING glStencilMask(0xFF);
		//OUTLINING glStencilFunc(GL_ALWAYS, 0, 0xFF);
		//OUTLINING glEnable(GL_DEPTH_TEST);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}