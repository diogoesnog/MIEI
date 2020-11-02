#version 420
 
layout(triangles) in;
layout (line_strip, max_vertices=6) out;

uniform mat4 m_pvm;

in Data {
	vec3 normal;
} DataIn[3];


 void main()
{

}

