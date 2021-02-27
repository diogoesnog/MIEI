// Seguindo o mesmo Princípio dados nas Aulas   
#version 330

// 1. Inputs
// Variável Global levelsToon que será usada no GUI do Composer
// Várias Opções para o Nível do Filtro Toon
uniform int levelsToon;

// São as mesmas variáveis que são enviadas pelo ficheiro vert
in Data {
  vec4 eyeVector;
  vec2 texCoord;
  vec3 normalVector;
  vec3 lightDirectionVector;
} DataIn;

// 2. Outputs
out vec4 colorOut; // Cor que Sai - Calculada na Função Main

float componDiffuse(vec3 normalVector, vec3 lightDirVector) {
  
  // Cálculo do Produto Escalar entre os 2 Ângulos (Normal e Luz)
  // Normalizar os Vetores
  float difuseAngle = dot(normalize(normalVector), normalize(lightDirVector));

  return max(difuseAngle, 0.0);
}

// 3. Função Main
void main() {
  
  // 1. Normalização dos Vetores Input
  // Serão Usados para O Produto Escalar do Vetor Normal e da View
  vec3 normalizeNormalVector = normalize(DataIn.normalVector);
  vec3 normalizeEyeVector = normalize(vec3(DataIn.eyeVector));
	
  float scalarProduct = dot(normalizeEyeVector, normalizeNormalVector);

  // 2. Cálculo Componente Diffuse Light
  // A Intensidade calculada será usada para os Vários Toon Levels
  float diffuseIntensity = componDiffuse(DataIn.normalVector, DataIn.lightDirectionVector);

  // 3. Definir Comportamento Vários Níveis de Toon
  // O Valor da Cor de Saída será definido por esta Escolha
  switch(levelsToon) {
    // Fatias de 30%
    case 1:
      if (diffuseIntensity>0.90)
        colorOut = vec4(0.0, 0.0, 1.0, 1.0);
      else if (diffuseIntensity>0.60)
        colorOut = vec4(0.0, 0.0, 0.65, 1.0);
      else if (diffuseIntensity>0.30)
        colorOut = vec4(0, 0.0, 0.45, 1.0);
      else
        colorOut = vec4(0, 0.0, 0.25, 1.0);
      break;
    case 2:
      if (diffuseIntensity>0.60)
        colorOut = vec4(0.0, 0.0, 0.9, 1.0);
      else if (diffuseIntensity>0.30)
        colorOut = vec4(0.0, 0.0, 0.6, 1.0);
      else
        colorOut = vec4(0.0, 0.0, 0.3, 1.0);
      break;
    case 3:
      if (diffuseIntensity>0.50)
        colorOut = vec4(0.0, 0.0, 0.8, 1.0);
      else
        colorOut = vec4(0.0, 0.0, 0.4, 1.0);
      break;
    case 4:
      colorOut = diffuseIntensity*vec4(0.0, 0.0, 1.0, 1.0);
      break;
  }
}
