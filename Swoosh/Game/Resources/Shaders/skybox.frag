#version 430

in vec3 textureCoords;

out vec4 colour;

uniform samplerCube skybox;

void main()
{
	colour = texture(skybox, textureCoords);
	}