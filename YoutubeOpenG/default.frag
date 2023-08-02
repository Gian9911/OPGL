#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;
uniform mat4 modelrot;

void main()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(vec3(modelrot * vec4((Normal),1.0f)));
	vec3 lightDirection = normalize(lightPos - vec3(modelrot * vec4(crntPos,1.0f)));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specular = 0.0f;
    	if (diffuse != 0.0f)
    	{
        	float specularLight = 0.50f;
        	vec3 viewDirection = normalize(camPos - vec3(modelrot * vec4(crntPos,1.0f)));
        	vec3 reflectionDirection = reflect(-lightDirection, normalize(Normal));
        	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
        	specular = specAmount * specularLight;
    	};

	
	// outputs final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}