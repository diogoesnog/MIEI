
#include <optix.h>
#include "random.h"
#include "LaunchParams7.h" // our launch params
#include <vec_math.h> // NVIDIAs math utils


extern "C" {
    __constant__ LaunchParams optixLaunchParams;
}
//  a single ray type
enum { PHONG=0, SHADOW, RAY_TYPE_COUNT };


// -------------------------------------------------------
// closest hit computes color based lolely on the triangle normal

extern "C" __global__ void __closesthit__radiance() {

    float3 &prd = *(float3*)getPRD<float3>();

    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  

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

    // intersection position
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax()*optixGetWorldRayDirection();

    // direction towards light
    float3 lPos = make_float3(optixLaunchParams.global->lightPos);
    float lDirLength = length(lPos - pos) - 0.01f;
    float3 lDir = normalize(lPos - pos);
    float3 nn = normalize(make_float3(n));

    float intensity = max(dot(lDir, nn),0.0f);

    // ray payload
    float shadowAttPRD = 1.0f;
    uint32_t u0, u1;
    packPointer( &shadowAttPRD, u0, u1 );  
  
    // trace shadow ray
    optixTrace(optixLaunchParams.traversable,
        pos,
        lDir,
        0.001f,         // tmin
        lDirLength,     // tmax
        0.0f,           // rayTime
        OptixVisibilityMask( 255 ),
        OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
        SHADOW,             // SBT offset
        RAY_TYPE_COUNT,     // SBT stride
        SHADOW,             // missSBTIndex 
        u0, u1 );

    if (sbtData.hasTexture && sbtData.vertexD.texCoord0) {  
        // get barycentric coordinates
        // compute pixel texture coordinate
        const float4 tc
          = (1.f-u-v) * sbtData.vertexD.texCoord0[index.x]
          +         u * sbtData.vertexD.texCoord0[index.y]
          +         v * sbtData.vertexD.texCoord0[index.z];
        // fetch texture value
        
        float4 fromTexture = tex2D<float4>(sbtData.texture,tc.x,tc.y);
        prd = make_float3(fromTexture) * min(intensity * shadowAttPRD + 0.0, 1.0);
    }
    else
        prd = sbtData.color * min(intensity * shadowAttPRD + 0.0, 1.0);
}


// any hit to ignore intersections with back facing geometry
extern "C" __global__ void __anyhit__radiance() {

}


// miss sets the background color
extern "C" __global__ void __miss__radiance() {

    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(0.0f, 0.0f, 1.0f);
}


// -----------------------------------------------
// Shadow rays

extern "C" __global__ void __closesthit__shadow() {

    float &prd = *(float*)getPRD<float>();
    prd = 0.0f;
}


// any hit for shadows
extern "C" __global__ void __anyhit__shadow() {

}


// miss for shadows
extern "C" __global__ void __miss__shadow() {

    float &prd = *(float*)getPRD<float>();
    // set blue as background color
    prd = 1.0f;
}


// -----------------------------------------------
// Light material


extern "C" __global__ void __closesthit__light() {

    float3 &prd = *(float3*)getPRD<float3>();
    prd = make_float3(1.0f, 1.0f, 1.0f);
}


extern "C" __global__ void __anyhit__light() {
}


extern "C" __global__ void __miss__light() {
}


extern "C" __global__ void __closesthit__light_shadow() {

    float &prd = *(float*)getPRD<float>();
    prd = 1.0f;
}


// any hit to ignore intersections based on alpha transparency
extern "C" __global__ void __anyhit__light_shadow() {
}


// miss sets the background color
extern "C" __global__ void __miss__light_shadow() {
}




// -----------------------------------------------
// Metal Phong rays

extern "C" __global__ void __closesthit__phong_metal() {

    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  

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
    // ray payload

    float3 normal = normalize(make_float3(n));

    // entering glass
    //if (dot(optixGetWorldRayDirection(), normal) < 0)

    float3 afterPRD = make_float3(1.0f);
    uint32_t u0, u1;
    packPointer( &afterPRD, u0, u1 );  

    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax()*optixGetWorldRayDirection();
    //(1.f-u-v) * A + u * B + v * C;
    
    float3 rayDir = reflect(optixGetWorldRayDirection(), normal);
    optixTrace(optixLaunchParams.traversable,
        pos,
        rayDir,
        0.00001f,    // tmin
        1e20f,  // tmax
        0.0f,   // rayTime
        OptixVisibilityMask( 255 ),
        OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
        PHONG,             // SBT offset
        RAY_TYPE_COUNT,     // SBT stride
        PHONG,             // missSBTIndex 
        u0, u1 );

    float3 &prd = *(float3*)getPRD<float3>();
    prd = make_float3(0.8,0.8,0.8) * afterPRD;
}





// -----------------------------------------------
// Glass Phong rays

