#version 460 core

vec4 positions[3] = vec4[](
    vec4(0.0, -0.5, 0.0, 1.0),
    vec4(0.5, 0.5, 0.0, 1.0),
    vec4(-0.5, 0.5, 0.0, 1.0)
);

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

out vec3 fragColor;

void main(void)
{
    gl_Position = positions[gl_VertexID];
    fragColor = colors[gl_VertexID];
}