#version 460 core

precision highp float;

#define GLOBAL_AMBIENT_STRENGTH 0.1

in vec3 fragColor;
in vec2 fragUv;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

struct Material
{
    sampler2D ambientMap;
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D opacityMap;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float opacity;

    float shininess;
};

uniform Material material;
uniform vec3 lightDirection;

vec4 selectBetween(sampler2D map, vec3 color);
vec3 getDiffuseSpecularImpact(vec3 lightDir, vec3 normal, vec3 viewDir);

void main()
{
    // Fragment's normal in view space
    vec3 normal = normalize(fragNormal);
    // Viewing direction
    vec3 viewDir = normalize(-fragPos);

    // Default fragment color
    vec3 result = selectBetween(material.diffuseMap, material.diffuseColor).xyz;
    
    // Ambient shading is global and do not come from all lighting sources
    vec3 shading = GLOBAL_AMBIENT_STRENGTH * selectBetween(material.ambientMap, material.ambientColor).xyz;
    shading += getDiffuseSpecularImpact(normalize(-lightDirection), normal, viewDir);

    FragColor = vec4(result * shading, 1.0);

    // Applying fragment's opacity. It comes either from texture map or set universally for material
    FragColor.a = max(texture(material.opacityMap, fragUv).r, material.opacity);
}

// Define what color to use between texture and its fallback color
// (if texture is present - color should be nulled)
vec4 selectBetween(sampler2D map, vec3 color)
{
    return mix(texture(map, fragUv), vec4(color, 0.0), float(length(color) > 0.0));
}

// Returns a vector of Phong diffuse and specular shading impact
vec3 getDiffuseSpecularImpact(vec3 lightDir, vec3 normal, vec3 viewDir)
{
    // Diffuse calculation
    vec3 diffuse = vec3(max(dot(normal, lightDir), 0.0));

    // Specular calculation
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 2.0));
    vec3 specColor = selectBetween(material.specularMap, material.specularColor).xyz;
    vec3 specular = specColor.xyz * spec;
    
    // wait what the fuck is with types here
    // TODO inspect
    return (diffuse + specular);
}