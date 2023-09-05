// //------- Ignore this ----------
// #include <filesystem>
// namespace fs = std::filesystem;
// //------------------------------

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb/stb_image.h>
#include <vector>

#include "Camera.h"
#include "EBO.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "imageProcessing.h"
#include "shaderClass.h"

#include "Mesh.h"
const unsigned int width = 1900;
const unsigned int height = 1200;

Vertex vertices[] = {
    //           COORDINATES             /            TexCoord   //
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // Bottom side
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // Bottom side
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // Bottom side
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // Bottom side

    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // up Side
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // up Side
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // up Side
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // up Side

    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // left side
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // left side
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // left side
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // Left Side

    // 12
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // Right side
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},   // Right side
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},  // Right side
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f)}, // Right Side

    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // Facing side
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Facing side
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // Facing side
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // Facing Side

    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // -Facing side
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},   // -Facing side
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // -Facing side
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f)}   // -Facing Side
};
GLuint indices[] = {2,  1,  0,              //
                    3,  2,  0,              //
                    6,  7,  4,              //
                    5,  6,  4,              //
                    9,  10, 11,             //
                    8,  9,  11,             //
                    14, 13, 12,             //
                    15, 14, 12,             //
                    16, 17, 18,             //
                    18, 19, 16,             //
                    20, 21, 23,             //
                    23, 22, 20};            //
Vertex lightVertices[] = {                  //     COORDINATES     //
    Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},  // 0 A
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)}, // 1 B
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},  // 2 C
    Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},   // 3 D
    Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},   // 4 E
    Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},  // 5 F
    Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},   // 6 G
    Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}};   // 7 H

