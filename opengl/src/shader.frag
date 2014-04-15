#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform float mixVal;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
	vec4 texColor = mix(texture(texKitten, Texcoord),
						 texture(texPuppy, Texcoord), mixVal);
    outColor = vec4(Color, 1.0) * texColor;
}