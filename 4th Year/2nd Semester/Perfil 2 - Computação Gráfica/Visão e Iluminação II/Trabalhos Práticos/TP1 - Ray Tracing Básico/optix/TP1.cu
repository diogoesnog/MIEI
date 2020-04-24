#include <optix.h>
#include "LaunchParams.h" // our launch params
#include "vec_math.h" // NVIDIAs math utils

extern "C" {
    __constant__ LaunchParams optixLaunchParams;
}

// Acrescentamos o SHADOW_RAY_TYPE
enum { PHONG_RAY_TYPE=0, SHADOW_RAY_TYPE, RAY_TYPE_COUNT};

extern "C" __global__ void __closesthit__radiance() {
    // get the payload variable
    float3 &prd = *(float3*)getPRD<float3>();

    // get mesh data
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

    // ray payload
    float3 pixelColorPRD = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );  

    // retrieve primitive id and indexes
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    float4 pos4 = (1.f-u-v) * sbtData.vertexD.position[index.x]
        + u * sbtData.vertexD.position[index.y]
        + v * sbtData.vertexD.position[index.z];

    float3 pos = make_float3(pos4.x,pos4.y,pos4.z);

    float4 norm4 = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        + u * sbtData.vertexD.normal[index.y]
        + v * sbtData.vertexD.normal[index.z];

    float3 normal = make_float3(norm4.x,norm4.y,norm4.z);

    float3 ldir = make_float3(0.600,-0.400,0.700);

    float i = dot(normalize(normal), normalize(-ldir));

    optixTrace(optixLaunchParams.traversable,
            pos,
            -ldir,
            0.1f, // tmin
            1e20f, // tmax
            0.0f, // rayTime
            OptixVisibilityMask( 255 ),
            OPTIX_RAY_FLAG_TERMINATE_ON_FIRST_HIT,
            SHADOW_RAY_TYPE, // SBT offset
            RAY_TYPE_COUNT, // SBT stride
            SHADOW_RAY_TYPE, // missSBTIndex
            u0, u1 );

    if (sbtData.hasTexture && sbtData.vertexD.texCoord0) {
        // compute pixel texture coordinate
        const float4 tc
            = (1.f-u-v) * sbtData.vertexD.texCoord0[index.x]
            +         u * sbtData.vertexD.texCoord0[index.y]
            +         v * sbtData.vertexD.texCoord0[index.z];
        // fetch texture value
        float4 fromTexture = tex2D<float4>(sbtData.texture,tc.x,tc.y);
        
        if (i > 0.8) {
            prd= make_float3(fromTexture) * i;
        } else {
            prd= make_float3(fromTexture) * 0.4; 
        }
    }
    else {
        if (i > 0.3) {
            prd = sbtData.color * i;
        } else {
            prd = sbtData.color * 0.3;
        }
    }
    if(pixelColorPRD.y == 1.0) {
        prd *= 0.5;
    }
}

// Nothing to do in here
extern "C" __global__ void __anyhit__radiance() {}

// Miss sets the Background Color
extern "C" __global__ void __miss__radiance() {

    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(1.0f, 1.0f, 1.0f);
}

extern "C" __global__ void __closesthit__shadow(){
    // get the payload variable
    float3 &prd = *(float3*)getPRD<float3>();
    prd=make_float3(0,1,0);
}

// Nothing to do in here
extern "C" __global__ void __anyhit__shadow() {}

extern "C" __global__ void __miss__shadow() {
    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(1.0f, 0.0f, 0.0f);
}

// GRADES PHON FUNCTIONS

extern "C" __global__ void __closesthit__phong_alphaTrans() {}

extern "C" __global__ void __anyhit__phong_alphaTrans() {
    // get the payload variable
    float3 &prd = *(float3*)getPRD<float3>();

    // get mesh data
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

    // ray payload
    float3 pixelColorPRD = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );  

    // retrieve primitive id and indexes
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    float4 norm4 = (1.f-u-v) * sbtData.vertexD.normal[index.x]
    + u * sbtData.vertexD.normal[index.y]
    + v * sbtData.vertexD.normal[index.z];

    float3 normal = make_float3(norm4.x,norm4.y,norm4.z);

    float3 ldir = make_float3(0.600,-0.400,0.700);

    float i = dot(normalize(normal), normalize(-ldir));

    if (sbtData.hasTexture && sbtData.vertexD.texCoord0) {
        // compute pixel texture coordinate
        const float4 tc
            = (1.f-u-v) * sbtData.vertexD.texCoord0[index.x]
            +         u * sbtData.vertexD.texCoord0[index.y]
            +         v * sbtData.vertexD.texCoord0[index.z];
        // fetch texture value
        float4 fromTexture = tex2D<float4>(sbtData.texture,tc.x,tc.y);

        if (fromTexture.w == 1) {
            if (i > 0.3) {
                prd= make_float3(fromTexture) * i;
            } else {
                prd= make_float3(fromTexture) * 0.3; 
            }
        }
        else {
            optixIgnoreIntersection();
        }
    }
}

