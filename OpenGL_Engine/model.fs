#version 430 core

in vec2 fs_tex;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    color = vec4(texture(texture_diffuse1, fs_tex));
}