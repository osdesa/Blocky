#version 460 core

out vec4 FragColor;

uniform vec3 backColour;

void main()
{
    FragColor = vec4(backColour, 1.0);
}