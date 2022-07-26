#include <Pipeline.h>
Pipeline::Pipeline(int width,int height){
    m_scale=Vector3f(1.0f,1.0f,1.0f);
    m_worldPos=Vector3f(0.0f,0.0f,0.0f);
    m_rotateInfo=Vector3f(0.0f,0.0f,0.0f);
    m_perspective.FOV=90.0f;
    m_perspective.zNear=0.0f;
    m_perspective.zFar=100.0f;
    m_perspective.Width=width;
    m_perspective.Height=height;
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
void Pipeline::UpdatePerspective(int width,int height){
    m_perspective.Width=width;
    m_perspective.Height=height;
}
void Pipeline::InitScaleTransform(Matrix4f &ScaleTrans){
    ScaleTrans=Matrix4f(m_scale.x,0.0f     ,0.0f     ,0.0f,
                        0.0f     ,m_scale.y,0.0f     ,0.0f,
                        0.0f     ,0.0f     ,m_scale.z,0.0f,
                        0.0f     ,0.0f     ,0.0f     ,1.0f);
}

const Matrix4f Pipeline::GetTrans(){
    Matrix4f ScaleTrans,RotateTrans,TranslationTrans,ProjectionTrans;

    InitScaleTransform(ScaleTrans);
    RotateTrans.InitRotateTransform(m_rotateInfo.x,m_rotateInfo.y,m_rotateInfo.z);
    TranslationTrans.InitTranslationTransform(m_worldPos);
    ProjectionTrans.InitPersProjTransform(m_perspective);
    
    this->m_transformation=ProjectionTrans*TranslationTrans*RotateTrans*ScaleTrans;
    return this->m_transformation;
}
