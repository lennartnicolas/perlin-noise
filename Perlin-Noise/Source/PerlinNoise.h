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


#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class PerlinNoise {
    
public:
    PerlinNoise() = default;
    ~PerlinNoise() = default;
    
    float noise(float x, float y = 0, float z = 0);
    void noiseDetail(int octaves = 4, float falloff = 0.5);
    void noiseSeed(u_int32_t seed = 0);
    
private:
    const int PERLIN_YWRAPB = 4;
    const int PERLIN_YWRAP  = 16;
    const int PERLIN_ZWRAPB = 8;
    const int PERLIN_ZWRAP  = 256;
    const int PERLIN_SIZE   = 4095;
    
    std::vector<float> perlin;
    int mOctaves = 4;
    float mFalloff = 0.5;
};

#endif
