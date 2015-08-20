#version 430

in vec3 fs_pos;
in vec3 fs_normal;
in vec2 fs_tex;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float specularPower;

layout (location = 0) out vec3 pos;
layout (location = 1) out vec3 diff;
layout (location = 2) out vec3 normal;
layout (location = 3) out vec2 specular;

void main(void){
    pos = fs_pos;
    diff = texture(texture_diffuse1, fs_tex).xyz;
    normal = normalize(fs_normal);
    specular = vec2(specularPower, texture(texture_specular1, fs_tex).x);
}