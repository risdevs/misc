#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform float mixVal;
uniform float time;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
	vec4 colKitten = texture(texKitten, Texcoord);
	vec4 colPuppy = texture(texPuppy, Texcoord);
    outColor = mix(colKitten, colPuppy, mixVal);
}