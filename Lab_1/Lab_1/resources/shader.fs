#version 330 core

#define MAX_LIGHTS_NUM 8

struct Light
{
    vec4 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} material;

in VS_OUT
{
    vec3 position;
    vec3 normal;
} vertex;

out vec4 fragmentColor;

uniform vec3 viewPosition;

uniform int lightsNumber;
uniform Light lights[MAX_LIGHTS_NUM];

vec3 calculatePointLight(Light light, Material material, vec3 vertexPosition, vec3 vertexNormal, vec3 viewDirection);

void main()
{
    vec3 viewDirection = normalize(viewPosition - vertex.position);

    vec3 result = vec3(0.0f);
    for (int i = 0; i < lightsNumber; ++i)
    {
        result += calculatePointLight(lights[i], material, vertex.position, vertex.normal, viewDirection);
    }

    fragmentColor = vec4(result, 1.0f);
}

vec3 calculatePointLight(Light light, Material material, vec3 vertexPosition, vec3 vertexNormal, vec3 viewDirection)
{
    vec3 ambient = light.ambient * material.ambient;
    
    vec3 lightDirection = normalize(vec3(light.position) - vertexPosition);
    float diffuseFactor = max(dot(normalize(vertexNormal), lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * (diffuseFactor * material.diffuse);

    vec3 reflectDirection = reflect(-lightDirection, normalize(vertexNormal));
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * (specularFactor * material.specular);

    return ambient + diffuse + specular;
}
