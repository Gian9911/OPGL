#include "Mesh.h"
#include "imageProcessing.h"
const unsigned int width = 1910;
const unsigned int height = 1600;

// Number of samples per pixel for MSAA
unsigned int samples = 8;



float rectangleVertices[] = {
    //  Coords   // texCoords
    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 
    -1.0f, 0.0f, 0.0f, -1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f};

// Vertices for plane with texture
std::vector<Vertex> vertices = {
    // Faccia inferiore del cubo  
    // coords,normal,color,tex_coords
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia superiore del cubo
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia sinistra del cubo
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia destra del cubo 2-6-7-3 - 12-13-14-15
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

    // Faccia frontale del cubo 5,6,1,2, - 16,17,18,19
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

    // Faccia dietro del cubo 4,7,0,3 - 20,21,22,23
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

};
// Indices for plane with texture
std::vector<GLuint> indices = {0, 1, 2, 0, 2, 3, 4, 7, 6, 4, 6, 5, 11, 10, 9, 11, 9, 8, 12, 13, 14, 12, 14, 15, 16, 17, 19, 19, 18, 16, 23, 21, 20, 20, 22, 23};


// Vertices for plane with texture
std::vector<Vertex> lightVertertices = {
    // Faccia inferiore del cubo
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia superiore del cubo
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia sinistra del cubo
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

    // Faccia destra del cubo 2-6-7-3 - 12-13-14-15
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

    // Faccia frontale del cubo 5,6,1,2, - 16,17,18,19
    Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

    // Faccia dietro del cubo 4,7,0,3 - 20,21,22,23
    Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

};
// Indices for plane with texture
std::vector<GLuint> lightIndices = {0, 1, 2, 0, 2, 3, 4, 7, 6, 4, 6, 5, 11, 10, 9, 11, 9, 8, 12, 13, 14, 12, 14, 15, 16, 17, 19, 19, 18, 16, 23, 21, 20, 20, 22, 23};

