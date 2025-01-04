#version 330 core
out vec4 color;

uniform vec4 light_color;

void main()
{
    color = light_color;
}