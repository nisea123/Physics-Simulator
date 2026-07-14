#version 330 core

in vec4 Color;
in vec2 localPos; // Can be used as midPoint for lines
in vec2 size; // Can be used as lenght and thickness for lines
in float shapeType;
in float Radius;
in float Rotation;

out vec4 FragColor;

uniform sampler2D textTexture;

vec3 borderColor = vec3(0.0);

const float TRIANGLE = 1.0;
const float RECTANGLE = 2.0;
const float CIRCLE = 3.0;
const float LINE = 4.0;
const float HEAD = 5.0;

void DrawTriangle();
void DrawRectangle();
void DrawCircle();
void DrawLine();
void DrawHead();

float RoundedRectSDF(vec2 p, vec2 b, float r)
{
    vec2 d = abs(p) - (b - vec2(r));
    return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - r;
}

void main()
{
  if(shapeType == TRIANGLE)
    {
        DrawTriangle();
    }
    else if(shapeType == RECTANGLE)
    {
        DrawRectangle();
    }
    else if(shapeType == CIRCLE)
    {
        DrawCircle();
    }
    else if(shapeType == LINE)
    {
        DrawLine();
    }
    else if(shapeType == HEAD) // Draws the tip of the arrow
    {
        DrawHead();
    }
}


void DrawTriangle(){
}

void DrawRectangle()
{
    vec2 p = (localPos - vec2(0.5)) * size;
    vec2 b = size * 0.5;

    float r = min(Radius, min(b.x, b.y));

    float d = RoundedRectSDF(p, b, r);

    float alpha = 1.0 - smoothstep(-fwidth(d), fwidth(d), d);

    FragColor = vec4(Color.rgb, Color.a * alpha);
}

void DrawCircle()
{
    vec2 p = (localPos - vec2(.5)) * Radius * 2;

    float r = Radius;

    float d = length(p) - r;

    float alpha = 1.0 - smoothstep(-fwidth(d), fwidth(d), d);

    FragColor = vec4(Color.rgb, Color.a * alpha);
}

void DrawLine()
{
   DrawRectangle();
}

float sdTriangleIsosceles( in vec2 p, in vec2 q )
{
    p.x = abs(p.x);
	vec2 a = p - q*clamp( dot(p,q)/dot(q,q), 0.0, 1.0 );
    vec2 b = p - q*vec2( clamp( p.x/q.x, 0.0, 1.0 ), 1.0 );
    float k = sign( q.y );
    float d = min(dot( a, a ),dot(b, b));
    float s = max( k*(p.x*q.y-p.y*q.x),k*(p.y-q.y)  );
	return sqrt(d)*sign(s);
}

void DrawHead()
{
    vec2 p = (localPos - vec2(0.5));
    p = vec2(p.y,-p.x);

    float d = sdTriangleIsosceles(p,vec2(1.0));

    float alpha = 1.0 - smoothstep(-fwidth(d), fwidth(d), d);

    FragColor = vec4(Color.rgb, Color.a * alpha);   
}