#include <Terrain.h>
#include <PerlinNoise.h>
#include <cstdlib>

Terrain::Terrain(){
    m_vBuff = std::make_shared<VertexBuffer>();
    m_iBuff = std::make_shared<IndexBuffer>();
    m_vLay = std::make_shared<VertexLayout>();

    m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kPosition,3);
    m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kUV,2);
    m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kNormal,3);

    m_WaterVerBuff = std::make_shared<VertexBuffer>();
    m_WaterIndBuff = std::make_shared<IndexBuffer>();
    m_WaterLayout = std::make_shared<VertexLayout>();

    m_WaterLayout->AddVertexAttribute(AttributeHelper::AttributeType::kPosition,2);
}

void Terrain::initResources(ResourceManager *resource_manager){
    m_GrassTex = resource_manager->getTexture("grass.jpeg");
    m_Rock1Tex = resource_manager->getTexture("rock1.jpeg");
    m_Rock2Tex = resource_manager->getTexture("rock2.jpeg");
    m_SnowTex = resource_manager->getTexture("snow.jpeg");
    m_SplatMap = resource_manager->getTexture("splatmap.tga");
    m_TerrainShader = resource_manager->createShader("terrain_shader");
    m_WaterShader = resource_manager->createShader("water_shader");
    BlendingState water_blending;
    water_blending.enabled=true;
    water_blending.source_func=BlendingFunc::SRC_ALPHA;
    water_blending.dest_func=BlendingFunc::ONE_MINUS_SRC_ALPHA;
    m_WaterShader->setBlendingState(water_blending);
}

void Terrain::generate(){
    generateTerrain();
    generateWater();
}

void Terrain::loadHeightMap(std::shared_ptr<HeightMap> height_map){
    m_hMap=height_map;
    m_Width=m_hMap->getWidth();
    m_Height=m_hMap->getHeight();
}
Vector3f Terrain::getNormal(std::size_t x,std::size_t y){
    float hL = m_hMap->getHeight(x-1,y);
    float hR = m_hMap->getHeight(x+1,y);
    float hD = m_hMap->getHeight(x,y-1);
    float hU = m_hMap->getHeight(x,y+1);

    Vector3f normal;
    normal.x=hL-hR;
    normal.y=hD-hU;
    normal.z=0.01f;
    normal = normal.Normalize();
    return normal;
}
float Terrain::getWidth(){
    return m_Width*m_Step;
}
float Terrain::getHeight(){
    return m_Height*m_Step;
}

void Terrain::generateTerrain(){
    struct Vertex{
        Vector3f position;
        Vector2f UV;
        Vector3f normal;
    };

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    const siv::PerlinNoise::seed_type seed =rand() %10000;
    const siv::PerlinNoise perlin{seed};

    for(std::size_t y=0;y<m_Height;y++){
        for(std::size_t x=0;x<m_Width;x++){
            float map_height = m_hMap->getHeight(x,y) * 60.0f;
            //float map_height = (perlin.octave2D_01(x*0.01,y*0.01,4)*150.0f)-30.0f;
            Vertex v;
            v.position=Vector3f{(float)x*m_Step,(float)y*m_Step,map_height*m_Step};
            v.UV=Vector2f{float(x)/m_Width,float(y)/m_Height};
            v.normal=getNormal(x,y);
            vertices.push_back(v);
        }
    }
    
    for(std::size_t y=0;y<m_Height-1;y++){
        for(std::size_t x=0;x<m_Width-1;x++){
            indices.push_back(y * m_Width + x);
            indices.push_back(y * m_Width + x + 1);
            indices.push_back((y + 1) * m_Width + x);
            indices.push_back(y * m_Width + x + 1);
            indices.push_back((y + 1) * m_Width + x + 1);
            indices.push_back((y + 1) * m_Width + x);
        }
    }
    
    m_vBuff->create(vertices.data(),*m_vLay,vertices.size());
    m_iBuff->create(*m_vBuff,indices.data(),indices.size());
}
void Terrain::generateWater(){
    float width=m_Width * m_Step;
    float height=m_Height * m_Step;
    float vertices[]={0.0f,0.0f,0.0f,
                      (float) height,(float)width,0.0f,
                      (float)width,(float) height};
    uint32_t indices[]={0,1,2,1,2,3};
    m_WaterVerBuff->create(vertices,*m_WaterLayout,4);
    m_WaterIndBuff->create(*m_WaterVerBuff,indices,6);
}

void Terrain::createTerrainPacket(RenderingQueue *render_queue,const Matrix4f &mvp){
    std::size_t topology_size = 3;
    auto *tex=render_queue->create_texture(nullptr,m_GrassTex.get(),UniformHelper::UniformType::kTexture0);
    tex=render_queue->create_texture(tex,m_Rock1Tex.get(),UniformHelper::UniformType::kTexture1);
    tex=render_queue->create_texture(tex,m_Rock2Tex.get(),UniformHelper::UniformType::kTexture2);
    tex=render_queue->create_texture(tex, m_SnowTex.get(),UniformHelper::UniformType::kTexture3);
    tex=render_queue->create_texture(tex,m_SplatMap.get(),UniformHelper::UniformType::kSplatMapTexture);

    RenderPacket packet;
    packet.vbuff=m_vBuff.get();
    packet.ibuff=m_iBuff.get();
    packet.shader=m_TerrainShader.get();
    packet.topology=GL_TRIANGLES;
    packet.primitive_start=0;
    packet.primitive_end=m_iBuff->getSize()/topology_size;
    packet.first_texture=tex;
    packet.first_uniform = render_queue->create_uniform(nullptr,UniformHelper::UniformType::kMVP,mvp);
    render_queue->push_rendering_packet(packet);
}

void Terrain::createWaterPacket(RenderingQueue *render_queue,const Matrix4f &mvp){
    size_t topology_size=3;
    RenderPacket packet;
    packet.vbuff = m_WaterVerBuff.get();
    packet.ibuff = m_WaterIndBuff.get();
    packet.shader = m_WaterShader.get();
    packet.topology = GL_TRIANGLES;
    packet.primitive_start = 0;
    packet.primitive_end = m_WaterIndBuff->getSize() / topology_size;
    packet.first_texture = nullptr;
    packet.first_uniform = render_queue->create_uniform(nullptr, UniformHelper::UniformType::kMVP, mvp);
    render_queue->push_rendering_packet(packet);
}
void Terrain::createRenderPackets(RenderingQueue &render_queue,const Camera &camera){
    Matrix4f mvp = camera.getProjectionMatrix()*camera.getViewMatrix();
    createTerrainPacket(&render_queue,mvp);
    createWaterPacket(&render_queue,mvp);
}
