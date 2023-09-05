#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures, int w, int h) {
  Mesh::vertices = vertices;
  Mesh::indices = indices;
  Mesh::textures = textures;
  width = w;
  height = h;
}

void Mesh::Draw(GLFWwindow *window, Shader &shader, Camera &camera
                // glm::mat4 matrix,//model
                // glm::vec3 translation

) {
  VAO.Bind();
  // Generates Vertex Buffer Object and links it to vertices
  VBO VBO(vertices);
  // Generates Element Buffer Object and links it to indices
  EBO EBO(indices);
  // Links VBO attributes such as coordinates and colors to VAO
  VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);                    // pos
  VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));  // tex
  VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(5 * sizeof(float)));  // norm
  VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void *)(8 * sizeof(float)));  // tangent
  VAO.LinkAttrib(VBO, 4, 3, GL_FLOAT, sizeof(Vertex), (void *)(11 * sizeof(float))); // bitangent

  // Unbind all to prevent accidentally modifying them
  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();
  // Bind shader to be able to access uniforms
  shader.Activate();
  VAO.Bind();

  // Keep track of how many of each type of textures we have
  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;
  unsigned int numNormal = 0;
  for (unsigned int i = 0; i < textures.size(); i++) {
    std::string num;
    std::string type = textures[i].type;
    if (type == "diffuse") {
      num = std::to_string(numDiffuse++);
    } else if (type == "specular") {
      num = std::to_string(numSpecular++);
    } 
    else if (type == "normal")
      num = std::to_string(numNormal++);
    textures[i].texUnit(shader, (type + num).c_str(), i);
    textures[i].Bind();
  }
  // Take care of the camera Matrix
  glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
  camera.Matrix(shader, "camMatrix");

  glm::mat4 model = glm::mat4(1.0f);

  glm::mat4 rotationNormalDX = glm::mat4(1.0f);
  rotationNormalDX = glm::rotate(rotationNormalDX, glm::radians(glm::radians(1.57f)), glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 proj = glm::mat4(1.0f);
  glm::mat4 scalingMatrix = glm::mat4(1.0f);
  glm::mat4 translationMatrix = glm::mat4(1.0f);
  // Assigns different transformations to each matrix
  model = glm::rotate(model, glm::radians(rotation), direction);
  view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
  proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
  scalingMatrix = glm::scale(scalingMatrix, glm::vec3(scale));
  translationMatrix = glm::translate(translationMatrix, (Tdirection));
  // modelPosition = Tdirection;

  /////////////
  // pyramidPos = vec3(vec4(pyramidPos,1.0) * translationMatrix);
  //////////////
  rotationMatrix = model * rotationMatrix;
  // Outputs the matrices into the vertices Shader
  int modelLoc = glGetUniformLocation(shader.ID, "modelrot");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

  int rotDx = glGetUniformLocation(shader.ID, "rotationNormalDX");
  glUniformMatrix4fv(rotDx, 1, GL_FALSE, glm::value_ptr(rotationNormalDX));

  // int viewLoc = glGetUniformLocation(shader.ID, "view");
  // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  // int projLoc = glGetUniformLocation(shader.ID, "projection");
  // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
  int scaleLoc = glGetUniformLocation(shader.ID, "scalingMatrix");
  glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scalingMatrix));
  int tranLoc = glGetUniformLocation(shader.ID, "translationMatrix");
  glUniformMatrix4fv(tranLoc, 1, GL_FALSE, glm::value_ptr(translationMatrix));

  // Draw the actual mesh
  GLuint glight = glGetUniformLocation(shader.ID, "lightType");
  glUniform1i(glight, lightType);
  GLuint n = glGetUniformLocation(shader.ID, "normalType");
  glUniform1i(n, normalType);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawAssistant(GLFWwindow *window, Shader &shader, Camera &camera) {
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { // prototipo luce dinamica
    lightType++;
    lightType = lightType % 2;
  }
  if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) { // prototipo normale dinamica
    normalType++;
    normalType = normalType % 2;
  }
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && scale < 1.6) {
    scale += 0.001f;
  }
  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && scale > 0.5) {
    scale -= 0.001f;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    Tdirection += glm::vec3(0.0f, -1.0f / sensibility, 0.0f);
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    Tdirection += glm::vec3(0.0f, 1.0f / sensibility, 0.0f);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    Tdirection += glm::vec3(-1.0f / sensibility, 0.0f, 0.0f);
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    Tdirection += glm::vec3(1.0f / sensibility, 0.0f, 0.0f);
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
    Tdirection += glm::vec3(0.0f, 0.0f, 1.0f / sensibility);
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) { //??
    Tdirection += glm::vec3(0.0f, 0.0f, -1.0f / sensibility);
  }

  ////////////////////
  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    // glm::vec3 cameraDirection = glm::normalize(camera.Position - camera.Orientation); // pyramidPos
    glm::vec3 newDir = Tdirection + (glm::cross(camera.Orientation, camera.Up) / sensibility);
    std::cout << "ORI: " << camera.Orientation.x << "," << camera.Orientation.y << "," << camera.Orientation.z << std::endl;
    std::cout << "VET: " << (-camera.Position + Tdirection).x << "," << (-camera.Position + Tdirection).y << "," << (-camera.Position + Tdirection).z << std::endl;
    std::cout << "Angle: " << abs(glm::angle(glm::normalize(camera.Orientation), glm::normalize(-camera.Position + newDir))) << std::endl;
    bool valid_move = (abs(glm::angle(glm::normalize(camera.Orientation), glm::normalize(-camera.Position + Tdirection)) <= glm::radians(35.0f)));
    if (valid_move)
      Tdirection += glm::cross(camera.Orientation, camera.Up) / sensibility; // asse x della camera
    // camera.Orientation = Tdirection - camera.Position;
    std::cout << "Orientation: " << camera.Orientation.x << "," << camera.Orientation.y << "," << camera.Orientation.z << std::endl;
    // std::cout << "Tdirection: " << Tdirection.x <<","<< Tdirection.y <<","<< Tdirection.z << std::endl;
    // direction = glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * camera.cameraMatrix);
  }
  // if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) {std::cout<<"ciao"<<std::endl;}
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    glm::vec3 newDir = Tdirection + (glm::vec3(0.0f, 1.0f, 0.0f) / sensibility);
    bool valid_move = ((glm::angle(newDir - camera.Position, glm::vec3(0, 1, 0))) - glm::radians(90.0f)) <= glm::radians(85.0f);
    if (valid_move) {
      Tdirection += glm::vec3(0.0f, 1.0f, 0.0f) / sensibility;
      camera.Orientation = Tdirection - camera.Position;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
    // Tdirection += (glm::vec3(0.0f, 0.0f, -1.0f / sensibility));
    // rotation = 0.1f;
    Tdirection += glm::normalize(camera.Position - Tdirection) / sensibility; // pyramidPos
    // if (modelPosition != glm::vec3(0, 0, 0)) {
    camera.Orientation = Tdirection - camera.Position;
    // }
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // glm::vec4 app = camera.cameraMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    // direction = glm::vec3(0.0f, 1.0f, 0.0f);
    //  direction.z = 0;
    //  direction.b = 0;
    //  direction.p = 0;
  }

  ////////////////////
  // glUniform1f(glGetUniformLocation(shader.ID, "lightType"), lightType);

  // double crntTime = glfwGetTime();
  rotation = 0.0f;
  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    rotation = 0.1f;
    glm::vec3 cameraDirection = glm::normalize(camera.Position - Tdirection);
    direction = glm::normalize(glm::cross(camera.Up, cameraDirection)); // asse x della camera
    // std::cout <<"DIR_X: "<< direction.x << ";" << direction.y << ";" << direction.z << std::endl;
    // direction = glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * camera.cameraMatrix);
  }
  if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
    rotation = 0.1f;
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // glm::vec4 app = camera.cameraMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    direction = glm::vec3(0.0f, 1.0f, 0.0f);
    // direction.z = 0;
    // direction.b = 0;
    // direction.p = 0;
  }
  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
    rotation = 0.1f;
    direction = glm::normalize(camera.Position - Tdirection);
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // glm::vec4 app = camera.cameraMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    // direction = glm::vec3(0.0f, 1.0f, 0.0f);
    //  direction.z = 0;
    //  direction.b = 0;
    //  direction.p = 0;
  }
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
    rotation = 0.1f;
    direction = glm::vec3(1.0f, 0.0f, 0.0f);
    // direction = glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * camera.cameraMatrix);
  }

  if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
    rotation = 0.1f;
    direction = glm::vec3(0.0f, 0.0f, 1.0f);
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // glm::vec4 app = camera.cameraMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    // direction = glm::vec3(0.0f, 1.0f, 0.0f);
    //  direction.z = 0;
    //  direction.b = 0;
    //  direction.p = 0;
  }
  Draw(window, shader, camera);
}