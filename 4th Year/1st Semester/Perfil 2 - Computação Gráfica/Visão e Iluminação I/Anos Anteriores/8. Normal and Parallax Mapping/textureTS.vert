#version 330

uniform	mat4 m_pvm;
uniform	mat4 m_viewModel;
uniform	mat4 m_view;
uniform	mat3 m_normal;

uniform	vec3 l_dir;	// camera space

in vec4 position;	// local space
in vec3 normal;		// local space
in vec3 tangent;	// local space
in vec2 texCoord0;

// the data to be sent to the fragment shader
out Data {
	vec2 texCoord;
	vec3 l_dir;
	vec3 eye;
} DataOut;

void main () {

	DataOut.texCoord = texCoord0;
	
	vec3 n = normalize(m_normal * normal);
	vec3 t = normalize(m_normal * tangent);
	vec3 b = normalize(cross(n,t));
	t = cross(b,n);
	
	mat3 tbn_inv = transpose(mat3(t,b,n));
	DataOut.eye = tbn_inv * (vec3(m_viewModel*(-position)));
	DataOut.l_dir = tbn_inv * (vec3(mat3(m_view) * l_dir));
	
	gl_Position = m_pvm * position;	
}