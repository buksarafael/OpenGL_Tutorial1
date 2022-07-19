#include <UniformHelper.h>
struct UniformData{
    UniformData();
    std::array<std::pair<const char*,Uniform>,(std::size_t)Uniform::Count> uniforms;
};

UniformData::UniformData(){
    uniforms = std::array<std::pair<const char*,Uniform>, (std::size_t)Uniform::Count>
    {
        std::pair<const char*,Uniform>{"Offset",Uniform::Offset},
        std::pair<const char*,Uniform>{"Model",Uniform::Model},
        std::pair<const char*,Uniform>{"View",Uniform::View},
        std::pair<const char*,Uniform>{"Projection",Uniform::Projection},
        std::pair<const char*,Uniform>{"MVP",Uniform::MVP},
        std::pair<const char*,Uniform>{"Texture",Uniform::Texture}
    };
}

UniformData& getUniforms(){
    static UniformData data;
    return data;
}

const char* UniformHelper::getName(Uniform uniform){
    for(const auto& pair : getUniforms().uniforms){
        if(pair.second==uniform){
            return pair.first;
        }
    }
}
