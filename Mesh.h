#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	glm::vec3 pos = glm::vec3(0.0f);
	float angle = 0.0f;
	float s = 1.0f;
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 matrix = glm::mat4(1.0f);

	// Initializes the mesh
	Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);

	// Draws the mesh
	void Draw(
		GLFWwindow *window,
		Shader &shader,
		Camera &camera,
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f)

	);
	void DrawAssistant(
		Mesh mesh,
		GLFWwindow *window,
		Shader &shader,
		Camera &camera);
};
#endif