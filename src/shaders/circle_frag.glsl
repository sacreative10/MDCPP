#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform vec3 uColor;
uniform float uThickness;
uniform bool uFill;

float fade = 0.005;

void main()
{
    // map uv to [-1, 1]
    vec2 uv2 = uv * 2.0 - 1.0;

    float thickness = uThickness;
    if (uFill) {
       thickness = 1;
    }


    if (length(uv2) > 1.0) {
        discard;
    }
    float d = 1.0 - length(uv2);

    vec3 col = vec3(smoothstep(0.f, fade, d));
    col *= vec3(smoothstep(thickness + fade, thickness, d));

    FragColor = vec4(col, 1.0);
    FragColor.rgb *= uColor;
}