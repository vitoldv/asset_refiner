#version 460 core

#define MAX_LIGHT_SOURCES 10

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aUv;

out vec3 fragColor;
out vec2 fragUv;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    fragColor = aColor;
    fragUv = aUv;
    fragNormal = normalMatrix * aNormal;
    // view space position of a fragment
    fragPos = vec3(view * model * vec4(aPos, 1.0));
}