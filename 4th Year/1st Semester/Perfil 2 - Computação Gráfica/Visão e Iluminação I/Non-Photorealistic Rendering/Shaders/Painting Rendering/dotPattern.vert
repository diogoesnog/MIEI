#version 430 core

layout (location=0) in  vec3 position;
layout (location=1) in  vec3 normal;
layout (location=2) in  vec2 uv;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_pro;

out vec3 cOut;
out vec3 pOut;
out vec3 nOut;
out vec2 uvOut;

void main() {

	gl_Position= m_pro * m_view * m_model * vec4(position.x*0.25, position.y*0.25, position.z*0.25, 1.0);

	vec4 temp= m_view * vec4(position, 1.0f); 
	pOut= vec3(temp.x, temp.y, temp.z);
    
	temp= transpose(inverse(m_view)) * vec4(normal, 1.0f);
	nOut= vec3(temp.x, temp.y, temp.z);
   
    cOut = vec3(0.5, 0.5, 0.5);
	uvOut=uv;
}