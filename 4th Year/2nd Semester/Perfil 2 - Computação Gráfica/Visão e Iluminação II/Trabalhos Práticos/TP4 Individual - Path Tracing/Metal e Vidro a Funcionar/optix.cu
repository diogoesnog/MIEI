 // Our Launch Params
#include "optixParams.h"

extern "C"
{
    __constant__ LaunchParams optixLaunchParams;
}

// Ray Types
enum { RAIDANCE=0, SHADOW, RAY_TYPE_COUNT };

struct ShadowPRD
{
    float       shadowAtt;
    uint32_t    seed;
};

struct RadiancePRD
{
    // Quantidade de Luz Emitida
    float3      emitted;
    // Quantidade de Luz Emitida, Transmitida ou Recebida pela Superfície em si
    float3      radiance;
    // Quantidade da Redução da Itensidade da Luz
    float3      attenuation;
    // Origem e Direção da Luz
    float3      origin;
    float3      direction;

    // Float correspondente à Roulette
    float       roulette;

    bool        done;
    uint32_t    seed;
    int32_t     countEmitted;
};

// ############################################################
// Radiance Rays

// Acrescenta-se a ideia de Roleta Russa
// Cria-se uma verificação para as possíveis Texturas dos cenários em Teste
extern "C" __global__ void __closesthit__radiance() 
{
    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  

    RadiancePRD &prd = *(RadiancePRD *)getPRD<RadiancePRD>();

    // Recuperar Id Primitivo e Índices
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // Obter Barycentric Coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    // Compute normal
    const float4 n
        = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        +         u * sbtData.vertexD.normal[index.y]
        +         v * sbtData.vertexD.normal[index.z];

    const float3 nn = normalize(make_float3(n));

    // Posição da Interceção
    const float3 &rayDir =  optixGetWorldRayDirection();
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax() * rayDir ;

    if (prd.countEmitted && length(sbtData.emission) != 0) {
        prd.emitted = sbtData.emission ;
        return;
    }
    else
        prd.emitted = make_float3(0.0f);

    uint32_t seed = prd.seed;

    {
        const float z1 = rnd(seed);
        const float z2 = rnd(seed);

        float3 w_in;
        cosine_sample_hemisphere( z1, z2, w_in );
        Onb onb( nn );
        onb.inverse_transform( w_in );
        prd.direction = w_in;
        prd.origin    = pos;

        prd.attenuation *= sbtData.diffuse ;
        prd.countEmitted = false;
    }
    
    // Roleta Russa
    float randomValue = rnd(prd.seed);
    float probability;

    // Caso não se acione a Roulette nas Settings do Composer
    if (optixLaunchParams.global->roulette == 0)
    {
        probability = 1;
    }
    else 
    {
        probability = (prd.attenuation.x + prd.attenuation.y + prd.attenuation.z)/3;
    }

    if(randomValue < probability)
    {
        const float z1 = rnd(seed);
        const float z2 = rnd(seed);

        const float3 lightV1 = make_float3(0.47f, 0.0, 0.0f);
        const float3 lightV2 = make_float3(0.0f, 0.0, 0.38f);
        const float3 light_pos = make_float3(optixLaunchParams.global->lightPos) + lightV1 * z1 + lightV2 * z2;

        // Calculate Properties of Light Sample (for area based pdf)
        const float  Ldist = length(light_pos - pos );
        const float3 L     = normalize(light_pos - pos );
        const float  nDl   = dot( nn, L );
        const float3 Ln    = normalize(cross(lightV1, lightV2));
        const float  LnDl  = -dot( Ln, L );

        float weight = 0.0f;
        if( nDl > 0.0f && LnDl > 0.0f )
        {
            uint32_t occluded = 0u;
            optixTrace(optixLaunchParams.traversable,
                pos,
                L,
                0.001f,         // tmin
                Ldist - 0.01f,  // tmax
                0.0f,                    // rayTime
                OptixVisibilityMask( 1 ),
                OPTIX_RAY_FLAG_TERMINATE_ON_FIRST_HIT,
                SHADOW,      // SBT offset
                RAY_TYPE_COUNT,          // SBT stride
                SHADOW,      // missSBTIndex
                occluded);

            if( !occluded )
            {
                const float att = Ldist * Ldist;
                const float A = length(cross(lightV1, lightV2));
                weight = nDl * LnDl * A  / att;
            }
        }
        
        float3 ldir = make_float3(0.600,-0.400,0.700);
        float i = dot(nn, normalize(-ldir));
        
        // Para renderizar as Texturas no caso de Cenários que as possuam
        if (sbtData.hasTexture && sbtData.vertexD.texCoord0) {
            
            // Compute Pixel Texture Coordinate
            const float4 tc
                = (1.f-u-v) * sbtData.vertexD.texCoord0[index.x]
                +         u * sbtData.vertexD.texCoord0[index.y]
                +         v * sbtData.vertexD.texCoord0[index.z];
            // Fetch Texture Value
            float4 fromTexture = tex2D<float4>(sbtData.texture,tc.x,tc.y);
            
            if (i > 0.8) {
                prd.radiance = make_float3(fromTexture) * i;
            } else {
                prd.radiance = make_float3(fromTexture) * 0.4; 
            }
        }
        else
        {
            prd.radiance += make_float3(5.0f, 5.0f, 5.0f) * weight * optixLaunchParams.global->lightScale/probability;
        }
    }
    else
    {
        prd.done= true;
    }
}

