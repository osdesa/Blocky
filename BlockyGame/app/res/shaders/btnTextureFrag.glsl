// Fragment shader
#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D uTexture;

void main()
{
    vec4 texCoord = vec4(texture(uTexture, vTexCoords));
    FragColor = texCoord;
}