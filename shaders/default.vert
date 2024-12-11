#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x * (1 + scale), aPos.y * (1 + scale), aPos.z * (1 + scale), 1.0);
   color = aColor;
}