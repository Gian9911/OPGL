#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwTerminate();
	return 0;
}