#version 330 core
in vec3 Color;
in vec2 UV;
in float shapeType;

out vec4 FragColor;

uniform sampler2D textTexture;

void main()
{
    vec3 borderColor = vec3(0.0, 0.0, 0.0);

    if(shapeType == -1)
    {
    float alpha = texture(textTexture, UV).r;
    FragColor = vec4(Color,alpha);
    }
  else if(shapeType == 0)
    {
  // triangle (barycentric)
          float edge = min(min(UV.x, UV.y), 1.0 - UV.x - UV.y);

           float borderSize = fwidth(edge) * 2.0;

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

        float borderSize = fwidth(edge) * 2.0;

        if(edge < borderSize)
            FragColor = vec4(borderColor, 1.0);
        else
            FragColor = vec4(Color, 1.0);
    
    } 
    else if (shapeType == 2)
    {
      // circle (radial UV assumed centered)
        float dist = length(UV * 2.0 - 1.0);

         float edge = 1 - dist;
         float borderSize = fwidth(edge) * 2.0;


        if(edge < borderSize)
            FragColor = vec4(borderColor, 1.0);
        else
            FragColor = vec4(Color, 1.0);
    }
}