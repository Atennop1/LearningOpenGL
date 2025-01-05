#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 tex_coord;

out vec3 normal;
out vec3 current_position;

uniform mat4 camera_matrix;
uniform mat4 model_matrix;

void main()
{
    current_position = vec3(model_matrix * vec4(aPos, 1.0f));
    gl_Position = camera_matrix * vec4(current_position, 1.0f);
    normal = mat3(transpose(inverse(model_matrix))) * aNormal;
    tex_coord = aTex;
    color = aColor;
}