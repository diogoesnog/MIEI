// Seguindo o mesmo Princípio dados nas Aulas   
#version 330

// 1. Inputs
// Só posso fazer transformações/operações entre Vetores se tiverem no mesmo Espaço
in vec4 position; // Espaço Local
in vec3 normal;	// Espaço Local
in vec2 texCoord0;

uniform	mat4 matrixPVM;
uniform	mat4 matrixVIEWMODEL;
uniform	mat4 matrixVIEW; // Matriz VIEW para que possamos trabalhar no Espaço Câmara
uniform	mat3 matrixNORMAL;

uniform	vec4 lightDirection; // Espaço Global

// 2. Outputs
// Aquilo que é Enviado para o Shader Frag
out Data {
  vec4 eyeVector;
  vec2 texCoord;
  vec3 normalVector;
  vec3 lightDirectionVector;
} DataOut;

// 3. Função Main
// Seguir a Mesma Ideia das Aulas
void main() {

  // Tem de Ficar em Primeiro
  // Caso contrário Imagem fica Preta
  DataOut.texCoord = texCoord0;

  // Colocar os Vetores no Mesmo Espaço e Normalizados
  // Ficam no Espaço Câmara
  DataOut.eyeVector = -(matrixVIEWMODEL * position);
  DataOut.normalVector = normalize(matrixNORMAL*normal);
  // Necessário Usar o vec3 porque matrixVIEW é uma mat4
  DataOut.lightDirectionVector = normalize(vec3(matrixVIEW * -lightDirection));

  gl_Position = matrixPVM*position;	
}
