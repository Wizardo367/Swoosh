#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec2 TextureUV;

out vec2 UV;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P * V * M * vec4(VertexPosition, 1.0f);
	UV = TextureUV;
}