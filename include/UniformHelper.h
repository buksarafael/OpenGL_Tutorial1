#pragma once
#include <array>
#include <iostream>

struct UniformData;
enum Uniform{
    uOffset=0,
    uModel,
    uView,
    uProjection,
    uMVP,
    uTexture,

    Count
};
struct UniformHelper{
    public:
        static const char* getName(Uniform);
};