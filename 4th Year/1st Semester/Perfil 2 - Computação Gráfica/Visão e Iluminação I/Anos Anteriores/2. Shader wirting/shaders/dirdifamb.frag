#version 330

out vec4 corFinal;

uniform vec4 diffuse;
uniform vec4 ambient;

in float intensidade;

void main(){

//corFinal = ambient + diffuse * intensidade ;
corFinal = max(ambient, diffuse*intensidade);
}