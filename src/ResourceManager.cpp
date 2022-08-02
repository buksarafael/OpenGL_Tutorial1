#include <ResourceManager.h>
ResourceManager::ResourceManager(){}

std::shared_ptr<ShadersProgram>
ResourceManager::createShader(const std::string shaderName){
    if(m_ShaderMap.count(shaderName))
        return m_ShaderMap[shaderName];
    std::shared_ptr<ShadersProgram> s;
    load_shaders(shaderName,s);
    m_ShaderMap.insert(std::make_pair(shaderName,s));
    return s;
}
std::shared_ptr<Texture> 
ResourceManager::getTexture(const std::string textureName){
    if(m_TexMap.count(textureName))
        return m_TexMap[textureName];
    std::shared_ptr<Texture> t;
    load_textures(textureName,t);
    m_TexMap.insert(std::make_pair(textureName,t));
    return t;
}

void ResourceManager::load_shaders(const std::string name,std::shared_ptr<ShadersProgram> &s){
    auto path = m_Shaders+name;
    auto v_path=path+".vs";
    auto f_path=path+".fs";

    auto shader = std::make_shared<ShadersProgram>();
    if(!shader->create(v_path.c_str(),f_path.c_str())){
        std::cout<<"Error creating shaders!"<<std::endl;
    }
    s=shader;
}

void ResourceManager::load_textures(const std::string name,std::shared_ptr<Texture>&t){
    auto path = m_Textures + name;
    auto texture = std::make_shared<Texture>(path.c_str());
    if(!texture->load()){
        std::cout<<"Error loading texture"<<std::endl;
    }
    t=texture;
}