#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec4 shapeState;
uniform float xTransform;
uniform float yTransform;

void main()
{
    gl_Position = vec4((aPos.x + xTransform), (aPos.y + yTransform), aPos.z, 1.0);
}