GLuint lightIndices[] = {2, 1, 0, 0, 3, 2, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2, 2, 6, 5, 2, 5, 1, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7};
void compute_TangentBitangent() {
  for (int i = 0; i < 36; i += 3) {
    float edge0x = vertices[indices[i + 1]].position.x - vertices[indices[i]].position.x;
    float edge0y = vertices[indices[i + 1]].position.y - vertices[indices[i]].position.y;
    float edge0z = vertices[indices[i + 1]].position.z - vertices[indices[i]].position.z;

    float edge1x = vertices[indices[i + 2]].position.x - vertices[indices[i]].position.x;
    float edge1y = vertices[indices[i + 2]].position.y - vertices[indices[i]].position.y;
    float edge1z = vertices[indices[i + 2]].position.z - vertices[indices[i]].position.z;

    glm::vec3 edge0 = glm::vec3(edge0x, edge0y, edge0z);
    glm::vec3 edge1 = glm::vec3(edge1x, edge1y, edge1z);
    glm::vec2 deltaUV0 = vertices[indices[i + 1]].texUV - vertices[indices[i]].texUV;
    glm::vec2 deltaUV1 = vertices[indices[i + 2]].texUV - vertices[indices[i]].texUV;

    // one over the determinant
    float invDet = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

    glm::vec3 tangent = glm::vec3(invDet * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
    vertices[indices[i]].tangent = tangent;
    vertices[indices[i + 1]].tangent = tangent;
    vertices[indices[i + 2]].tangent = tangent;
    // std::cout << "tangent: " << vertices[indices[i]].tangent.x << "," << vertices[indices[i]].tangent.y << "," << vertices[indices[i]].tangent.z << std::endl;
    glm::vec3 bitangent = glm::vec3(invDet * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));
    vertices[indices[i]].bitangent = bitangent;
    vertices[indices[i + 1]].bitangent = bitangent;
    vertices[indices[i + 2]].bitangent = bitangent;

    glm::vec3 cross = glm::normalize(glm::cross(edge0, edge1));
    vertices[indices[i]].normal = cross;
    vertices[indices[i + 1]].normal = cross;
    vertices[indices[i + 2]].normal = cross;
  }
}
unsigned int loadTexture(char const *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  std::cout << "TEX_"
            << "Normal"
            << ": " << textureID << std::endl;
  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    format == GL_RGBA ? GL_CLAMP_TO_EDGE
                                      : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  return textureID;
}
int main() {

  glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
  // glm::mat4 cubeModel = glm::mat4(1.0f);
  // cubeModel = glm::translate(cubeModel, cubePos);
  // std::cout << vertices[indices[2]].tangent.x << std::endl;

  // std::cout << "tangent: " << vertices[indices[11]].tangent.x << "," << vertices[indices[11]].tangent.y << "," << vertices[indices[11]].tangent.z << std::endl;

  // Initialize GLFW
  glfwInit();
  unsigned int sample = 8;

  // Tell GLFW what version of OpenGL we are using
  // In this case we are using OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_SAMPLES, sample);

  // Tell GLFW we are using the CORE profile
  // So that means we only have the modern functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
  GLFWwindow *window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
  // Error check if the window fails to create
  if (window == NULL) {
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
  // Shader shaderProgram("default.vert", "default.frag");
  // Shader for light cube
  Shader shaderProgram("default.vert", "default.frag");
  std::string diffusePath = "textures/diffuse.png";
  // Crea normal in textrues/normal_map.png"
  // ImageProcessing ip;
  // ip.compute_normal_map(diffusePath, 1);
  std::string normalPath = "textures/normal.png";

  Shader lightShader("light.vert", "light.frag");
  // Shader normalShader("default.vert", "normals.frag", "normals.geom");

  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
  glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  // glUniform1i(glGetUniformLocation(shaderProgram.ID, "diffuse0"), 1);
  // Gets ID of uniform called "scale"
  // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  Texture textures[]{
      // Texture(diffusePath.c_str(), "diffuse", 0),
  };

  // glActiveTexture(GL_TEXTURE1);
  unsigned int diffuseMap = loadTexture(diffusePath.c_str());
  unsigned int normalMap = loadTexture(normalPath.c_str());
  shaderProgram.Activate();
  glUniform1i(glGetUniformLocation(shaderProgram.ID, "diffuse0"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram.ID, "normal0"), 1);
  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  // glBindTexture(GL_TEXTURE_2D, normalMap);
  // Texture normalTex(normalPath.c_str(), "normal", 1);
  lightShader.Activate();
  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
  glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  // glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));

  // glUniform1i(glGetUniformLocation(shaderProgram.ID, "normal0"), 1);

  // std::vector<Texture> textures = {Texture((diffusePath).c_str(), "diffuse", 0)};

  // Variables that help the rotation of the pyramid
  // float rotation = 0.0f;
  std::vector<Vertex> v(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
  std::vector<GLuint> i(indices, indices + sizeof(indices) / sizeof(GLuint));
  std::vector<Texture> t(textures, textures + sizeof(textures) / sizeof(Texture));

  std::vector<Texture> app{};

  std::vector<Vertex> lv(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
  std::vector<GLuint> li(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
  // std::vector<Texture> lt(app,app+sizeof(app)/sizeof(Texture));
  // Enables the Depth Buffer
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CW);
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
  Camera camera(width, height, cameraPos);

  glfwSwapInterval(0);

  Mesh meshLight(lv, li, app, width, height);

  double prevTime;
  double currTime;
  double timeDiff;
  unsigned int counter = 0;
  compute_TangentBitangent();
  Mesh mesh(v, i, t, width, height);

  while (!glfwWindowShouldClose(window)) {
    currTime = glfwGetTime();
    timeDiff = currTime - prevTime;
    counter++;
    if (timeDiff >= 1.0 / 30.0) {
      std::string fps = std::to_string((1.0 / timeDiff) * counter);
      std::string ms = std::to_string(timeDiff / counter * 1000);
      std::string title = "FPS: " + fps + " ms: " + ms;
      glfwSetWindowTitle(window, title.c_str());
      prevTime = currTime;
      counter = 0;
    }
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    // shaderProgram.Activate();
    camera.Inputs(window);
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    shaderProgram.Activate();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    // glUniform1i(glGetUniformLocation(shaderProgram.ID, "normal0"), 1);

    // normalTex.Bind();
    // normalShader.Activate();
    // camera.Matrix(shaderProgram, "camMatrix");

    compute_TangentBitangent();
    std::vector<Vertex> v(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    mesh.vertices = v;

    meshLight.Draw(window, lightShader, camera);
    mesh.DrawAssistant(window, shaderProgram, camera);
    // mesh.Draw(window, normalShader, camera);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

    // Tells OpenGL which Shader Program we want to use
    // lightShader.Activate();
    // Draw primitives, number of indices, datatype of indices, index of indices
    // glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

    // Draw primitives, number of indices, datatype of indices, index of indices

    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
  }

  // Delete all the objects we've created
  // VAO1.Delete();
  // VBO1.Delete();
  // EBO1.Delete();
  // brickTex.Delete();
  // normalTex.Delete();
  shaderProgram.Delete();
  // lightVAO.Delete();
  // lightVBO.Delete();
  // lightEBO.Delete();
  lightShader.Delete();
  // normalShader.Delete();
  //  Delete window before ending the program
  glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  glfwTerminate();
  return 0;
}