extern "C" __global__ void __miss__phong_alphaTrans() {
}

// GRADES SHADOW FUNCTIONS

extern "C" __global__ void __closesthit__shadow_alphaTrans() {}

extern "C" __global__ void __anyhit__shadow_alphaTrans() {
    // get the payload variable
    float3 &prd = *(float3*)getPRD<float3>();

    // get mesh data
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

    // ray payload
    float3 pixelColorPRD = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );  

    // retrieve primitive id and indexes
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    float4 norm4 = (1.f-u-v) * sbtData.vertexD.normal[index.x]
    + u * sbtData.vertexD.normal[index.y]
    + v * sbtData.vertexD.normal[index.z];

    float3 normal = make_float3(norm4.x,norm4.y,norm4.z);

    float3 ldir = make_float3(0.600,-0.400,0.700);

    float i = dot(normalize(normal), normalize(-ldir));

    if (sbtData.hasTexture && sbtData.vertexD.texCoord0) {
        // compute pixel texture coordinate
        const float4 tc
            = (1.f-u-v) * sbtData.vertexD.texCoord0[index.x]
            +         u * sbtData.vertexD.texCoord0[index.y]
            +         v * sbtData.vertexD.texCoord0[index.z];
        // fetch texture value
        float4 fromTexture = tex2D<float4>(sbtData.texture,tc.x,tc.y);

        if (fromTexture.w != 1) {
            optixIgnoreIntersection();
        }
    }
}

extern "C" __global__ void __miss__shadow_alphaTrans() {
    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(1.0f, 0.0f, 0.0f);
}

// GLASS FUNCTIONS

// Nothing to do in here
extern "C" __global__ void __anyhit__phong_glass() {}

extern "C" __global__ void __closesthit__phong_glass() {
    // get the payload variable
    float3 &prd = *(float3*)getPRD<float3>();

    // get mesh data
    const TriangleMeshSBTData &sbtData
        = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

    // retrieve primitive id and indexes
    const int   primID = optixGetPrimitiveIndex();
    const uint3 index  = sbtData.index[primID];

    // get barycentric coordinates
    const float u = optixGetTriangleBarycentrics().x;
    const float v = optixGetTriangleBarycentrics().y;

    float4 pos4 = (1.f-u-v) * sbtData.vertexD.position[index.x]
        + u * sbtData.vertexD.position[index.y]
        + v * sbtData.vertexD.position[index.z];

    float3 pos = make_float3(pos4.x,pos4.y,pos4.z);

    float4 norm4 = (1.f-u-v) * sbtData.vertexD.normal[index.x]
        + u * sbtData.vertexD.normal[index.y]
        + v * sbtData.vertexD.normal[index.z];

    float3 normal = make_float3(norm4.x,norm4.y,norm4.z);

    float3 ldir = make_float3(0.600,-0.400,0.700);

    const auto &camera=optixLaunchParams.camera;
    const int ix=optixGetLaunchIndex().x;
    const int iy=optixGetLaunchIndex().y;
    const float2 screen(make_float2(ix+.5f,iy+.5f)/make_float2(optixGetLaunchDimensions().x,optixGetLaunchDimensions().y)*2.0-1.0);
    float3 rayDir=normalize(camera.direction+screen.x*camera.horizontal+screen.y*camera.vertical);
    
    // Cor do Reflexo

    float3 reflexoPRD = make_float3(0.f);
    uint32_t u0, u1;
    packPointer( &reflexoPRD, u0, u1 );

    float3 reflexoDir = reflect(rayDir, normal);

    optixTrace(optixLaunchParams.traversable,
        pos,
        reflexoDir,
        0.00001f, // tmin
        1e20f, // tmax
        0.0f, // rayTime
        OptixVisibilityMask( 255 ),
        OPTIX_RAY_FLAG_NONE,
        PHONG_RAY_TYPE, // SBT offset
        RAY_TYPE_COUNT, // SBT stride
        PHONG_RAY_TYPE, // missSBTIndex
        u0, u1 );

    // Cor da Transmissão

    float3 transmissaoPRD = make_float3(1.f);
    uint32_t u0_2, u1_2;
    packPointer( &transmissaoPRD, u0_2, u1_2 );

    optixTrace(optixLaunchParams.traversable,
        pos,
        rayDir,
        0.00001f, // tmin
        1e20f, // tmax
        0.0f, // rayTime
        OptixVisibilityMask( 255 ),
        OPTIX_RAY_FLAG_NONE,
        PHONG_RAY_TYPE, // SBT offset
        RAY_TYPE_COUNT, // SBT stride
        PHONG_RAY_TYPE, // missSBTIndex
        u0_2, u1_2 );
    
    // Valor 
    float R0 = 0.04; // pow((1-1.5)/(1+1.5), 2);

    // Schlick's Approximation
    // Para calcular o valor de Schlick's Approximation a usar no PRD final
    float s = R0 + (1 - R0) * pow(1 - abs(dot(normalize(normal), normalize(rayDir))), 5);
    
    prd = transmissaoPRD * (1 - s) + reflexoPRD * s;
}

