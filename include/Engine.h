#pragma once
#include <OpenGL/gl3.h>
#include <Application.h>
#include <Camera.h>
#include <iostream>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <IndexBuffer.h>
#include <ResourceManager.h>
#include <Pipeline.h>
#include <Terrain.h>
#include <HeightMap.h>
#include <RenderingQueue.h>

class Engine : public Application{
private:
    Camera m_Camera;
    Pipeline m_Model;
    RenderingQueue m_RenderQueue;
    std::shared_ptr<HeightMap> m_HeightMap;
    std::shared_ptr<Terrain> m_Terrain;
    Vector2f m_Mouse;
    // ResourceManager m_ResourceManager;
    // std::shared_ptr<VertexBuffer> m_VertexBuffer;
    // std::shared_ptr<VertexLayout> m_VertexLayout;
    // std::shared_ptr<IndexBuffer> m_IndexBuffer;
    // std::shared_ptr<ShadersProgram> m_Shader;
    // std::shared_ptr<Texture> m_Texture;
private:
void initModel();
void initCamera();
void initTerrain();
void cursor_callback();
void window_callback(int Width,int Height) override;
void update(const InputState &input_state, const float delta_time) override;
void render() override;

public:
Engine()=default;
Engine &operator=(const Engine &) = delete;
bool initialize(const char *window_name, std::size_t width,std::size_t height);
void before_run(InputState &input_state) override;
};