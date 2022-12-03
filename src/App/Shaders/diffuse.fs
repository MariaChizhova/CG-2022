#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat3 NormalMat;
in float Ambient;
in float Diffuse;
in vec3 Specular;

out vec4 out_col;

uniform sampler2D texture_diffuse;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool isVertex;

void main() {
    vec3 color = texture(texture_diffuse, TexCoords).rgb;
    float ambient, diffuse;
    vec3 specular;

    if (isVertex) {
        ambient = Ambient;
        diffuse = Diffuse;
        specular = Specular;
    } else {
        ambient = 0.1;
        vec3 normalized = -NormalMat * normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        diffuse = max(dot(lightDir, normalized), 0.0);
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, normalized);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        specular = vec3(0.5) * spec;
    }
	out_col = vec4(ambient * color + diffuse * color + specular, 1.0);
}
