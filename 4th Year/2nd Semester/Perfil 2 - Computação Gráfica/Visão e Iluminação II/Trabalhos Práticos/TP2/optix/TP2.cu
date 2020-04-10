#include <optix.h>
#include "random.h"
#include "LaunchParams7.h" // our launch params
#include "vec_math.h" // NVIDIAs math utils


extern "C" {
    __constant__ LaunchParams optixLaunchParams;
}
//  a single ray type
enum { PHONG=0, SHADOW, RAY_TYPE_COUNT };

struct colorPRD {
    float3 color;
    unsigned int seed;
} ;

struct shadowPRD {
    float shadowAtt;
    unsigned int seed;
} ;

// -------------------------------------------------------
// closest hit computes color based lolely on the triangle normal
extern "C" __global__ void __closesthit__radiance() {
    
    colorPRD &prd = *(colorPRD*)getPRD<colorPRD>();
    
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
    float3 nn = normalize(make_float3(n));
    
    // intersection position
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax()*optixGetWorldRayDirection();
    
    // Ambient Occlusion
    int numRays = 4;
    float ambientOcclusion = 0;
    shadowPRD AOPRD;
    AOPRD.shadowAtt = 1.0f;
    AOPRD.seed = prd.seed;
    
    uint32_t u0, u1;
    packPointer(&AOPRD, u0, u1);
    
    for (int i = 0; i < numRays; ++i) {
        const float z1 = rnd(prd.seed);
        const float z2 = rnd(prd.seed);
        
        float3 rayDir, p;
        
        // Uniform hemisphere sampling
        // p.y = z1;
        // float k = sqrt(1-pow(p.y, 2));
        // float beta = 2 * M_PIf * z2;
        // p.x = k * sin(beta);
        // p.z = k * cos(beta);
        
        // cosine weighted hemisphere sampling
        float r = sqrt(z1);
        float beta = 2 * M_PIf * z2;
        p.x = r * sin(beta);
        p.z = r * cos(beta);
        p.y = sqrt(1-pow(r,2));

        // Converting from sampling to world space
        float3 t;
        float3 c1 = cross(nn, make_float3(0.0, 0.0, 1.0));
        float3 c2 = cross(nn, make_float3(0.0, 1.0, 0.0));
        
        if( length(c1) > length(c2) ) {
            t = c1;
        }
        else {
            t = c2;
        }
        normalize(t);
        float3 b = cross(t, nn);
        rayDir = p.x * b + p.y * nn + p.z * t;
        
        // trace ambient occlusion
        optixTrace(optixLaunchParams.traversable,
                   pos,
                   rayDir,
                   0.00001f,    // tmin
                   0.5f,        // tmax
                   0.0f,        // rayTime
                   OptixVisibilityMask( 255 ),
                   OPTIX_RAY_FLAG_NONE,
                   SHADOW,             // SBT offset
                   RAY_TYPE_COUNT,     // SBT stride
                   SHADOW,             // missSBTIndex 
                   u0, u1);
        
        ambientOcclusion += AOPRD.shadowAtt;
    }
    
    prd.color = make_float3(ambientOcclusion / numRays);
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
    // ray payload
    colorPRD &prd = *(colorPRD*)getPRD<colorPRD>();
    
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
       
    colorPRD afterPRD;
    afterPRD.color = make_float3(1.0f);
    afterPRD.seed = prd.seed;
    uint32_t u0, u1;
    packPointer( &afterPRD, u0, u1 );  
    
    const float3 pos = optixGetWorldRayOrigin() + optixGetRayTmax()*optixGetWorldRayDirection();
    
    float3 rayDir = reflect(optixGetWorldRayDirection(), normal);
    optixTrace(optixLaunchParams.traversable,
               pos,
               rayDir,
               0.04f,    // tmin is high to void self-intersection
               1e20f,  // tmax
               0.0f,   // rayTime
               OptixVisibilityMask( 255 ),
               OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
               PHONG,             // SBT offset
               RAY_TYPE_COUNT,     // SBT stride
               PHONG,             // missSBTIndex 
               u0, u1 );
    
    prd.color = make_float3(0.8,0.8,0.8) * afterPRD.color;
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
    // ray payload 
    colorPRD &prd = *(colorPRD*)getPRD<colorPRD>();
    
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
    
    colorPRD refractPRD;
    refractPRD.color = make_float3(0.0f);
    refractPRD.seed = prd.seed;
    uint32_t u0, u1;
    packPointer( &refractPRD, u0, u1 );  
    
    if (length(rayDir) > 0)
        optixTrace(optixLaunchParams.traversable,
                   pos,
                   rayDir,
                   0.00001f,    // tmin
                   1e20f,       // tmax
                   0.0f,        // rayTime
                   OptixVisibilityMask( 255 ),
                   OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
                   PHONG,               // SBT offset
                   RAY_TYPE_COUNT,      // SBT stride
                   PHONG,               // missSBTIndex 
                   u0, u1 );
        
        
    colorPRD reflectPRD;
    reflectPRD.color = make_float3(0.0f);
    reflectPRD.seed = prd.seed;
    if (dotP > 0) {
        float3 reflectDir = reflect(normRayDir, normal);        
        packPointer( &reflectPRD, u0, u1 );  
        optixTrace(optixLaunchParams.traversable,
                    pos,
                    reflectDir,
                    0.00001f,    // tmin
                    1e20f,       // tmax
                    0.0f,        // rayTime
                    OptixVisibilityMask( 255 ),
                    OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
                    PHONG,               // SBT offset
                    RAY_TYPE_COUNT,      // SBT stride
                    PHONG,               // missSBTIndex 
                    u0, u1 );
        float r0 = (1.5f - 1.0f)/(1.5f + 1.0f);
        r0 = r0*r0 + (1-r0*r0) * pow(1-dotP,5);
        prd.color =  refractPRD.color * (1-r0) + r0*reflectPRD.color;
    }
    else
        prd.color =  refractPRD.color ;
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
               1e20f,     // tmax
               0.0f,      // rayTime
               OptixVisibilityMask( 255 ),
               OPTIX_RAY_FLAG_NONE, //OPTIX_RAY_FLAG_NONE,
               SHADOW,              // SBT offset
               RAY_TYPE_COUNT,      // SBT stride
               SHADOW,              // missSBTIndex 
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
    
    
    if (optixLaunchParams.frame.frame == 0 && ix == 0 && iy == 0) {
        
        // print info to console
        printf("===========================================\n");
        printf("Nau Ray-Tracing Debug\n");
        const float4 &ld = optixLaunchParams.global->lightPos;
        printf("LightPos: %f, %f %f %f\n", ld.x,ld.y,ld.z,ld.w);
        printf("Launch dim: %u %u\n", optixGetLaunchDimensions().x, optixGetLaunchDimensions().y);
        printf("Rays per pixel squared: %d \n", optixLaunchParams.frame.raysPerPixel);
        printf("===========================================\n");
    }
    
    
    // ray payload
    colorPRD pixelColorPRD;
    pixelColorPRD.color = make_float3(1.f);
    uint32_t u0, u1;
    packPointer( &pixelColorPRD, u0, u1 );  
    
    float raysPerPixel = float(optixLaunchParams.frame.raysPerPixel);
    // half pixel
    float2 delta = make_float2(1.0f/raysPerPixel, 1.0f/raysPerPixel);
    
    // compute ray direction
    // normalized screen plane position, in [-1, 1]^2
    
    float red = 0.0f, blue = 0.0f, green = 0.0f;
    for (int i = 0; i < raysPerPixel; ++i) {
        for (int j = 0; j < raysPerPixel; ++j) {
            float2 subpixel_jitter;
            uint32_t seed = tea<4>( ix * optixGetLaunchDimensions().x + iy, i*raysPerPixel + j );
            pixelColorPRD.seed = seed;

            subpixel_jitter = make_float2( rnd( seed )-0.5f, rnd( seed )-0.5f );
            
            const float2 screen(make_float2(ix + subpixel_jitter.x, iy + subpixel_jitter.y)
            / make_float2(optixGetLaunchDimensions().x, optixGetLaunchDimensions().y) * 2.0 - 1.0);
            
            // note: nau already takes into account the field of view and ratio when computing 
            // camera horizontal and vertival
            float3 rayDir = normalize(camera.direction
            + (screen.x ) * camera.horizontal
            + (screen.y ) * camera.vertical);
            
            // trace primary ray
            optixTrace(optixLaunchParams.traversable,
                       camera.position,
                       rayDir,
                       0.f,    // tmin
                       1e20f,  // tmax
                       0.0f,   // rayTime
                       OptixVisibilityMask( 255 ),
                       OPTIX_RAY_FLAG_NONE, //,OPTIX_RAY_FLAG_DISABLE_ANYHIT
                       PHONG,               // SBT offset
                       RAY_TYPE_COUNT,      // SBT stride
                       PHONG,               // missSBTIndex 
                       u0, u1 );
            
            red += pixelColorPRD.color.x / (raysPerPixel*raysPerPixel);
            green += pixelColorPRD.color.y / (raysPerPixel*raysPerPixel);
            blue += pixelColorPRD.color.z / (raysPerPixel*raysPerPixel);
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


