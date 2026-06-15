#version 330 core

// QUAD (per vertex)
layout(location = 0) in vec2 aPos;

// INSTANCE DATA (per shape)
layout(location = 1) in vec2 iPosition;
layout(location = 2) in vec2 iSize;
layout(location = 3) in vec4 iColor;
layout(location = 4) in float iRadius;
layout(location = 5) in float iRotation;
layout(location = 6) in float iType;

uniform mat4 projection;

out vec4 Color;
out float shapeType;
out float Radius;
out float Rotation;
out vec2 localPos;
out vec2 size;

void main()
{
    // move quad into shape space
   vec2 centeredPos = (aPos - vec2(0.5)) * iSize;

   float c = cos(iRotation);
   float s = sin(iRotation);

   vec2 rotated = vec2(
    centeredPos.x * c - centeredPos.y * s,
    centeredPos.x * s + centeredPos.y * c);

   vec2 worldPos = iPosition + rotated;

    gl_Position = projection * vec4(worldPos, 0.0, 1.0);

    // pass data to fragment shader
    Color = iColor;
    Radius = iRadius;
    shapeType = iType;
    size = iSize;
    Rotation = iRotation;

    // IMPORTANT: local position for SDF
    localPos = aPos;
}