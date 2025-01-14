#version 330 core
out vec4 FragColor;

struct Light
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 current_position;
in vec3 normal;
in vec2 tex_coord;

uniform vec3 camera_position;
uniform Light light;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
float shininess;

void main()
{
    vec3 ambient = light.ambient * texture(diffuse0, tex_coord).rgb;

    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(-light.direction);
    float diff = max(dot(norm, light_direction), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(diffuse0, tex_coord).rgb;

    vec3 view_direction = normalize(camera_position - current_position);
    vec3 reflection_direction = reflect(-light_direction, norm);
    float spec = pow(max(dot(view_direction, reflection_direction), 0.0f), shininess);
    vec3 specular = light.specular * spec * texture(specular0, tex_coord).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = texture(diffuse0, tex_coord) * vec4(result, 1.0f);
}