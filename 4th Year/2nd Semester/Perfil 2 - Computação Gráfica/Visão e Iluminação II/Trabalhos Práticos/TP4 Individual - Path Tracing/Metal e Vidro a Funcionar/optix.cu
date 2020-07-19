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

    bool        done;
    uint32_t    seed;
    int32_t     countEmitted;
};

// Esta função não sofre alterações
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
    
    const float z1 = rnd(seed);
    const float z2 = rnd(seed);
    prd.seed = seed;

    const float3 lightV1 = make_float3(0.47f, 0.0, 0.0f);
    const float3 lightV2 = make_float3(0.0f, 0.0, 0.38f);
    const float3 light_pos = make_float3(optixLaunchParams.global->lightPos) + lightV1 * z1 + lightV2 * z2;

    // Calculate properties of Light Sample (for area based pdf)
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

    prd.radiance += make_float3(5.0f, 5.0f, 5.0f) * weight * optixLaunchParams.global->lightScale;
}

// Esta função não sofre alterações
extern "C" __global__ void __anyhit__radiance()
{
}

// Miss usada para definir a Cor de Fundo
// Cor mudada de float3(0,0,0) para float3(1,1,1)
// Fundo branco. Nota-se no Reflexo do Objecto.
extern "C" __global__ void __miss__radiance()
{
    RadiancePRD &prd = *(RadiancePRD*)getPRD<RadiancePRD>();
    // Cor de Fundo representada pelo Float3
    prd.radiance = make_float3(1.0f, 1.0f, 1.0f);
    prd.done = true;
}

// 1. Shadow Rays

extern "C" __global__ void __closesthit__shadow()
{
    optixSetPayload_0( static_cast<uint32_t>(true));
}

// any hit for shadows
extern "C" __global__ void __anyhit__shadow()
{
}

// miss for shadows
extern "C" __global__ void __miss__shadow()
{
    optixSetPayload_0( static_cast<uint32_t>(false));
}

//METAL

extern "C" __global__ void __closesthit__radiance_metal()
{

    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  


    RadiancePRD &prd = *(RadiancePRD *)getPRD<RadiancePRD>();

    // retrieve primitive id and indexes
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    // compute normal
    const float4 n
        = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        +         u * sbtData.vertexD.normal[index.y]
        +         v * sbtData.vertexD.normal[index.z];

    const float3 normal = normalize(make_float3(n));
    float3 normRayDir = optixGetWorldRayDirection();

    // intersection position
    const float3 &rayDir =  optixGetWorldRayDirection();
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax() * rayDir;

    if (prd.countEmitted && length(sbtData.emission) != 0) {
        prd.emitted = sbtData.emission;
        return;
    }
    else
        prd.emitted = make_float3(0.0f);

    //declaração do seed  
    uint32_t seed = prd.seed;
    const float z1 = rnd(seed);
    const float z2 = rnd(seed);
    prd.seed = seed;

    RadiancePRD afterPRD;
    afterPRD.radiance = make_float3(1.0f);
    afterPRD.seed = prd.seed;
    uint32_t u0, u1;
    packPointer( &afterPRD, u0, u1 );
    
    //Achar o número de raios brilhantes, e o grau de brilho
    const float glossiness = optixLaunchParams.global->glossiness;
    const int glossy_rays = optixLaunchParams.global->glossyRays;
    float3 glossy = make_float3(0.0f);
    float3 direcaoL;
    float3 reflectDir = reflect(optixGetWorldRayDirection(), normal);
    
    //Lançar os raios
    for (int i = 0; i < glossy_rays; ++i) {
        afterPRD.radiance = make_float3(1.0f);
        do{
            const float z1 = rnd(seed);
            const float z2 = rnd(seed);
            prd.seed = seed;
        
            cosine_power_sample_hemisphere( z1, z2, direcaoL, glossiness );
            Onb onb( reflectDir );
            onb.inverse_transform( direcaoL );
            prd.direction = direcaoL;
            prd.origin    = pos;
            prd.attenuation *= sbtData.diffuse ;
           // prd.countEmitted = false;
        } while (dot(direcaoL, normal) < 0.001);
    
        glossy += afterPRD.radiance;
    
    }

    const float3 lightV1 = make_float3(0.47f, 0.0, 0.0f);
    const float3 lightV2 = make_float3(0.0f, 0.0, 0.38f);
    const float3 light_pos = make_float3(optixLaunchParams.global->lightPos) + lightV1 * z1 + lightV2 * z2;

    // Calculate properties of light sample (for area based pdf)
    const float  Ldist = length(light_pos - pos );
    const float3 L     = normalize(light_pos - pos );
    const float  nDl   = dot( normal, L );
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
            OPTIX_RAY_FLAG_NONE,
            RAIDANCE,      // SBT offset
            RAY_TYPE_COUNT,          // SBT stride
            RAIDANCE,      // missSBTIndex
            u0,u1);

    if( !occluded )
        {
            const float att = Ldist * Ldist;
            const float A = length(cross(lightV1, lightV2));
        weight = nDl * LnDl * A  / att;
        }
    }
    prd.seed = seed;
    prd.radiance += make_float3(5.0f, 5.0f, 5.0f)*weight* optixLaunchParams.global->lightScale * (glossy *make_float3(0.8f, 0.8f, 0.8f) / glossy_rays);
}

