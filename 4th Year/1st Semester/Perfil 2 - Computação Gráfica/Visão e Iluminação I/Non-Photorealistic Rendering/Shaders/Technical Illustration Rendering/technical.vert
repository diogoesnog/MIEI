#version 330

uniform	mat4 m_pvm;     // matrix projection view model
uniform	mat4 m_vm;      // matix view model
uniform	mat4 m_view;    // matrix view
uniform	mat3 m_normal;  // matrix normal

uniform	vec4 l_dir;	   // global space

in vec4 position;	// local space
in vec3 normal;		// local space

// the data to be sent to the fragment shader
out Data {
    vec4 eye;
    vec3 normal;
    vec3 l_dir;
} DataOut;

void main () {
    DataOut.normal = m_normal * normal;
    DataOut.eye = -(m_vm * position);

	// transform light to camera space
    DataOut.l_dir = vec3(m_view * -l_dir);

    gl_Position = m_pvm * position;	
}
