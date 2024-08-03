// Fragment shader
#version 460 core

out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D uTexture;
uniform float lighting;


void main()
{
    vec4 texCoord = vec4(texture(uTexture, v_TexCoord));
    FragColor = texCoord;
    FragColor = FragColor * lighting;
    FragColor.a = 0.7;
}