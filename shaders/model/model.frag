#version 330 core
out vec4 FragColor;

struct Light
{
    vec3 direction;
    float strength;

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
uniform float shininess;

float near = 0.1;
float far = 100.0;

void main()
{
    vec3 ambient = light.ambient * texture(diffuse0, tex_coord).rgb;

    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(-light.direction);
    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(diffuse0, tex_coord).rgb;

    vec3 view_direction = normalize(camera_position - current_position);
    vec3 reflect_direction = reflect(-light_direction, norm);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), shininess);
    vec3 specular = light.specular * spec * texture(specular0, tex_coord).rgb;

    vec3 light = (ambient + diffuse + specular) * light.strength;
    float depth = 1 - (2.0 * near * far) / (far + near - (gl_FragCoord.z * 2.0 - 1.0) * (far - near)) / far;
    FragColor = texture(diffuse0, tex_coord) * vec4(light, 1.0) * vec4(vec3(depth), 1.0);
}