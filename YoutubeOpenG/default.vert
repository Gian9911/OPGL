#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;
// Colors
// Texture Coordinates
layout (location = 1) in vec2 aTex; 
// Normal
layout(location = 2) in vec3 aNormal;
// Tangent
layout(location = 3) in vec3 aTangent;
// Bitangent
layout(location = 4) in vec3 aBitangent;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 modelrot; // rotation model
uniform mat4 view;
uniform mat4 proj;
uniform mat4 camMatrix; // projection*view 
uniform mat4 model; // cube model
uniform mat4 scalingMatrix;
uniform mat4 translationMatrix;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform int lightType;

 
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
// out vec3 Normal;
out vec3 crntPos;
out vec3 Pos;
//out mat4 model;
out vec3 lightPosition;
out vec3 cameraPos;
out mat3 TBN;

out vec3 T;
out vec3 B;
out vec3 N;


void main()
{ 
	// crntPos = vec3(translationMatrix * scalingMatrix * modelrot *model * vec4(aPos,1.0f));
	crntPos = vec3(translationMatrix * modelrot * scalingMatrix * vec4(aPos, 1.0f));
	Pos = crntPos;
	gl_Position =   camMatrix  * translationMatrix * modelrot * scalingMatrix * vec4(aPos, 1.0f); //contains the position of the current vertex - aveva crntPos
	texCoord = aTex;
	
	// Normal=aNormal;
	// Pos = vec3(translationMatrix * modelrot * scalingMatrix * vec4(aPos, 1.0)); //contains the position of the current vertex;
	// crntPos = crntPos;
	mat3 my_model = transpose(inverse(mat3(translationMatrix * modelrot * scalingMatrix)));
	
	 T = normalize(vec3(my_model * aTangent));
	 N = normalize(vec3(my_model * aNormal));
	 T = normalize(T - dot(T, N) * N);
   B = cross(N, T);

	TBN = transpose(mat3(T,B,N));
	// TBN is an orthogonal matrix and so its inverse is equal to its transpose
	// TBN = transpose(TBN);
	lightPosition = TBN * lightPos;
	cameraPos = TBN * camPos;
	crntPos =   TBN * crntPos;
	}
