#version 330 core

in vec3 Color;
in vec2 UV;

out vec4 FragColor;

uniform float borderSize;
uniform vec3 borderColor;
uniform int shapeType;

void main()
{
    if(shapeType == 0)
    {
  // triangle (barycentric)
          float edge = min(min(UV.x, UV.y), 1.0 - UV.x - UV.y);

        if(edge < borderSize)
            FragColor = vec4(borderColor, 1.0);
        else
            FragColor = vec4(Color, 1.0);
    }
    else if(shapeType == 1)
    {
           // rectangle (UV)
        float edge = min(min(UV.x, 1.0 - UV.x),
                         min(UV.y, 1.0 - UV.y));

        if(edge < borderSize)
            FragColor = vec4(borderColor, 1.0);
        else
            FragColor = vec4(Color, 1.0);
    
    }
    else
    {
      // circle (radial UV assumed centered)
        float dist = length(UV);

        if(dist > 1.0 - borderSize)
            FragColor = vec4(borderColor, 1.0);
        else
            FragColor = vec4(Color, 1.0);
    }
}