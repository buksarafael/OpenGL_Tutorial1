#pragma once
#include <array>
#include <iostream>

struct UniformData;
enum Uniform{
    Offset=0,
    Model,
    View,
    Projection,
    MVP,
    Texture,

    Count
};
struct UniformHelper{
    public:
        static const char* getName(Uniform);
};