// Esta função não sofre alterações
extern "C" __global__ void __anyhit__radiance()
{
}

// Miss usada para definir a Cor de Fundo
extern "C" __global__ void __miss__radiance()
{
    RadiancePRD &prd = *(RadiancePRD*)getPRD<RadiancePRD>();
    
    // Cor de Fundo representada pelo Float3
    prd.radiance = make_float3(0.0f, 0.0f, 0.0f);
    prd.done = true;
}

//Funções Usadas para o Vidro

extern "C" __global__ void __closesthit__radiance__glass()
{
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();
    
    RadiancePRD &prd = *(RadiancePRD*)getPRD<RadiancePRD>();

    // Recuperar Id Primitivo e Índices
    const int primID = optixGetPrimitiveIndex();
    const uint3 index = sbtData.index[primID];

    // Obter Barycentric Coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    // Calcular o Vetor Normal à Superfície
    const float4 n
        = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        +         u * sbtData.vertexD.normal[index.y]
        +         v * sbtData.vertexD.normal[index.z];
    
    if(prd.countEmitted && length(sbtData.emission) != 0)
    {
        prd.emitted = sbtData.emission;
        return;
    }
    else
    {
        prd.emitted = make_float3(0.0f);
    }   

    // Tratar da Parte da Reflexão

    // 1. Normalizar o Vetor Normal
    // O Vetor Normalizado é dado com a mesma direção
    const float3 normalSurface = normalize(make_float3(n));

    // 2. Calcular a Direção do Raio
    const float3 rayDirection = optixGetWorldRayDirection();
    
    // 3. Calcular a Posição
    const float3 position = optixGetWorldRayOrigin() + rayDirection * optixGetRayTmax();
    
    // 4. Aplicar a Reflexão com a Direção do Raio e a Normal à Superfície
    float3 reflection = reflect(rayDirection, normalSurface);

    // Tratar da Parte da Refração
    // Refração vem sempre acompanhada da Reflexão
    // Parte da Luz que incide é Refletida e outra Refratada

    float3 refraction;

    // Produto Escalar do Vetor da Direção do Raio e do Vetor da Normal à Superfície < 0
    if(dot(rayDirection, normalSurface) < 0)
    {
        refraction = refract(rayDirection, normalSurface, 0.6);
    }
    // Produto Escalar do Vetor da Direção do Raio e do Vetor da Normal > 0
    else
    {
        refraction = refract(rayDirection, -normalSurface, 1.50);
    }
    
    prd.attenuation *= sbtData.diffuse;
    prd.countEmitted = true;
    prd.origin = position;
    prd.done = false;

    // Seed é a semente que se usa para gerar o número através da função random(rnd)
    if(rnd(prd.seed) < rnd(prd.seed) * M_PIf)
    {
        prd.direction = rnd(prd.seed) * M_PIf * refraction;
    }
    else
    {
        prd.direction = reflection;
    }
}

//Funções Usadas para o Metal

