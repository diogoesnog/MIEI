#version 430 core

in vec3 cOut;
in vec3 pOut;
in vec3 nOut;
in vec2 uvOut;

uniform mat4 m_view;
uniform vec3 l_dir;  
uniform vec3 v_dir;
uniform vec3 l_color;
uniform sampler2D diffuseMap;

layout(location = 0) out vec4 gl_FragColor;

void main() {
	
	// Luz ambiente
	float amb= 1.0;
	vec3 ambient= amb*l_color;
	
	// Luz difusa
	float diff= 1.0; 
	vec3 norm= normalize(nOut);
	float diff= max(dot(norm, l_dir), 0.0); 	
	vec3 diffuse= diff * diff * l_color;  	
	
	// Iluminação Especular
	float spec = 1.0f;
	vec3 r_dir= reflect(-l_dir, norm);
	float spec= pow(max(dot(v_dir, r_dir), 0.0), 16);
	vec3 specular= spec * spec * l_color;
	
	float edge_thresh = 0.0; 
	float visiblity = dot(v_dir, norm);

	// Cor escura se o ponto for menor que 0.2, caso contrário mantem as cores
	float edge_detection = (visiblity > edge_thresh) ? 0 : 1;
		
	vec3 endTexture= texture(diffuseMap, uvOut).rgb;
	vec3 endColor;
	if(edge_detection ==0){
		endColor= (ambient + diffuse + specular) * cOut; 
	}else{
		float scale_origin=0.5;
		float scale = scale_origin + edge_thresh;
		float factor = (visiblity + scale_origin) / scale;
		endColor= factor * ambient * cOut; 
	}

	gl_FragColor= vec4(endColor, 1.0f);
}