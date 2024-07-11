#version 330 core

layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 textCoords;

uniform mat4 textPosition;

void main()
{
    gl_Position = textPosition * vec4(vertex.xy, 0.0, 1.0);
    textCoords = vertex.zw;
}