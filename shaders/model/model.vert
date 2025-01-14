#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 current_position;
out vec3 normal;
out vec2 tex_coord;

uniform mat4 camera_matrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    current_position = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
    gl_Position = camera_matrix * vec4(current_position, 1.0f);
    normal = mat3(transpose(inverse(model))) * aNormal;
    tex_coord = aTex;
}