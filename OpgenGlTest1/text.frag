#version 330 core

in vec2 UV;
in vec3 Color;

uniform sampler2D textTexture;

out vec4 FragColor;

void main() {
   float alpha = texture(textTexture, UV).r;
   FragColor = vec4(Color, alpha);
}