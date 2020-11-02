#version 330

in vec4 position; 
in vec3 normal;

uniform vec4 diffuse;
uniform vec4 ambient;

uniform mat4 m_pvm;
uniform mat4 m_view;
uniform mat3 m_normal;

uniform vec4 l_dir;

out float intensidade;
out vec4 cor;




void main(){

vec3 l = normalize(vec3(m_view * -l_dir));
vec3 n = normalize(m_normal*normal);


intensidade=max(0,dot(n,l));



gl_Position = m_pvm * position;

}