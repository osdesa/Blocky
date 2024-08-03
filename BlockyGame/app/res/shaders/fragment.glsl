// Fragment shader
#version 460 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform float waterEffect;
uniform float lighting;
uniform sampler2D uTexture;

void main()
{
    vec4 texCoord = vec4(texture(uTexture, v_TexCoord));
    FragColor = texCoord;
    FragColor = FragColor * lighting;
    FragColor.r = FragColor.r * waterEffect;
    FragColor.g = FragColor.g * waterEffect;
    FragColor.b = FragColor.b * (1 / waterEffect);
    FragColor.a = 1;
}