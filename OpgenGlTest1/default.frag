#version 330 core

in vec4 Color;
in vec2 localPos;
in float shapeType;
in float Radius;

out vec4 FragColor;

uniform sampler2D textTexture;

vec3 borderColor = vec3(0.0);
float t = 0.005;

void DrawTriangle();
void DrawRectangle();
void DrawCircle();
void DrawText();

float RoundedRectSDF(vec2 p, vec2 b, float r)
{
    vec2 d = abs(p) - (b - vec2(r));
    return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - r;
}

void main()
{
    if(shapeType == 0)
    {
        DrawText();
    }
    else if(shapeType == 1)
    {
        DrawTriangle();
    }
    else if(shapeType == 2)
    {
        DrawRectangle();
    }
    else if(shapeType == 3)
    {
        DrawCircle();
    }
}

void DrawText(){
   float alpha = texture(textTexture, localPos).a;
   FragColor = vec4(Color.xyz, alpha);
}

void DrawTriangle(){
}

void DrawRectangle(){
   FragColor = Color;
}

void DrawCircle(){
     
}