int main() {
  // Controls the gamma function
  float gamma = 2.2f;
  // Initialize GLFW
  glfwInit();

  // Tell GLFW what version of OpenGL we are using
  // In this case we are using OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Only use this if you don't have a framebuffer
  // glfwWindowHint(GLFW_SAMPLES, samples);
  // Tell GLFW we are using the CORE profile
  // So that means we only have the modern functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFWwindow object of 800 by 800 pixels
  GLFWwindow *window = glfwCreateWindow(width, height, "OPGL", NULL, NULL);
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

  // Generates shaders
  Shader shaderProgram("default.vert", "default.frag", "default.geom");
  Shader lightShader("light.vert", "light.frag");
  Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");
  

  // Take care of all the light related things
  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos = glm::vec3(0.0f, 0.5f, 0.0f);
  //glm::mat4 lightModel = glm::mat4(1.0f);
	//lightModel = glm::translate(lightModel, lightPos);
  

  shaderProgram.Activate();
  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  
  framebufferProgram.Activate();
  glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
  glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);


  // Enables the Depth Buffer
  glEnable(GL_DEPTH_TEST);

  // Enables Multisampling
  glEnable(GL_MULTISAMPLE);

  // Enables Cull Facing
  glEnable(GL_CULL_FACE);
  // Keeps front faces
  glCullFace(GL_FRONT);
  // Uses counter clock-wise standard
  glFrontFace(GL_CCW);

  // Creates camera object
  Camera camera(width, height, glm::vec3(0.0f, 0.5f, 6.0f));

  // Prepare framebuffer rectangle VBO and VAO
  unsigned int rectVAO, rectVBO;
  glGenVertexArrays(1, &rectVAO);
  glGenBuffers(1, &rectVBO);
  glBindVertexArray(rectVAO);
  glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

  // Variables to create periodic event for FPS displaying
  double prevTime = 0.0;
  double crntTime = 0.0;
  double timeDiff;
  // Keeps track of the amount of frames in timeDiff
  unsigned int counter = 0;

  // Use this to disable VSync (not advized)
  // glfwSwapInterval(0);

  // Create Frame Buffer Object
  unsigned int FBO;
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  // Create Framebuffer Texture
  unsigned int framebufferTexture;
  glGenTextures(1, &framebufferTexture);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB16F, width, height, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);

  // Create Render Buffer Object
  unsigned int RBO;
  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

  // Error checking framebuffer
  auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer error: " << fboStatus << std::endl;

  // Create Frame Buffer Object
  unsigned int postProcessingFBO;
  glGenFramebuffers(1, &postProcessingFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

  // Create Framebuffer Texture
  unsigned int postProcessingTexture;
  glGenTextures(1, &postProcessingTexture);
  glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessingTexture, 0);

  // Error checking framebuffer
  fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Post-Processing Framebuffer error: " << fboStatus << std::endl;

  // Paths to textures

  std::string diffusePath = "textures/diffuse.png";
  // Crea normal in textrues/normal_map.png"
  ImageProcessing ip;
  ip.compute_normal_map(diffusePath, 1);
  ip.compute_specular_map(diffusePath);
  std::string normalPath = "textures/normal_map.png";

  std::vector<Texture> textures = {Texture((diffusePath).c_str(), "diffuse", 0)};
  std::vector<Texture> textures2 = {};

  // Plane with the texture
  Mesh mesh(vertices, indices, textures);
  Mesh lightMesh(lightVertertices, lightIndices, textures2);
  // Normal map for the plane
  Texture normalMap((normalPath).c_str(), "normal", 10);

  float angle = 0.0f;
	float s = 1.0f;
  glm::vec3 tr = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 rot = glm::mat4(1.0f);
  // Main while loop
  while (!glfwWindowShouldClose(window)) {
    	glm::vec3 direction = glm::vec3(1.0f);

    // Updates counter and times
    crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;
    counter++;

    if (timeDiff >= 1.0 / 30.0) {
      // Creates new title
      std::string FPS = std::to_string((1.0 / timeDiff) * counter);
      std::string ms = std::to_string((timeDiff / counter) * 1000);
      std::string newTitle = "OPGL - " + FPS + "FPS / ";
      glfwSetWindowTitle(window, newTitle.c_str());

      // Resets times and counter
      prevTime = crntTime;
      counter = 0;
    }

    // Bind the custom framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  
    // Specify the color of the background
    glClearColor(pow(0.07f, gamma), pow(0.13f, gamma), pow(0.17f, gamma), 1.0f);
    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Enable depth testing since it's disabled when drawing the framebuffer rectangle
    glEnable(GL_DEPTH_TEST);

    camera.Inputs(window);
    // Updates and exports the camera matrix to the Vertex Shader
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    shaderProgram.Activate();
    // normalMap.Bind();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "normal0"), 1);

/*    //rotation
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			angle = 0.1f;
      rot = glm::rotate(rot, glm::radians(angle), glm::vec3(1.0f,0.0f,0.0f));

		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{

			angle = 0.1f;
			rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));

		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{

			angle = 0.1f;
			rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f,0.0f,1.0f));

		}
	
		//translation
    		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			angle = 0.1f;
      rot = glm::rotate(rot, glm::radians(angle), glm::vec3(1.0f,0.0f,0.0f));

		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{

			angle = 0.1f;
			rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));

		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{

			angle = 0.1f;
			rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f,0.0f,1.0f));

    }
		
		//rot = glm::rotate(rot, glm::radians(angle), direction);
    angle = 0.0f;
    direction = glm::vec3(0.0001f, 0.0f, 0.0f);

		// Draw the normal model
		mesh.Draw(window, shaderProgram, camera, rot);//framebuffer has msaa can't do anything"
    //lightMesh.Draw(window, lightShader, camera,glm::quat(1.0f, 0.0f, 0.0f, 0.0f),glm::vec3(0.001f),lightModel, glm::vec3(1.0f));//framebuffer has msaa can't do anything
*/
    mesh.DrawAssistant(mesh, window, shaderProgram, camera);

    // Make it so the multisampling FBO is read while the post-processing FBO is drawn
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFBO);
    // Conclude the multisampling and copy it to the post-processing FBO
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Draw the framebuffer rectangle
    framebufferProgram.Activate();
    glBindVertexArray(rectVAO);
    glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
    glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
  }

  // Delete all the objects we've created
  shaderProgram.Delete();
  
  glDeleteFramebuffers(1, &FBO);
  glDeleteFramebuffers(1, &postProcessingFBO);
  
  // Delete window before ending the program
  glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  glfwTerminate();
  return 0;
}