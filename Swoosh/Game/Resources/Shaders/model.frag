#version 430

in vec2 UV;
out vec4 colour;

uniform sampler2D modelTexture;

void main()
{
	colour = texture(modelTexture, UV);
}