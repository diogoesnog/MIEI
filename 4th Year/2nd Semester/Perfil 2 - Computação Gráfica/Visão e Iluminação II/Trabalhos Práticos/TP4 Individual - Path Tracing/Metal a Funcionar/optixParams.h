#include "C:/Users/diogo/Documents/GitHub/nau-optix7/projects/optix test/launchParamsGlobal.h"
#include "C:/Users/diogo/Documents/GitHub/nau-optix7/projects/optix test/util.h"

struct GlobalParams
{
    float4                      lightPos;
    float4                      *accumBuffer;
    int                         shadowRays;
    float                       gamma;
    float                       lightScale;

    // Parâmetros usados para o Metal
    float                       glossiness; // Grau do Brilho em si
    int                         glossyRays; // Quantidade de Raios Brilhantes
};


struct LaunchParams
{
    Frame                       frame;
    Camera                      camera;
    OptixTraversableHandle      traversable;

    GlobalParams                *global;
};


