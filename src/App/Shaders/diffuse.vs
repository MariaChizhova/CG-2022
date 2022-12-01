#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out mat3 NormalMat;
out float Ambient;
out float Diffuse;
out vec3 Specular;

void main() {
    vec3 newPos = pos;
    newPos.y += sin(dot(newPos.xz, vec2(2*time)) + time * 30) * 0.4;

    vec3 posPlusTangent = pos + tangent * 0.01;
    vec3 posPlusBitangent = pos + bitangent * 0.01;

    posPlusTangent.y += sin(dot(posPlusTangent.xz, vec2(2*time)) + time * 30) * 0.4;
    posPlusBitangent.y += sin(dot(posPlusBitangent.xz, vec2(2*time))  + time * 30) * 0.4;

    vec3 newTangent = posPlusTangent - newPos;
    vec3 newBitangent = posPlusBitangent - newPos;
    vec3 normalized = normalize(cross(newBitangent, newTangent));

    Normal = normalized;
    TexCoords = texCoords;
    FragPos = vec3(model * vec4(newPos, 1.0));
    NormalMat = inverse(transpose(mat3(model)));

    normalized = -NormalMat * normalize(normalized);
    float ambient = 0.1;
    Ambient = ambient;
    vec3 lightDir = normalize(lightPos - FragPos);
    Diffuse = max(dot(lightDir, normalized), 0.0);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalized);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    Specular = vec3(0.5) * spec;

	gl_Position = projection * view * model * vec4(newPos.xyz, 1.0);
}
