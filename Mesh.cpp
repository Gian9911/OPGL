#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(
	GLFWwindow *window,
	Shader &shader,
	Camera &camera,
	glm::quat rotation,
	glm::vec3 scale,
	glm::mat4 matrix,
	glm::vec3 translation

)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, glm::vec3(s));

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawAssistant(
	Mesh mesh,
	GLFWwindow *window,
	Shader &shader,
	Camera &camera)
{
	// scale
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		s += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		s -= 0.001f;
	}
    // translation
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		translation += glm::vec3(0.01f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		translation -= glm::vec3(0.01f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		translation += glm::vec3(0.0f, 0.0f, 0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		translation -= glm::vec3(0.0f, 0.0f, 0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
	{
		translation += glm::vec3(0.0f, 0.01f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
	{
		translation -= glm::vec3(0.0f, 0.01f, 0.0f);
	}
	
	// rotation
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		angle = 0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{

		angle = 0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{

		angle = 0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		angle = -0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{

		angle = -0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{

		angle = -0.1f;
		rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	}


	angle = 0.0f;
	direction = glm::vec3(0.0001f, 0.0f, 0.0f);

	// Draw the normal model
	mesh.Draw(window, shader, camera, rot, glm::vec3(s), glm::mat4(1.0f), translation);
}