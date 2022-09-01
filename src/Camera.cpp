#include <Camera.h>
Camera::Camera(){
    // m_position = Vector3f(2.0f,2.0f,2.0f);
    m_target   = Vector3f(0.0f,0.0f,0.0f);
    m_up       = Vector3f(0.0f,0.0f,1.0f);
    m_pitch = 0.0f;
    m_yaw=0.0f;
}
void Camera::SetPosition(float x,float y,float z){
    // m_position.x=x;
    // m_position.y=y;
    // m_position.z=z;
}
void Camera::SetPosition(Vector3f pos){
    // m_position.x=pos.x;
    // m_position.y=pos.y;
    // m_position.z=pos.z;
}
void Camera::LookAt(float x, float y, float z){
    m_target.x=x;
    m_target.y=y;
    m_target.z=z;
}
void Camera::LookAt(const Vector3f &Target,const Vector3f &Pos){
    //m_position=Pos;
    m_target=Target;
}
void Camera::Move(Vector3f distance){
    //m_position+=distance;
}
void Camera::onYaw(float rad){
    m_yaw+=rad;
}
void Camera::onPitch(float rad){
    m_pitch+=rad;
}
void Camera::moveUp(const double speed){
    m_target.z += 100.0f * speed;
}
void Camera::moveSide(const double speed){
    Vector3f dir{0.0f,1.0f,0.0f};
    dir.Rotate(m_yaw,{0.0f,0.0f,1.0f});
    m_target+=(dir*speed)*1000.0f;
}
void Camera::moveForward(const double speed){
    Vector3f dir{1.0f,0.0f,0.0f};
    dir.Rotate(m_pitch,{0.0f,1.0f,0.0f});
    dir.Rotate(m_yaw,{0.0f,0.0f,1.0f});
    dir.z=0;
    dir.Normalize();
    m_target+=dir * speed * 1000.0f;
}
void Camera::updateCamera(){
    Vector3f dir{1.0f,0.0f,0.0f};
    dir.Rotate(-m_pitch,{0.0f,1.0f,0.0f});
    dir.Rotate(m_yaw,{0.0f,0.0f,1.0f});
    m_ViewMatrix.InitCameraTransform(m_target+dir*m_Distance,m_target,m_up);
}
void Camera::setProjection(PersProjInfo &p){
    m_perspective.FOV=p.FOV;
    m_perspective.zNear=p.zNear;
    m_perspective.zFar=p.zFar;
    m_perspective.Width=p.Width;
    m_perspective.Height=p.Height;
    m_ProjectionMatrix.InitPersProjTransform(m_perspective);
}
void Camera::setProjection(float width,float height){
    PersProjInfo p;
    p.FOV=m_FOV;
    p.Height=height;
    p.Width=width;
    p.zFar=m_zFar;
    p.zNear=m_zNear;
    setProjection(p);
}
const Matrix4f Camera::getViewMatrix() const{
    return m_ViewMatrix;
}
const float Camera::getYaw() const{
    return m_yaw;
}
const Matrix4f Camera::getProjectionMatrix() const{
    return m_ProjectionMatrix;
}

const Vector3f Camera::getTarget() const{
    return m_target;
}
void Camera::UpdatePerspective(int width,int height){
    setProjection(width, height);
}
