#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 tex_coord;

in vec3 normal;
in vec3 current_position;

uniform sampler2D tex0;
uniform vec4 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

void main()
{
    float ambient = 0.20f;

    vec3 normalized_normal = normalize(normal);
    vec3 light_direction = normalize(light_position - current_position);

    float specular_light = 0.50f;
    vec3 view_direction = normalize(camera_position - current_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float specular_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), 8);
    float specular = specular_amount * specular_light;

    float diffuse = max(dot(normalized_normal, light_direction), 0.0f);
    FragColor = texture(tex0, tex_coord) * light_color * (diffuse + ambient + specular);
}