//////////////////////////////////////////////////////////////

// http://mrl.nyu.edu/~perlin/noise/
// Adapting from PApplet.java
// which was adapted from toxi
// which was adapted from the german demo group farbrausch
// as used in their demo "art": http://www.farb-rausch.de/fr010src.zip

// someday we might consider using "improved noise"
// http://mrl.nyu.edu/~perlin/paper445.pdf
// See: https://github.com/shiffman/The-Nature-of-Code-Examples-p5.js/
//      blob/main/introduction/Noise1D/noise.js


#include "PerlinNoise.h"

float PerlinNoise::noise(float x, float y, float z){
    
    if (perlin.empty())
        for(int i = 0; i < PERLIN_SIZE + 1; i++)
            perlin.push_back((float)std::rand() / (float)RAND_MAX);
    
    if(x < 0) x = -x;
    if(y < 0) y = -y;
    if(z < 0) z = -z;
    
    int xi = floor(x);
    int yi = floor(y);
    int zi = floor(z);
    
    float xf = x - xi;
    float yf = y - yi;
    float zf = z - zi;
    
    float rxf;
    float ryf;
    
    float r = 0;
    float amplitude = 0.5;
    
    float n1;
    float n2;
    float n3;
    
    for(int i = 0; i < mOctaves; i++){
        
        int of = xi + (yi << PERLIN_YWRAPB) + (zi << PERLIN_ZWRAPB);
        
        rxf = 0.5 * (1.0 - cos(xf * M_PI));
        ryf = 0.5 * (1.0 - cos(yf * M_PI));
        
        n1 = perlin[of & PERLIN_SIZE];
        n1 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n1);
        n2 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
        n2 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n2);
        n1 += ryf * (n2 - n1);

        of += PERLIN_ZWRAP;
        n2 = perlin[of & PERLIN_SIZE];
        n2 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n2);
        n3 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
        n3 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n3);
        n2 += ryf * (n3 - n2);
        
        n1 += 0.5 * (1.0 - cos(zf * M_PI)) * (n2 - n1);
        
        r += n1 * amplitude;
        amplitude *= mFalloff;
        
        xi <<= 1;
        yi <<= 1;
        zi <<= 1;
        
        xf *= 2;
        yf *= 2;
        zf *= 2;
        
        if (xf >= 1.0) {
              xi++;
              xf--;
        }
        if (yf >= 1.0) {
              yi++;
              yf--;
        }
        if (zf >= 1.0) {
              zi++;
              zf--;
        }
    }
    return r;
}

void PerlinNoise::noiseDetail(int octaves, float falloff){
    
    if(octaves > 0) mOctaves = octaves;
    if(falloff > 0) mFalloff = falloff;
}

void PerlinNoise::noiseSeed(u_int32_t seed){
    std::minstd_rand lcg(seed);
    for(int i = 0; i < PERLIN_SIZE + 1; i++)
        perlin.push_back((float)lcg() / (float)lcg._Max);
}