SUTIL_INLINE SUTIL_HOSTDEVICE float3 refract(const float3& i, const float3& n, const float eta) {

    float k = 1.0 - eta * eta * (1.0 - dot(n, i) * dot(n, i));
    if (k < 0.0)
        return make_float3(0.0f);
    else
        return (eta * i - (eta * dot(n, i) + sqrt(k)) * n);
}


extern "C" __global__ void __closesthit__phong_glass() {

    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();  

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

    float3 normal = normalize(make_float3(n));
    const float3 normRayDir = optixGetWorldRayDirection();

    // new ray direction
    float3 rayDir;
    // entering glass
    float dotP;
    if (dot(normRayDir, normal) < 0) {
        dotP = dot(normRayDir, -normal);
        rayDir = refract(normRayDir, normal, 0.66);
    }
    // exiting glass
    else {
        dotP = 0;
        rayDir = refract(normRayDir, -normal, 1.5);
    }

    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax() * optixGetWorldRayDirection();
    
    float3 refractPRD = make_float3(0.0f);
    uint32_t u0, u1;
    packPointer( &refractPRD, u0, u1 );  
    
    if (length(rayDir) > 0)
        optixTrace(optixLaunchParams.traversable,
            pos,
            rayDir,
            0.00001f,    // tmin
            1e20f,  // tmax
            0.0f,   // rayTime
            OptixVisibilityMask( 255 ),
            OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
            PHONG,             // SBT offset
            RAY_TYPE_COUNT,     // SBT stride
            PHONG,             // missSBTIndex 
            u0, u1 );

    // ray payload 
    float3 &prd = *(float3*)getPRD<float3>();
 
    float3 reflectPRD = make_float3(0.0f);
    if (dotP > 0) {
        float3 reflectDir = reflect(normRayDir, normal);        
        packPointer( &reflectPRD, u0, u1 );  
        optixTrace(optixLaunchParams.traversable,
            pos,
            reflectDir,
            0.00001f,    // tmin
            1e20f,  // tmax
            0.0f,   // rayTime
            OptixVisibilityMask( 255 ),
            OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
            PHONG,             // SBT offset
            RAY_TYPE_COUNT,     // SBT stride
            PHONG,             // missSBTIndex 
            u0, u1 );
        float r0 = (1.5f - 1.0f)/(1.5f + 1.0f);
        r0 = r0*r0 + (1-r0*r0) * pow(1-dotP,5);
        prd =  refractPRD * (1-r0) + r0*reflectPRD;
    }
    else
        prd =  refractPRD ;
}



extern "C" __global__ void __anyhit__phong_glass() {

}


// miss sets the background color
extern "C" __global__ void __miss__phong_glass() {

    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(0.0f, 0.0f, 1.0f);
}



// -----------------------------------------------
// Glass Shadow rays

extern "C" __global__ void __closesthit__shadow_glass() {

    // ray payload
    float afterPRD = 1.0f;
    uint32_t u0, u1;
    packPointer( &afterPRD, u0, u1 );  

    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax()*optixGetWorldRayDirection();
    
    // trace primary ray
    optixTrace(optixLaunchParams.traversable,
        pos,
        optixGetWorldRayDirection(),
        0.001f,    // tmin
        1e20f,  // tmax
        0.0f,   // rayTime
        OptixVisibilityMask( 255 ),
        OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
        SHADOW,             // SBT offset
        RAY_TYPE_COUNT,     // SBT stride
        SHADOW,             // missSBTIndex 
        u0, u1 );

    float &prd = *(float*)getPRD<float>();
    prd = 0.95f * afterPRD;
}


// any hit for shadows
extern "C" __global__ void __anyhit__shadow_glass() {

}


// miss for shadows
extern "C" __global__ void __miss__shadow_glass() {

    float &prd = *(float*)getPRD<float>();
    // set blue as background color
    prd = 1.0f;
}


// -----------------------------------------------
// Primary Rays