extern "C" __global__ void __miss__phong_glass() {
    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(1.0f, 1.0f, 1.0f);
}

//GLASS SHADOW FUNCTIONS

// Nothing to do in here
extern "C" __global__ void __anyhit__shadow_glass() {}

extern "C" __global__ void __closesthit__shadow_glass() {
   // get the payload variable
   float3 &prd = *(float3*)getPRD<float3>();

   // get mesh data
   const TriangleMeshSBTData &sbtData
       = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

   // retrieve primitive id and indexes
   const int   primID = optixGetPrimitiveIndex();
   const uint3 index  = sbtData.index[primID];

   // get barycentric coordinates
   const float u = optixGetTriangleBarycentrics().x;
   const float v = optixGetTriangleBarycentrics().y;

   float4 pos4 = (1.f-u-v) * sbtData.vertexD.position[index.x]
       + u * sbtData.vertexD.position[index.y]
       + v * sbtData.vertexD.position[index.z];

   float3 pos = make_float3(pos4.x,pos4.y,pos4.z);

   float4 norm4 = (1.f-u-v) * sbtData.vertexD.normal[index.x]
       + u * sbtData.vertexD.normal[index.y]
       + v * sbtData.vertexD.normal[index.z];

   float3 normal = make_float3(norm4.x,norm4.y,norm4.z);

   float3 ldir = make_float3(0.600,-0.400,0.700);

   const auto &camera=optixLaunchParams.camera;
   const int ix=optixGetLaunchIndex().x;
   const int iy=optixGetLaunchIndex().y;
   const float2 screen(make_float2(ix+.5f,iy+.5f)/make_float2(optixGetLaunchDimensions().x,optixGetLaunchDimensions().y)*2.0-1.0);
   float3 rayDir=normalize(camera.direction+screen.x*camera.horizontal+screen.y*camera.vertical);
   
   // Cor do Reflexo

   float3 PRD = make_float3(0.f);
   uint32_t u0, u1;
   packPointer( &PRD, u0, u1 );

   float3 reflexoDir = reflect(rayDir, normal);

   optixTrace(optixLaunchParams.traversable,
       pos,
       -ldir,
       0.00001f, // tmin
       1e20f, // tmax
       0.0f, // rayTime
       OptixVisibilityMask( 255 ),
       OPTIX_RAY_FLAG_NONE,
       SHADOW_RAY_TYPE, // SBT offset
       RAY_TYPE_COUNT, // SBT stride
       SHADOW_RAY_TYPE, // missSBTIndex
       u0, u1 );

    prd = PRD;
}

extern "C" __global__ void __miss__shadow_glass() {
    float3 &prd = *(float3*)getPRD<float3>();
    // set blue as background color
    prd = make_float3(1.0f, 0.0f, 0.0f);
}

extern "C" __global__ void __raygen__renderFrame() {

    const int ix = optixGetLaunchIndex().x;
    const int iy = optixGetLaunchIndex().y;
    const auto &camera = optixLaunchParams.camera;  

    // ray payload
    float3 pixelColorPRD = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );  

    // compute ray direction
    // normalized screen plane position, in [-1, 1]^2
    const float2 screen(make_float2(ix+.5f,iy+.5f)
            / make_float2(optixGetLaunchDimensions().x, optixGetLaunchDimensions().y) * 2.0 - 1.0);

    // note: nau already takes into account the field of view when computing 
    // camera horizontal and vertival
    float3 rayDir = normalize(camera.direction
            + screen.x  * camera.horizontal
            + screen.y * camera.vertical);

    // trace primary ray
    optixTrace(optixLaunchParams.traversable,
            camera.position,
            rayDir,
            0.f,    // tmin
            1e20f,  // tmax
            0.0f,   // rayTime
            OptixVisibilityMask( 255 ),
            OPTIX_RAY_FLAG_NONE,
            PHONG_RAY_TYPE,             // SBT offset
            RAY_TYPE_COUNT,             // SBT stride
            PHONG_RAY_TYPE,             // missSBTIndex 
            u0, u1 );

    //convert float (0-1) to int (0-255)
    const int r = int(255.0f*pixelColorPRD.x);
    const int g = int(255.0f*pixelColorPRD.y);
    const int b = int(255.0f*pixelColorPRD.z);

    // convert to 32-bit rgba value 
    const uint32_t rgba = 0xff000000
        | (r<<0) | (g<<8) | (b<<16);
    // compute index
    const uint32_t fbIndex = ix+iy*optixGetLaunchDimensions().x;
    // write to output buffer
    optixLaunchParams.frame.colorBuffer[fbIndex] = rgba;
}
