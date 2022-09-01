#pragma once
#include <array>
#include <iostream>

struct UniformHelper{
enum UniformType{
    kOffset=0,
    kMVP,
    kTexture0,
    kTexture1,
    kTexture2,
    kTexture3,
    kTexture4,
    kSplatMapTexture,

    kUniformCount
};
    static const char* getUniformName(const UniformType u);
    static UniformType getUniformType(const char *uniform_name);
};