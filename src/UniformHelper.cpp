#include <UniformHelper.h>
struct UniformData{
    UniformData();
    std::array<std::pair<const char*,Uniform>,(std::size_t)Uniform::Count> uniforms;
};

UniformData::UniformData(){
    uniforms = std::array<std::pair<const char*,Uniform>, (std::size_t)Uniform::Count>
    {
        std::pair<const char*,Uniform>{"Offset",Uniform::uOffset},
        std::pair<const char*,Uniform>{"Model",Uniform::uModel},
        std::pair<const char*,Uniform>{"View",Uniform::uView},
        std::pair<const char*,Uniform>{"Projection",Uniform::uProjection},
        std::pair<const char*,Uniform>{"MVP",Uniform::uMVP},
        std::pair<const char*,Uniform>{"Texture",Uniform::uTexture}
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
