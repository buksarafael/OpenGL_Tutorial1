#include <Pipeline.h>
Pipeline::Pipeline(){
    m_scale=Vector3f(1.0f,1.0f,1.0f);
    m_worldPos=Vector3f(0.0f,0.0f,0.0f);
    m_rotateInfo=Vector3f(0.0f,0.0f,0.0f);
}
void Pipeline::SetScale(float ScaleX,float ScaleY,float ScaleZ){
    m_scale.x=ScaleX;
    m_scale.y=ScaleY;
    m_scale.z=ScaleZ;
}
void Pipeline::SetScale(float s){
    SetScale(s,s,s);
}
void Pipeline::SetScale(Vector3f& scale){
    SetScale(scale.x,scale.y,scale.z);
}
void Pipeline::SetWorldPos(float x,float y, float z){
    m_worldPos.x=x;
    m_worldPos.y=y;
    m_worldPos.z=z;
}
void Pipeline::SetWorldPos(const Vector3f& Pos){
    m_worldPos=Pos;
}
void Pipeline::SetRotation(float RotateX, float RotateY, float RotateZ){
    m_rotateInfo.x=RotateX;
    m_rotateInfo.y=RotateY;
    m_rotateInfo.z=RotateZ;
}
void Pipeline::SetRotation(const Vector3f& r){
    SetRotation(r.x,r.y,r.z);
}

void Pipeline::Rotate(float RotateX,float RotateY,float RotateZ){
    m_rotateInfo.x+=RotateX;
    m_rotateInfo.y+=RotateY;
    m_rotateInfo.z+=RotateZ;
}

void Pipeline::Rotate(const Vector3f r){
    Rotate(r.x,r.y,r.z);
}

void Pipeline::InitScaleTransform(Matrix4f &ScaleTrans){
    ScaleTrans=Matrix4f(m_scale.x,0.0f     ,0.0f     ,0.0f,
                        0.0f     ,m_scale.y,0.0f     ,0.0f,
                        0.0f     ,0.0f     ,m_scale.z,0.0f,
                        0.0f     ,0.0f     ,0.0f     ,1.0f);
}

const Matrix4f Pipeline::GetTrans(){
    Matrix4f ScaleTrans,RotateTrans,TranslationTrans;

    InitScaleTransform(ScaleTrans);
    RotateTrans.InitRotateTransform(m_rotateInfo.x,m_rotateInfo.y,m_rotateInfo.z);
    TranslationTrans.InitTranslationTransform(m_worldPos);
    
    this->m_transformation=TranslationTrans*RotateTrans*ScaleTrans;
    return this->m_transformation;
}