extern "C" __global__ void __closesthit__radiance__metal()
{
    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  

    RadiancePRD &prd = *(RadiancePRD *)getPRD<RadiancePRD>();

    // Recuperar Id Primitivo e Índices
    const int primID = optixGetPrimitiveIndex();
    const uint3 index = sbtData.index[primID];

    // Obter Barycentric Coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    // Calcular o Vetor Normal à Superfície
    const float4 n
        = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        +         u * sbtData.vertexD.normal[index.y]
        +         v * sbtData.vertexD.normal[index.z];

    // Tratar da Parte da Reflexão

    // 1. Normalizar o Vetor Normal
    // O Vetor Normalizado é dado com a mesma direção
    const float3 normalSurface = normalize(make_float3(n));

    // 2. Calcular a Direção do Raio
    const float3 &rayDirection = optixGetWorldRayDirection();
    
    // 3. Calcular a Posição
    const float3 position = optixGetWorldRayOrigin() + rayDirection * optixGetRayTmax();
    
    // 4. Aplicar a Reflexão com a Direção do Raio e a Normal à Superfície
    float3 reflection = reflect(rayDirection, normalSurface);

    if (prd.countEmitted && length(sbtData.emission) != 0)
    {
        prd.emitted = sbtData.emission;
        return;
    }
    else
    {
        prd.emitted = make_float3(0.0f);
    }

    // Pack Pointer essencial para o resultado
    RadiancePRD afterPRD;
    uint32_t u0, u1;
    packPointer(&afterPRD, u0, u1);
    
    // Parte Essencial ao Path Tracing

    // Definir/Determinar o Glossiness (Brilho) e o Glossy Rays (Raios Brilhantes)
    const float glossiness = optixLaunchParams.global->glossiness;
    const int glossyRays = optixLaunchParams.global->glossyRays;
    
    int numberGlossyRays = 0;

    float3 directionLightIncident = make_float3(0.0f);
    float3 glossyMetal = make_float3(0.0f);

    // Lançar o Número de Raios Brilhantes escolhidos aquando da Execução
    while(numberGlossyRays < glossyRays) {

        do{
            const float z1 = rnd(prd.seed);
            const float z2 = rnd(prd.seed);
            
            // Produz o Efeito Glossy ao Metal
            // Hemisphere Sampling consiste em disparar raios em direção ao Hemisférico
            // O w_in no exemplo base passa a ser a Direção da Luz Incidente
            cosine_power_sample_hemisphere(z1, z2, directionLightIncident, glossiness);
            
            Onb onb(reflection);
            onb.inverse_transform(directionLightIncident);
            
            // Atualização dos Valores do RadiancePRD
            prd.direction = directionLightIncident;
            prd.origin = position;
            prd.attenuation *= sbtData.diffuse;

            // Para se poder criar a luz que é refratada da Bola
            prd.countEmitted = true;
        } while (dot(directionLightIncident, normalSurface) < 0);
    
        // Dá o efeito Glossy ao Metal
        // Quanto maior este valor, maior a "bola" de luz que cai sobre o cimo da Superfície
        glossyMetal = glossyMetal + make_float3(0.5f);
        
        ++numberGlossyRays;
    }

    // O restanto do Código Base
    
    const float z1 = rnd(prd.seed);
    const float z2 = rnd(prd.seed);

    const float3 lightV1 = make_float3(0.47f, 0.0, 0.0f);
    const float3 lightV2 = make_float3(0.0f, 0.0, 0.38f);
    const float3 light_pos = make_float3(optixLaunchParams.global->lightPos) + lightV1 * z1 + lightV2 * z2;

    // Calculate Properties of Light Sample
    const float  Ldist = length(light_pos - position);
    const float3 L     = normalize(light_pos - position);
    const float  nDl   = dot(normalSurface, L);
    const float3 Ln    = normalize(cross(lightV1, lightV2));
    const float  LnDl  = -dot(Ln, L);

    float weight = 0.0f;

    if( nDl > 0.0f && LnDl > 0.0f )
    {
        uint32_t occluded = 0u;
        optixTrace(optixLaunchParams.traversable,
            position,
            L,
            0.001f,         // tmin
            Ldist - 0.01f,  // tmax
            0.0f,                    // rayTime
            OptixVisibilityMask( 1 ),
            OPTIX_RAY_FLAG_NONE,
            RAIDANCE,      // SBT offset
            RAY_TYPE_COUNT,          // SBT stride
            RAIDANCE,      // missSBTIndex
            u0,u1);

        if(!occluded)
        {
            const float att = Ldist * Ldist;
            const float A = length(cross(lightV1, lightV2));
            weight = nDl * LnDl * A  / att;
        }
    }

    prd.radiance
        += make_float3(5.0f, 5.0f, 5.0f)
        * weight
        * optixLaunchParams.global->lightScale 
        * (glossyMetal/glossyRays);
}

