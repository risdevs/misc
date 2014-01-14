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

	if(Texcoord.y < 0.5)
		outColor = texture(texKitten, Texcoord);
	else
		outColor = texture(texKitten, vec2(Texcoord.x + sin(Texcoord.y * 60.0 + time * 100.0) / 30.0, Texcoord.y)) * vec4(0.7, 0.7, 1.0, 1.0);



/*
	if(Texcoord.y < 0.5)
		outColor = texture(texKitten, Texcoord);
	else
		outColor = texture(texKitten, vec2(Texcoord.x, 1.0 - Texcoord.y));
*/
/*
	vec4 colKitten = texture(texKitten, Texcoord);
	vec4 colPuppy = texture(texPuppy, Texcoord);
    outColor = mix(colKitten, colPuppy, mixVal);
*/
}