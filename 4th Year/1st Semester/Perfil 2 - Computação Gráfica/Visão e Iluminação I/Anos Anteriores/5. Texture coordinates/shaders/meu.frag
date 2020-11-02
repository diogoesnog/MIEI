#version 330

uniform sampler2D tex;
uniform float div;
vec4 cor1 = (234.0,173.0,234.0,1.0);
vec4 cor2 = (216.0,191.0,216.0,1.0);

in vec2 texCoord;


out vec4 ColorOut;

void main() {
    float c = texture(tex, texCoord)* div;
    colorOut = mix(cor1,cor2,c);
    vec2 t=texCoord;  
    float l=length(vec2(dFdx(t.s),dFdy(t.f)));
    float gap = l * 8;  

}