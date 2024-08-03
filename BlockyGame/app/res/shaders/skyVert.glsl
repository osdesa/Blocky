// Vertex Shader
#version 460 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * (u_Model * vec4(aPosition, 1.0));
	v_TexCoord = aTexCoords;
}