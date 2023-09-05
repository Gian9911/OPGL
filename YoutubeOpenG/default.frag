#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the color from the Vertex Shader
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
// in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;
in vec3 Pos;
in mat3 TBN;
in vec3 lightPosition;
// Gets the position of the camera from the main function
in vec3 cameraPos;

in vec3 T;
in vec3 B;
in vec3 N;

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D normal0;
uniform sampler2D specular0;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function

uniform mat4 modelrot;
uniform mat4 camMatrix; // projection*view 
uniform int lightType;
uniform int normalType;
uniform mat4 scalingMatrix; 
uniform mat4 translationMatrix;
uniform vec3 lightPos;
// uniform mat4 scalingMatrix;
vec4 pointLight()
{

	float a = 0.3f;
	float b = 0.7f;
	float dist = length(lightPosition - crntPos);
	float intens = 1.0f / (a * dist * dist + b * dist + 1.0f);

	vec3 normal = texture(normal0, texCoord).rgb;
	normal = normalize(normal * 2.0f - 1.0f); // [0,1]->[-1,1]
	vec3 color = texture(diffuse0,texCoord).rgb;
	// diffuse
	vec3 lightDir = normalize(lightPosition - crntPos);
	float diff = max(dot(lightDir, normal),0.0f);
	vec3 diffuse = diff*color;
	vec3 ambient = 0.1 * color;
	// specular
	vec3 viewDir = normalize(cameraPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

	vec3 specular = vec3(0.2) * spec;
	return vec4(diffuse, 1.0f);
}

// vec4 pointLight2()
// {
// 		// ambient lighting
// 	float ambient = 0.10f;

// 	float a = 3.0f;
// 	float b = 0.7f;
// 	float dist = length(lightPosition - crntPos);
// 	float intens = 1.0f / (a * dist * dist + b * dist + 1.0f);

// 	// diffuse lighting
// 	//mat4 trasInv = transpose(inverse(scalingMatrix * modelrot));
// 	// vec3 normal = normalize(vec3(trasInv * vec4(Normal,1.0f))); // original
// 	// vec3 normal = normalize(vec3(trasInv * vec4(( texture(normal0, texCoord).xyz * 2.0f - 1.0f),0.0f))); // normal rotated 
// 	vec3 normalTex = normalize(texture(normal0, texCoord).xyz * 2.0f - 1.0f);
// 	vec3 normal = normalize(vec3(vec4((Normal),1.0f)));
// 	// float diffuse=0;
// 	// vec3 lightDirection = normalize(lightPosition);
// 	// vec3 lightDirection = normalize(lightPosition - vec3(scalingMatrix * translationMatrix * modelrot * vec4(crntPos,1.0f)));
// 	vec3 lightDirection = normalize(lightPosition - crntPos);
// 	float diffuse = max(dot(normalTex, lightDirection), 0.0f);
// //if(dot(normal, lightDirection)>0){
// 	// if (normalType == 0){
// 	// 		diffuse = (dot(normal, lightDirection));
// 	// 	}
// 	// else
// 	// 		diffuse = (dot(normalTex, lightDirection));
// 	//}
// 	//else
// 	//	diffuse=0;
// 	// float specular = 0.0f;
// 	// if (diffuse != 0.0f)
// 	// {
// 	// 		float specularLight = 0.50f;
// 	// 		vec3 viewDirection = normalize(camPos - vec3(camMatrix * vec4(crntPos,1.0f)));
// 	// 		vec3 reflectionDirection = normalize(reflect(-lightDirection, normalize(Normal)));
// 	// 		vec3 halfway = normalize(viewDirection + lightDirection); //phong-blind
// 	// 		//  float specAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
// 	// 		float specAmount = pow(max(dot(normal, halfway), 0.0f), 8);
// 	// 		specular = specAmount * specularLight;
// 	// };
// 	ambient = 0;
// 	float specular=0;
// 	intens = 1;
// 	return texture(diffuse0, texCoord) * lightColor * (diffuse*intens + specular + ambient);
// }

// vec4 directionalLight()
// {
// 	float ambient = 0.40f;
// 	// diffuse lighting
// 	mat4 trasInv = transpose(inverse(scalingMatrix * modelrot));
// 	vec3 normal = normalize(vec3(trasInv * vec4((Normal),1.0f))); // normal rotated 
// 	vec3 lightDirection = normalize(lightPosition);
// 	float diffuse = max(dot(normal, lightDirection), 0.0f);

// 	float specular = 0.0f;
// 	if (diffuse != 0.0f)
// 	{
// 			float specularLight = 0.50f;
// 			vec3 viewDirection = normalize(camPos - Pos);
// 			vec3 reflectionDirection = normalize(reflect(-lightDirection, normalize(normal)));
// 			float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
// 			specular = specAmount * specularLight;
// 	};
// 	ambient = 0;
// 	return texture(diffuse0, texCoord) * lightColor * (diffuse + specular + ambient);
// }

vec4 spotLight()
{
	float ambient = 0.1f;
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	// diffuse lighting
	//mat4 trasInv = transpose(inverse(scalingMatrix * modelrot));
	//vec3 normal = normalize(vec3(trasInv * vec4((Normal),1.0f))); // normal rotated 
	vec3 normal = texture(normal0, texCoord).rgb;
	normal = normalize(normal * 2.0f - 1.0f); // [0,1]->[-1,1]
	// vec3 lightDirection = normalize(lightPosition);
	vec3 lightDirection = normalize(lightPosition - crntPos);
	float diff = max(dot(lightDirection, normal), 0.0f);
	float intens=0.0f;
	float specular = 0.0f;
	vec3 color = texture(diffuse0, texCoord).rgb;
	vec3 diffuse = diff * color;
	if (diff != 0.0f)
	{
			float specularLight = 0.50f;
			vec3 viewDirection = normalize(cameraPos - crntPos);
			vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));
			float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 64);
			specular = specAmount * specularLight;
			//diffuse=0;
			float angle = dot(normalize(lightPos),normalize(lightDirection)); //?????????? //1->light 0->dark
			intens = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	};
	// return texture(diffuse0, texCoord) * lightColor*intens*specular;
	return texture(diffuse0, texCoord) * lightColor * (diff*intens + specular*intens + ambient);
}
void main()
{
	vec4 app;
	if(lightType==0)
		app = spotLight();
	if(lightType==1)
		app = pointLight();
	FragColor=app;
}