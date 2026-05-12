#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

uniform mat4 projection;

out vec3 Color;
out vec2 UV;

void main()
{
 gl_Position = projection * vec4(aPos, 1);
 Color = aColor;
 UV = aUV;
}