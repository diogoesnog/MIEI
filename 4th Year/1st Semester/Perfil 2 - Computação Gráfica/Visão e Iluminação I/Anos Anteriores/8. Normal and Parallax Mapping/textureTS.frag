#version 330

uniform sampler2D tex,normalMap;

in Data {
	vec2 texCoord;
	vec3 l_dir, eye;
} DataIn;

out vec4 colorOut;

void main() {


	vec3 n = vec3(texture(normalMap, DataIn.texCoord) * 2 - 1);
	

	
	float intensity = max(dot(n,normalize(-DataIn.l_dir)), 0.0);

	vec4 diffuse = texture(tex, DataIn.texCoord);
	colorOut = (intensity + 0.15) * vec4(0.8);

	

}