// ############################################################
// Shadow Rays

extern "C" __global__ void __closesthit__shadow()
{
    optixSetPayload_0( static_cast<uint32_t>(true));
}

// Any Hit for Shadows
extern "C" __global__ void __anyhit__shadow()
{
}

// Miss for Shadows
extern "C" __global__ void __miss__shadow()
{
    optixSetPayload_0( static_cast<uint32_t>(false));
}

// ############################################################
// Primary Rays

extern "C" __global__ void __raygen__renderFrame()
{

    const int ix = optixGetLaunchIndex().x;
    const int iy = optixGetLaunchIndex().y;
    const auto &camera = optixLaunchParams.camera;  

    const int &maxDepth = optixLaunchParams.frame.maxDepth;

    float squaredRaysPerPixel = float(optixLaunchParams.frame.raysPerPixel);
    float2 delta = make_float2(1.0f/squaredRaysPerPixel, 1.0f/squaredRaysPerPixel);

    float3 result = make_float3(0.0f);

    uint32_t seed = tea<4>( ix * optixGetLaunchDimensions().x + iy, optixLaunchParams.frame.frame );

    for (int i = 0; i < squaredRaysPerPixel; ++i) {
        for (int j = 0; j < squaredRaysPerPixel; ++j) {

            const float2 subpixel_jitter = make_float2( delta.x * (i + rnd(seed)), delta.y * (j + rnd( seed )));
            const float2 screen(make_float2(ix + subpixel_jitter.x, iy + subpixel_jitter.y)
                            / make_float2(optixGetLaunchDimensions().x, optixGetLaunchDimensions().y) * 2.0 - 1.0);
        
            // note: nau already takes into account the field of view and ratio when computing 
            // camera horizontal and vertical
            float3 origin = camera.position;
            float3 rayDir = normalize(camera.direction
                                + (screen.x ) * camera.horizontal
                                + (screen.y ) * camera.vertical);

            RadiancePRD prd;
            prd.emitted      = make_float3(0.f);
            prd.radiance     = make_float3(0.f);
            prd.attenuation  = make_float3(1.f);
            prd.countEmitted = true;
            prd.done         = false;
            prd.seed         = seed;

            uint32_t u0, u1;
            packPointer( &prd, u0, u1 );             
            
            for (int k = 0; k < maxDepth && !prd.done; ++k) {

                optixTrace(optixLaunchParams.traversable,
                        origin,
                        rayDir,
                        0.001f,    // tmin
                        1e20f,  // tmax
                        0.0f, OptixVisibilityMask( 1 ),
                        OPTIX_RAY_FLAG_NONE, RAIDANCE, RAY_TYPE_COUNT, RAIDANCE, u0, u1 );

                result += prd.emitted;
                result += prd.radiance * prd.attenuation;

                origin = prd.origin;
                rayDir = prd.direction;
            }
        }
    }

    result = result / (squaredRaysPerPixel*squaredRaysPerPixel);
    float gamma = optixLaunchParams.global->gamma;
    // compute index
    const uint32_t fbIndex = ix + iy*optixGetLaunchDimensions().x;

    optixLaunchParams.global->accumBuffer[fbIndex] = 
        (optixLaunchParams.global->accumBuffer[fbIndex] * optixLaunchParams.frame.subFrame +
        make_float4(result.x, result.y, result.z, 1)) /(optixLaunchParams.frame.subFrame+1);

    
    float4 rgbaf = optixLaunchParams.global->accumBuffer[fbIndex];
    //convert float (0-1) to int (0-255)
    const int r = int(255.0f*min(1.0f, pow(rgbaf.x, 1/gamma)));
    const int g = int(255.0f*min(1.0f, pow(rgbaf.y, 1/gamma)));
    const int b = int(255.0f*min(1.0f, pow(rgbaf.z, 1/gamma))) ;

    // convert to 32-bit rgba value 
    const uint32_t rgba = 0xff000000 | (r<<0) | (g<<8) | (b<<16);
    // write to output buffer
    optixLaunchParams.frame.colorBuffer[fbIndex] = rgba;
}