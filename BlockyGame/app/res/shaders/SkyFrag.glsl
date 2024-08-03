#version 460

uniform sampler2D uTexture;

in vec2 v_TexCoord;
out vec4 FragColour;

void main()
{
	vec4 texCoord = vec4(texture(uTexture, v_TexCoord));
    FragColour = texCoord;
}