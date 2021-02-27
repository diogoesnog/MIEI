#version 430 core

smooth in highp vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform int option;
uniform int level;
uniform vec2 screenSize;
out vec4 cOut;

void main() {
    
    // Multiplica os niveis da pintura
    float levelSqr = float((level + 1) * (level + 1));
    vec3 color[4];
    vec3 colorSqr[4];
    vec3 texColor;

    for (int i = 0; i < 4; i++)
    {
        color[i] = vec3(0.0f);
        colorSqr[i] = vec3(0.0f);
    }

    for (int i = -level; i <= 0; i++)
    {
        for (int j = -level; j <= 0; j++)
        {
            if(option == 0)
            {
                // Retorna um texel (o valor cor da textura) para as coordenadas fornecidas
                texColor = texture2D(texture1, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 1)
            {
                texColor = texture2D(texture2, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 2)
            {
                texColor = texture2D(texture3, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else
            {
                texColor = texture2D(texture4, texCoord + vec2(j, i) / screenSize).rgb;
            }
            color[0] += texColor;
            colorSqr[0] += texColor * texColor;
        }
    }

    for (int i = -level; i <= 0; i++)
    {
        for (int j = 0; j <= level; j++)
        {
            if(option == 0)
            {
                texColor = texture2D(texture1, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 1)
            {
                texColor = texture2D(texture2, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 2)
            {
                texColor = texture2D(texture3, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else
            {
                texColor = texture2D(texture4, texCoord + vec2(j, i) / screenSize).rgb;
            }
            color[1] += texColor;
            colorSqr[1] += texColor * texColor;
        }
    }

    for (int i = 0; i <= level; i++)
    {
        for (int j = 0; j <= level; j++)
        {
            if(option == 0)
            {
                texColor = texture2D(texture1, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 1)
            {
                texColor = texture2D(texture2, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 2)
            {
                texColor = texture2D(texture3, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else
            {
                texColor = texture2D(texture4, texCoord + vec2(j, i) / screenSize).rgb;
            }
            color[2] += texColor;
            colorSqr[2] += texColor * texColor;
        }
    }

    for (int i = 0; i <= level; i++)
    {
        for (int j = -level; j <= 0; j++)
        {
            if(option == 0)
            {
                texColor = texture2D(texture1, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 1)
            {
                texColor = texture2D(texture2, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else if(option == 2)
            {
                texColor = texture2D(texture3, texCoord + vec2(j, i) / screenSize).rgb;
            }
            else
            {
                texColor = texture2D(texture4, texCoord + vec2(j, i) / screenSize).rgb;
            }
            color[3] += texColor;
            colorSqr[3] += texColor * texColor;
        }
    }

    float minSigma = 4.71828;

    for (int i = 0; i < 4; i++)
    {
        // Divide o valor da variavel pelo valor de uma expressão e atribui o resultado
        color[i] /= levelSqr;
        colorSqr[i] = abs(colorSqr[i] / levelSqr - color[i] * color[i]);
        float sigma = colorSqr[i].r + colorSqr[i].g + colorSqr[i].b;

        if (sigma < minSigma)
        {
            minSigma = sigma;
            if(option == 0)
            {
                cOut = vec4(color[i], texture2D(texture1, texCoord).a);
            }
            else if(option == 1)
            {
                cOut = vec4(color[i], texture2D(texture2, texCoord).a);
            }
            else if(option == 2)
            {
                cOut = vec4(color[i], texture2D(texture3, texCoord).a);
            }
            else
            {
                cOut = vec4(color[i], texture2D(texture4, texCoord).a);
            }
        }
    }
}
