#version 430

in vec2 fs_tex;

out vec4 color;

uniform sampler2D ourTexture;

void main(void){
	color = texture(ourTexture, fs_tex);
}