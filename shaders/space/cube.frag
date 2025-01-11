#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 normal;
in vec2 tex_coord;
in vec3 current_position;

uniform sampler2D tex0;
uniform vec3 camera_position;

uniform Light light;
uniform Material material;

void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse, tex_coord).rgb;
    float distance = length(light.position - current_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light.position - current_position);
    float diff = max(dot(norm, light_direction), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tex_coord).rgb;

    vec3 view_direction = normalize(camera_position - current_position);
    vec3 reflection_direction = reflect(-light_direction, norm);
    float spec = pow(max(dot(view_direction, reflection_direction), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, tex_coord).rgb;

    vec3 result = attenuation * (ambient + diffuse + specular);
    FragColor = texture(tex0, tex_coord) * vec4(result, 1.0f);
}