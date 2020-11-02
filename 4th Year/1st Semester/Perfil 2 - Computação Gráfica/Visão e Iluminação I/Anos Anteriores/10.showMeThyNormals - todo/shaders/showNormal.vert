#version 420

in vec4 position;
in vec3 normal;

out Data {
	vec3 normal;
} DataOut;

void main()
{
	DataOut.normal = normal;
	gl_Position = position ;
} 