extern "C" __global__ void __raygen__renderFrame() {

    // compute a test pattern based on pixel ID
    const int ix = optixGetLaunchIndex().x;
    const int iy = optixGetLaunchIndex().y;
    const auto &camera = optixLaunchParams.camera;  
    
    float raysPerPixel = float(optixLaunchParams.frame.raysPerPixel);
    float2 delta = make_float2(1.0f/raysPerPixel, 1.0f/raysPerPixel);

    const float d_o = optixLaunchParams.global->focalDistance;
    const float A = optixLaunchParams.global->aperture;
    const float d_p = optixLaunchParams.global->lensDistance;
 
	if (optixLaunchParams.frame.frame == 0 && ix == 0 && iy == 0) {

		// print info to console
		printf("===========================================\n");
        printf("Nau Ray-Tracing Debug\n");
        const float4 &ld = optixLaunchParams.global->lightPos;
        printf("LightPos: %f, %f %f %f\n", ld.x,ld.y,ld.z,ld.w);
        printf("Launch dim: %u %u\n", optixGetLaunchDimensions().x, optixGetLaunchDimensions().y);
        printf("===========================================\n");
	}

    // ray payload
    float3 pixelColorPRD = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );

    // compute ray direction
    // normalized screen plane position, in [-1, 1]^2
    const float2 screen(make_float2(ix+.5f,iy+.5f)
                    / make_float2(optixGetLaunchDimensions().x, optixGetLaunchDimensions().y) * 2.0 - 1.0);


    // TP3

    //Cálculo coordenadas do pixel
    float3 pixel = camera.position + (screen.x * (-1)) * camera.horizontal + (screen.y * (-1)) * camera.vertical;

    //Cálculo direção do pixel à camara
    float3 dir_pixel_camera = pixel - camera.position;

    //Cálculo do ângulo entre o vetor do pixel ao centro da camera e do vetor do centro da camera ao centro do Plano de Imagem
    float angle_dcp_dcpi = acos((dir_pixel_camera.x * camera.direction.x + dir_pixel_camera.y * camera.direction.y + dir_pixel_camera.z * camera.direction.z)/(sqrt (pow(dir_pixel_camera.x, 2) + pow(dir_pixel_camera.y, 2) + pow(dir_pixel_camera.z, 2)) * sqrt((pow(camera.direction.x, 2) + pow(camera.direction.y, 2) + pow(camera.direction.z, 2)))));

    //Cálculo da distância entre o pixel ao centro da camera
    float dpc = sqrt(pow(pixel.x - camera.position.x, 2) + pow(pixel.y - camera.position.y, 2) + pow(pixel.z - camera.position.z, 2)); 
    
    //Cálculo da distância entre o centro da camera e o centro do Plano de Imagem
    float dc_planoImagem = cos(angle_dcp_dcpi) * dpc;

    //Cálculo das coordenadas do centro da lente
    float3 centroLente = camera.position + camera.direction * (d_p - dc_planoImagem);

    // Cálculo da distância do pixel ao centro da lente
    float dpl = sqrt(pow(pixel.x - centroLente.x, 2) + pow(pixel.y - centroLente.y, 2) + pow(pixel.z - centroLente.z, 2)); 


    //Cálculo do ponto P (PONTO DO PLANO DE FOCO)
    float m = d_o / d_p; // factor de proporção

    float dlP = dpl * m; // Distância do centro da lente ao ponto P 

    float3 P = pixel + normalize(centroLente - pixel) * (dpl + dlP); // Coordenadas do P no plano de foco
    


    float red = 0.0f, blue = 0.0f, green = 0.0f;
    for (int i = 0; i < raysPerPixel; ++i) {
        for (int j = 0; j < raysPerPixel; ++j) {
            uint32_t seed = tea<4>( ix * optixGetLaunchDimensions().x + iy, i*raysPerPixel + j );

            float raio = A * rnd(seed);
            float angulo = 2 * M_PIf * rnd(seed);

            float3 frente = normalize(camera.direction);

            float dot_perp = dot(frente, make_float3(1,0,0));

            float3 perpendicular;

            if (dot_perp < 0.1) {
                perpendicular = normalize(cross(make_float3(1,0,0), frente));
            } else {
                perpendicular = normalize(cross(make_float3(0,1,0), frente));
            }

            float3 outra_perp = normalize(cross(perpendicular, frente));

            //Cálculo do ponto de origem para lançar o raio
            float3 ponto_sampling = centroLente + raio * (perpendicular * cos (angulo) + outra_perp * sin(angulo));
            
            //Cálculo da direção dos raios
            float3 direcao = normalize(P - ponto_sampling);
            
            // trace primary ray
            optixTrace(optixLaunchParams.traversable,
                    ponto_sampling,
                    direcao,
                    0.f,    // tmin
                    1e20f,  // tmax
                    0.0f,   // rayTime
                    OptixVisibilityMask( 255 ),
                    OPTIX_RAY_FLAG_NONE,//,OPTIX_RAY_FLAG_DISABLE_ANYHIT
                    PHONG,             // SBT offset
                    RAY_TYPE_COUNT,               // SBT stride
                    PHONG,             // missSBTIndex 
                    u0, u1 );

            red += pixelColorPRD.x / (raysPerPixel*raysPerPixel);
            green += pixelColorPRD.y / (raysPerPixel*raysPerPixel);
            blue += pixelColorPRD.z / (raysPerPixel*raysPerPixel);

            if (ix == 0 && iy == 0) {
                printf("pixel: %f %f %f\n", pixel.x, pixel.y, pixel.z);
                printf("centro camera: %f %f %f\n", camera.position.x, camera.position.y, camera.position.z);
            }
        }
    }

    //convert float (0-1) to int (0-255)
    const int r = int(255.0f*red);
    const int g = int(255.0f*green);
    const int b = int(255.0f*blue);
    // convert to 32-bit rgba value 
    const uint32_t rgba = 0xff000000
      | (r<<0) | (g<<8) | (b<<16);
    // compute index
    const uint32_t fbIndex = ix + iy*optixGetLaunchDimensions().x;
    // write to output buffer
    optixLaunchParams.frame.colorBuffer[fbIndex] = rgba;
}
  

