#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out VS_OUT
{
	vec3 position;
	vec3 normal;
} vertex;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertex.position = vec3(world * vec4(vertexPosition, 1.0f));
	vertex.normal = mat3(transpose(inverse(world))) * vertexNormal;

	gl_Position = projection * view * vec4(vertex.position, 1.0f);
}