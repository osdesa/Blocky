#version 460 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

out vec2 vTexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex, 0, 1.0);
    vTexCoords = texCoords;
}