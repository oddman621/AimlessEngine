#version 460 core

layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;
out vec4 vs_color;

vec4 positions[3] = vec4[](
    vec4(0.0, -0.5, 0.0, 1.0),
    vec4(0.5, 0.5, 0.0, 1.0),
    vec4(-0.5, 0.5, 0.0, 1.0)
);

void main(void)
{
    gl_Position = positions[gl_VertexID] + offset;
    vs_color = color;
}