#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform bool uWireframe;
uniform vec3 uColor;

void main() {
    if (uWireframe) {
        FragColor = vec4(uColor, 1.0);
    } else {
        FragColor = texture(uTexture, TexCoord);
    }
}

