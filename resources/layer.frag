#version 330 core
uniform float time;
uniform vec2 resolution;
uniform sampler2D tex0;

in vec2 uv;
out vec4 FragColor;

void main()
{
    vec4 texColor = texture(tex0, uv + vec2(sin(time + uv.x * 30.0)*0.25, cos(time + uv.y * 20.0)*0.25));
    //FragColor = vec4(sin(time)*0.5+0.5, 1.0, cos(uv.y*50.0), 1.0);
    FragColor = texColor;
}