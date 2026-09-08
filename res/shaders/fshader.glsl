#version 440 core

in vec2 fUV;
in vec3 fNormal;
in vec3 fFragPos;

uniform sampler2D tex0;
uniform vec3 fViewPos;

out vec4 fColor;

#define LIGHT vec3(1.0, 1.0, 1.0)
#define LIGHT_DIRECTION vec3(-0.433, 0.766, -0.469)
#define LIGHT_POSITION vec3(2.0, 2.0, 2.0)

float ambientStrength = 0.1f;
float specularStrength = 0.5f;

vec4 calculateAmbient() {
    vec3 ambient = ambientStrength * LIGHT;
    return vec4(ambient, 1.0);
}

vec4 calculateDiffuse() {
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(LIGHT_POSITION - fFragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    return vec4(diff * LIGHT, 1.0);
}

vec4 calculateSpecular() {
    vec3 lightDir = normalize(LIGHT_POSITION - fFragPos);
    vec3 norm = normalize(fNormal);

    vec3 viewDir = normalize(fViewPos - fFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    return vec4(specularStrength * spec * LIGHT, 1.0);
}

void main() {
    vec4 ambient = calculateAmbient();
    vec4 diffuse = calculateDiffuse();
    vec4 specular = calculateSpecular();

    vec4 objectColor = texture(tex0, fUV);

    fColor = objectColor * (ambient + diffuse + specular);
}