#include <Pipeline.h>
Pipeline::Pipeline(){
    m_scale=Vector3f(1.0f,1.0f,1.0f);
    m_worldPos=Vector3f(0.0f,0.0f,0.0f);
    m_rotateInfo=Vector3f(0.0f,0.0f,0.0f);
}
void Pipeline::Scale(float ScaleX,float ScaleY,float ScaleZ){
    m_scale.x=ScaleX;
    m_scale.y=ScaleY;
    m_scale.z=ScaleZ;
}
void Pipeline::Scale(float s){
    Scale(s,s,s);
}
void Pipeline::Scale(Vector3f& scale){
    Scale(scale.x,scale.y,scale.z);
}
void Pipeline::WorldPos(float x,float y, float z){
    m_worldPos.x=x;
    m_worldPos.y=y;
    m_worldPos.z=z;
}
void Pipeline::WorldPos(const Vector3f& Pos){
    m_worldPos=Pos;
}
void Pipeline::Rotate(float RotateX, float RotateY, float RotateZ){
    m_rotateInfo.x=RotateX;
    m_rotateInfo.y=RotateY;
    m_rotateInfo.z=RotateZ;
}
void Pipeline::Rotate(const Vector3f& r){
    Rotate(r.x,r.y,r.z);
}

void Pipeline::InitScaleTransform(Matrix4f &ScaleTrans){
    ScaleTrans=Matrix4f(m_scale.x,0.0f     ,0.0f     ,0.0f,
                        0.0f     ,m_scale.y,0.0f     ,0.0f,
                        0.0f     ,0.0f     ,m_scale.z,0.0f,
                        0.0f     ,0.0f     ,0.0f     ,1.0f);
}
void Pipeline::InitRotateTransform(Matrix4f &RotateTrans){
    Matrix4f RotateX(1.0f,                  0.0f,                  0.0f,                 0.0f,
                      0.0f,                 cosf(m_rotateInfo.x), -sinf(m_rotateInfo.x), 0.0f,
                      0.0,                  sinf(m_rotateInfo.x),  cosf(m_rotateInfo.x), 0.0f,
                      0.0f,                 0.0f,                  0.0f,                 1.0f);
    Matrix4f RotateY(cosf(m_rotateInfo.y),  0.0f, -sinf(m_rotateInfo.y), 0.0f,
                      0.0f,                 1.0f,                  0.0f, 0.0f,
                      sinf(m_rotateInfo.y), 0.0f,  cosf(m_rotateInfo.y), 0.0f,
                      0.0f,                 0.0f,                  0.0f, 1.0f);
    Matrix4f RotateZ(cosf(m_rotateInfo.z), -sinf(m_rotateInfo.z),  0.0f, 0.0f,
                      sinf(m_rotateInfo.z), cosf(m_rotateInfo.z),  0.0f, 0.0f,
                      0.0,                  0.0f,                  1.0f, 0.0f,
                      0.0f,                 0.0f,                  0.0f, 1.0f);
    RotateTrans=RotateZ*RotateY*RotateX;
}
void Pipeline::InitTranslationTransform(Matrix4f &TranslationTrans){
    TranslationTrans=Matrix4f(1.0f,0.0f,0.0f,m_worldPos.x,
                              0.0f,1.0f,0.0f,m_worldPos.y,
                              0.0f,0.0f,1.0f,m_worldPos.z,
                              0.0f,0.0f,0.0f,1.0f);
}
void Pipeline::InitProjectionTransform(Matrix4f &ProjectionTrans){
    //ProjectionTrans=;
}
bool lmao=0;
const Matrix4f Pipeline::GetTrans(){
    Matrix4f ScaleTrans,RotateTrans,TranslationTrans,ProjectionTrans;
    InitScaleTransform(ScaleTrans);
    InitRotateTransform(RotateTrans);
    InitTranslationTransform(TranslationTrans);
    //InitProjectionTransform(ProjectionTrans);
    this->m_transformation=TranslationTrans*RotateTrans*ScaleTrans;
    return this->m_transformation;
}
