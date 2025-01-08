#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 color;
in vec2 tex_coord;

in vec3 normal;
in vec3 current_position;

uniform sampler2D tex0;
uniform vec3 camera_position;

uniform Light light;
uniform Material material;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 normalized_normal = normalize(normal);
    vec3 light_direction = normalize(light.position - current_position);
    float diffuse_amount = max(dot(normalized_normal, light_direction), 0.0f);
    vec3 diffuse = light.diffuse * (diffuse_amount * material.diffuse);

    vec3 view_direction = normalize(camera_position - current_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float specular_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), material.shininess);
    vec3 specular = light.specular * (specular_amount * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = texture(tex0, tex_coord) * vec4(result, 1.0f);
}