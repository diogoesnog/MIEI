#version 330

in Data {
	vec4 eye;
	vec3 normal;
	vec3 l_dir;
} DataIn;

out vec4 colorOut;

void main() {
	// normalize the inputs
	vec3 normal = normalize( DataIn.normal);
	float intensity = max(dot(normal, normalize(DataIn.l_dir)), 0.0);
	vec3 eye = normalize(vec3(DataIn.eye));

	vec4 k_blue = vec4(0,0,0.6,1);
	vec4 k_yellow = vec4(0.6,0.6,0,1);	
	vec4 aux = vec4(1,1,1,1);

	float alpha = 0.4;
	float beta = 0.6;

	vec4 k_cool = k_blue + aux*alpha;
	vec4 k_warm = k_yellow + aux*beta; 
	
	float edge = dot(eye, normal);

	if (edge < 0.3) {
		colorOut = vec4(0.0,0.0,0.0,1.0);
    }
	else {
		colorOut = mix(k_cool, k_warm, intensity);
    }
}
