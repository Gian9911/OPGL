// #include "Model.h"

// const unsigned int width = 800;
// const unsigned int height = 800;

// int main() {
//   float gamma = 2.2f;
//   unsigned int samples = 8;
//   // Initialize GLFW
//   glfwInit();

//   // Tell GLFW what version of OpenGL we are using
//   // In this case we are using OpenGL 3.3
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   // Tell GLFW we are using the CORE profile
//   // So that means we only have the modern functions
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//   // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
//   GLFWwindow *window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
//   // Error check if the window fails to create
//   if (window == NULL) {
//     std::cout << "Failed to create GLFW window" << std::endl;
//     glfwTerminate();
//     return -1;
//   }
//   // Introduce the window into the current context
//   glfwMakeContextCurrent(window);

//   // Load GLAD so it configures OpenGL
//   gladLoadGL();
//   // Specify the viewport of OpenGL in the Window
//   // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//   glViewport(0, 0, width, height);

//   // Generates Shader object using shaders default.vert and default.frag
//   Shader shaderProgram("default_model.vert", "default_model.frag", "default.geom");
//   Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");

//   // Take care of all the light related things
//   glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//   glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
//   glm::mat4 lightModel = glm::mat4(1.0f);
//   lightModel = glm::translate(lightModel, lightPos);

//   shaderProgram.Activate();

//   glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
//   glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

//   glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
//   glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);

//   // Enables the Depth Buffer
//   glEnable(GL_DEPTH_TEST);

//   glEnable(GL_MULTISAMPLE);

//   // Enables Cull Facing
//   glEnable(GL_CULL_FACE);
//   // Keeps front faces
//   glCullFace(GL_FRONT);
//   // Uses counter clock-wise standard
//   glFrontFace(GL_CCW);

//   // Creates camera object
//   Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
//   // Create Frame Buffer Object
//   unsigned int FBO;
//   glGenFramebuffers(1, &FBO);
//   glBindFramebuffer(GL_FRAMEBUFFER, FBO);

//   Model model("models/bunny/scene.gltf");

//   // Create Framebuffer Texture
//   unsigned int framebufferTexture;
//   glGenTextures(1, &framebufferTexture);
//   glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
//   glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB16F, width, height, GL_TRUE);
//   glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
//   glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
//   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);

//   // Create Render Buffer Object
//   unsigned int RBO;
//   glGenRenderbuffers(1, &RBO);
//   glBindRenderbuffer(GL_RENDERBUFFER, RBO);
//   glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
//   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

//   // Error checking framebuffer
//   auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//   if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
//     std::cout << "Framebuffer error: " << fboStatus << std::endl;

//   // Create Frame Buffer Object
//   unsigned int postProcessingFBO;
//   glGenFramebuffers(1, &postProcessingFBO);
//   glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

//   // Create Framebuffer Texture
//   unsigned int postProcessingTexture;
//   glGenTextures(1, &postProcessingTexture);
//   glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessingTexture, 0);

//   // Error checking framebuffer
//   fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//   if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
//     std::cout << "Post-Processing Framebuffer error: " << fboStatus << std::endl;

//   // Paths to textures

//   std::string diffusePath = "textures/diffuse_denim.png";
//   std::string normalPath = "textures/normal_denim.png";

//   std::vector<Texture> textures = {Texture((diffusePath).c_str(), "diffuse", 0)};
// 	std::vector<Mesh> planes;
//   // Plane with the texture
//   for (int i = 0; i < model.meshes.size(); i++) {
//     Mesh plane(model.meshes[i].vertices, model.meshes[i].indices, model.meshes[i].textures);
//   }
//   // Normal map for the plane
//   Texture normalMap((normalPath).c_str(), "normal", 1);

//   /*
//    * I'm doing this relative path thing in order to centralize all the resources into one folder and not
//    * duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
//    * folder and then give a relative path from this folder to whatever resource you want to get to.
//    * Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
//    */
//   // std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
//   // std::string modelPath = "/Resources/YoutubeOpenGL 13 - Model Loading/models/bunny/scene.gltf";

//   // Load in a model

//   // Original code from the tutorial
//   // Model model("models/bunny/scene.gltf");

//   // Main while loop
//   while (!glfwWindowShouldClose(window)) {
//     // Specify the color of the background
//     glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//     // Clean the back buffer and depth buffer
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     // Handles camera inputs
//     camera.Inputs(window);
//     // Updates and exports the camera matrix to the Vertex Shader
//     camera.updateMatrix(45.0f, 0.1f, 100.0f);

//     // Draw a model
//     model.Draw(shaderProgram, camera);

//     // Swap the back buffer with the front buffer
//     glfwSwapBuffers(window);
//     // Take care of all GLFW events
//     glfwPollEvents();
//   }

//   // Delete all the objects we've created
//   shaderProgram.Delete();
//   // Delete window before ending the program
//   glfwDestroyWindow(window);
//   // Terminate GLFW before ending the program
//   glfwTerminate();
//   return 0;
// }