#version 330

uniform sampler2D texDay, texNight, texSpec, texClouds;
uniform float shininess = 128;

in Data {
	vec4 eye;
	vec2 texCoord;
	vec3 normal;
	vec3 l_dir;
} DataIn;

out vec4 colorOut;

void main() {
	// get texture color
	vec4 eColor = texture(texDay, DataIn.texCoord);

	// set the specular term to black
	vec4 spec = vec4(0.0);

	vec4 colorDay, colorNight;
	//float intSpec, posInt = 0.0;

	vec3 n = normalize(DataIn.normal);
	vec3 e = normalize(vec3(DataIn.eye));

	float intensity = max(dot(n,DataIn.l_dir), 0.0);

	// if the vertex is lit compute the specular color
	if (intensity > 0.0) {
		// compute the half vector
		vec3 h = normalize(DataIn.l_dir + e);	
		// compute the specular intensity
		float intSpec = max(dot(h,n), 0.0);
		// compute the specular term into spec
		spec = vec4(1) * pow(intSpec,shininess);
	}

	float gloss = texture(texSpec, DataIn.texCoord).r;
	float clouds = texture(texClouds, DataIn.texCoord).r;

	vec4 cD = texture(texDay, DataIn.texCoord);
	vec4 cN = texture(texNight, DataIn.texCoord);
	
	//colorDay = intensity * cD + gloss * spec;
	//colorNight = cN;
	
	colorDay = clouds * intensity + (1-clouds) * intensity * cD + gloss * spec;
	colorNight = (1-clouds) * texture(texNight, DataIn.texCoord);

	vec4 color;
	if (intensity > 0.1)
		color = colorDay;
	else if (intensity > 0.0) {
		// we are assuming a fixed intensity of 0.1 for mixing purposes
		// color = mix(cN, 0.1f * cD + gloss * spec, intensity* 10.0f);
		color = mix(colorNight, clouds * 0.1f + (1-clouds) * 0.1f * cD + gloss * spec, intensity * 10.0f);
	}
	else {
		color = colorNight;
	}
	
	colorOut = color;
}
