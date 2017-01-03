#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 textureCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P * V * M * vec4(VertexPosition, 1.0f);
	textureCoords = VertexPosition;
}