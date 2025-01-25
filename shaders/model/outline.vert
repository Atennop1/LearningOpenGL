#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 camera_matrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform float outline_thickness;

void main()
{
    vec3 current_position = vec3(model * translation * rotation * scale * vec4(aPos + aNormal * outline_thickness, 1.0f));
    gl_Position = camera_matrix * vec4(current_position, 1.0f);
}