//GLASS

extern "C" __global__ void __closesthit__radiance_glass()
{
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();
    
    RadiancePRD &prd = *(RadiancePRD*)getPRD<RadiancePRD>();

    // retrieve primitive id and indexes
    const int primID = optixGetPrimitiveIndex();
    const uint3 index = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    // compute normal
    const float4 n
        = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        +         u * sbtData.vertexD.normal[index.y]
        +         v * sbtData.vertexD.normal[index.z];
    
    float3 normal = normalize(make_float3(n));
    const float3 normRayDir = optixGetWorldRayDirection();

    // intersection position
    const float3 &rayDir = optixGetWorldRayDirection();
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax() * rayDir;
    float3 reflectDir = reflect(normRayDir, normal);

    if(prd.countEmitted && length(sbtData.emission) != 0)
    {
        prd.emitted = sbtData.emission;
        return;
    }
    else
    {
        prd.emitted = make_float3(0.0f);
    }

    uint32_t seed = prd.seed;

    const float z1 = rnd(seed);
    const float z2 = rnd(seed);
    prd.seed = seed;
    const float z = rnd(prd.seed);

    const float3 lightV1 = make_float3(0.47f, 0.0, 0.0f);
    const float3 lightV2 = make_float3(0.0f, 0.0, 0.38f);
    const float3 light_pos = make_float3(optixLaunchParams.global->lightPos) + lightV1 * z1 + lightV2 * z2;

    // calculate properties of light sample (for area based pdf)
    const float Ldist = length(light_pos - pos);
    const float3 L = normalize(light_pos - pos);
    const float nDl = dot(normal,L);
    const float3 Ln = normalize(cross(lightV1, lightV2));
    const float LnDl = -dot(Ln, L);

    // nova direcao do raio
    float3 direcao;

    // entering glass
    float dotP;
    if(dot(normRayDir, normal) < 0)
    {
        dotP = dot(normRayDir, -normal);

        direcao = refract(normRayDir, normal, 0.66);
        prd.direction = direcao;
        prd.attenuation *= sbtData.diffuse;
        prd.countEmitted = true;
        prd.origin = pos;
        prd.done = false;
        prd.seed = seed; 
    }
    // exiting glass
    else
    {
        dotP = 0;
        
        direcao = refract(normRayDir, -normal, 1.5);
        prd.direction = direcao;
        prd.attenuation *= sbtData.diffuse;
        prd.countEmitted = true;
        prd.origin = pos;
        prd.done = false;
        prd.seed = seed; 
    }

    RadiancePRD refractPRD;
    refractPRD.radiance = make_float3(0.0f);
    refractPRD.seed = prd.seed;
    uint32_t u0, u1;
    packPointer(&refractPRD, u0, u1);

    float weight = 0.0f;
    if(nDl > 0.0f && LnDl > 0.0f)
    {
        uint32_t occluded = 0u;
        if(length(direcao) > 0)
        {
            optixTrace(optixLaunchParams.traversable,
                pos,
                direcao,
                0.00001f,
                Ldist - 0.01f,
                0.0f,
                OptixVisibilityMask(1),
                OPTIX_RAY_FLAG_NONE,
                RAIDANCE,
                RAY_TYPE_COUNT,
                RAIDANCE,
                u0,u1);
        }
        RadiancePRD reflectPRD;
        reflectPRD.radiance = make_float3(0.0f);
        reflectPRD.seed = prd.seed;

        if(dotP > 0)
        {
            packPointer(&reflectPRD, u0, u1);

            //Achar o número de raios brilhantes, e o grau de brilho
            const float glossiness = optixLaunchParams.global->glossiness;
            const int glossy_rays = optixLaunchParams.global->glossyRays;
            float3 glossy = make_float3(0.0f);
            float3 direcaoL;
            float3 reflectDir = reflect(optixGetWorldRayDirection(), normal);
            
            //Lançar os raios
            for (int i = 0; i < glossy_rays; ++i) {
                reflectPRD.radiance = make_float3(1.0f);
                do{
                    const float z1 = rnd(seed);
                    const float z2 = rnd(seed);
                    prd.seed = seed;
                
                    cosine_power_sample_hemisphere( z1, z2, direcaoL, glossiness );
                    Onb onb( reflectDir );
                    onb.inverse_transform( direcaoL );
                    prd.direction = direcaoL;
                    prd.origin    = pos;
                    prd.attenuation *= sbtData.diffuse ;
                // prd.countEmitted = false;
                } while (dot(direcaoL, normal) < 0.001);
            
                glossy += reflectPRD.radiance;
            
            }

            optixTrace(optixLaunchParams.traversable,
                pos,
                L,
                0.00001f,
                Ldist - 0.01f,
                0.0f,
                OptixVisibilityMask(1),
                OPTIX_RAY_FLAG_NONE,
                RAIDANCE,
                RAY_TYPE_COUNT,
                RAIDANCE,
                u0,u1);
            
            float r0 = (15.0f - 1.0f)/(15.0f + 1.0f);
            r0 = r0*r0 + (1-r0*r0) * pow(1-dotP, 5);
            prd.radiance += make_float3(5.0f, 5.0f, 5.0f)*(weight)*optixLaunchParams.global->lightScale * (refractPRD.radiance * (1-r0) + r0 * reflectPRD.radiance);
        }
        else
        {
            prd.radiance += make_float3(5.0f, 5.0f, 5.0f)*(weight)*optixLaunchParams.global->lightScale * refractPRD.radiance;
        }
        if(!occluded)
        {
            const float att = Ldist * Ldist;
            const float A = length(cross(lightV1,lightV2));
            weight = nDl * LnDl * A / att;
        }
    }

    if(rnd(prd.seed) > 0.5)
    {
        prd.direction = direcao;
    }
    else
    {
        prd.direction = reflectDir;
    }

}

extern "C" __global__ void __anyhit__radiance_glass()
{
}

// miss sets the background color
extern "C" __global__ void __miss__radiance_glass()
{
    RadiancePRD &prd = *(RadiancePRD*)getPRD<RadiancePRD>();
    // set black as background color
    prd.radiance = make_float3(0.0f, 0.0f, 0.0f);
    prd.done = true;
}

// Shadow rays

extern "C" __global__ void __closesthit__shadow_glass()
{
    optixSetPayload_0( static_cast<uint32_t>(true));
}

// any hit for shadows
extern "C" __global__ void __anyhit__shadow_glass()
{
}

// miss for shadows
extern "C" __global__ void __miss__shadow_glass()
{
    optixSetPayload_0( static_cast<uint32_t>(false));
}

// -----------------------------------------------
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