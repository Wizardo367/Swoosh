// Used in IMAT3111

#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 VertPos; //Vertex position in eye coords
out vec3 Normal; //Transformed normal

uniform mat3 NormalMatrix;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
   VertPos = vec3(V * M * vec4(VertexPosition,1.0)); 
   Normal = normalize(NormalMatrix * VertexNormal);
   gl_Position = P * V * M * vec4(VertexPosition,1.0);
}
