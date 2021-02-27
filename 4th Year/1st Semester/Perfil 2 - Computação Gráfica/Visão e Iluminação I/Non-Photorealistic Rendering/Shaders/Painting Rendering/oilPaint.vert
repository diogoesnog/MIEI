#version 430 core

// Higher Precision: highp -> 16-bit, floating point range: -2^62 to 2^62, integer range: -2^16 to 2^16
// Espaço Local
in highp vec2 texCoord0;
in highp vec4 position;

uniform highp mat4  m_pvm;

smooth out highp vec2 texCoord;

void main() {
    // Mapeamento da Textura
    texCoord = texCoord0; // Camera 
    gl_Position = m_pvm * position; // Clip Space

}