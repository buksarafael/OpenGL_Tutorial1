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
#include <RenderingQueue.h>

class Engine : public Application{
private:
    Camera m_Camera;
    Pipeline m_Model;
    ResourceManager m_ResourceManager;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<VertexLayout> m_VertexLayout;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<ShadersProgram> m_Shader;
    std::shared_ptr<Texture> m_Texture;
    RenderingQueue m_RenderQueue;
private:
void initBuffer();
void initShaders();
void initTexture();
void initModel();
void initCamera();
void key_callback(Application *App,int key);
void window_callback(Application *App, int width,int height);
void render();
ResourceManager &getResourceManager();
public:
Engine()=default;
bool initialize(const char* window_name, int width,int height);
};