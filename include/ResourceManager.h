#pragma once
#include <OpenGL/gl3.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <HeightMap.h>

class ResourceManager{
    public:

    ResourceManager();
    std::shared_ptr<ShadersProgram> createShader(const std::string shaderName);
    std::shared_ptr<Texture> getTexture(const std::string textureName);
    std::shared_ptr<HeightMap> getHeightMap(const std::string heightmapName);

    private:
    static inline std::string m_Shaders = "/Users/rafaelb/Desktop/Tutorial1/shaders/";
    static inline std::string m_Textures= "/Users/rafaelb/Desktop/Tutorial1/assets/";
    static inline std::string m_HeightMapPath="/Users/rafaelb/Desktop/Tutorial1/assets/";

    void load_shaders(const std::string shader_file,std::shared_ptr<ShadersProgram>&);
    void load_textures(const std::string texture_file,std::shared_ptr<Texture>&);
    void load_heightmap(const std::string map_file,std::shared_ptr<HeightMap>&);

    std::unordered_map<std::string,std::shared_ptr<Texture>> m_TexMap;
    std::unordered_map<std::string,std::shared_ptr<ShadersProgram>> m_ShaderMap;
    std::unordered_map<std::string,std::shared_ptr<HeightMap>> m_HeightMap;
};