// Seguindo o mesmo Princípio dados nas Aulas   
#version 330

// 1. Inputs
uniform vec3    color;
uniform float   gridStep;
uniform float   angle;

// São as mesmas variáveis que são enviadas pelo ficheiro vert
in Data {
  vec2 texCoord;
  vec3 normalVector;
  vec3 lightDirectionVector;
} DataIn;

// 2. Outputs
out vec4 colorOut; // Cor que Sai - Calculada na Função Main

/*
  * Function:  rotateMatrix
  * --------------------
  * Efetua uma Rotação Matriz consoante um Valor Ângulo
  *
  * angle: Valor em Graus do Ângulo
  *
  * returns: Matriz com a Rotação Efeutada
*/
mat2 rotateMatrix(float angle) {
  return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}
   	
/*
  * Function:  rotateMatrix
  * --------------------
  * Calcula Fator da Componente Difusa proveninente da Iluminação
  *
  * normalVector: Vetor da Direção da Normal
  * lightDirVector: Vetor da Direção da Luz
  *
  * returns: Matriz com a Rotação Efeutada
*/
float componDiffuse(vec3 normalVector, vec3 lightDirVector) {
  
  // Cálculo do Produto Escalar entre os 2 Ângulos (Normal e Luz)
  // Normalizar os Vetores
  float difuseAngle = dot(normalize(normalVector), normalize(lightDirVector));

  return max(0.0, -difuseAngle);
}

/*
  * Function:  dotsAndAntiAlising
  * --------------------
  * Trata dos Dots e do Filtro Anti-Alising para que as bordas da Grid fiquem mais (ou menos) lisas
  *
  * pixel: Pixel a Verificar
  * center: Centro do Círculo
  * radius: Raio do Círculo
  *
  * returns: Valor de Float referente ao Dot e seu Anti-Alising que se quer aplicar
*/
float dotsAndAntiAlising(vec2 pixel, vec2 center, float radius) {

  float radiusCircle = radius;
  float borderSize = 2.5; // Quanto maior o Border Size - mais Lisas as Bordas da Grid
  float distanceCircle = length(pixel-center);

  return 1.0 - smoothstep(radiusCircle-borderSize, radiusCircle+borderSize, distanceCircle);
}

// 3. Função Main
// Cálculo da Luz Difusa, Cordenadas, Grelha e Cor Final
void main() {

  // 1. Rotação da Matriz de Coordenadas
  vec2 pos = rotateMatrix(radians(angle)) * gl_FragCoord.xy;

  // 2. Cálculo Componente Diffuse Light
  float diffuseIntensity = componDiffuse(DataIn.normalVector, DataIn.lightDirectionVector);

  // 3. Definir a Grid Position
  vec2 gridPosition = mod(pos, gridStep);

  // 4. Calcular a Cor Final
  vec3 finalColor = color;
  // Último Parâmetro é o Raio - Quanto menor, mais espaçadas os dots
  finalColor -= dotsAndAntiAlising(gridPosition, vec2(gridStep / 2.0), 0.7 * gridStep * pow(1.0 - diffuseIntensity, 2.0));
  finalColor = clamp(finalColor, 0.05, 1.0); // limita finalColor entre 0.05 e 1.0
  
  colorOut = vec4(finalColor, 1.0);
}
