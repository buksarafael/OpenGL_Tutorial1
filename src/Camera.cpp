#include <Camera.h>
Camera::Camera(){
    m_position = Vector3f(2.0f,2.0f,2.0f);
    m_target   = Vector3f(0.0f,0.0f,0.0f);
    m_up       = Vector3f(0.0f,1.0f,0.0f);
}
void Camera::SetPosition(float x,float y,float z){
    m_position.x=x;
    m_position.y=y;
    m_position.z=z;
}
void Camera::SetPosition(Vector3f pos){
    m_position.x=pos.x;
    m_position.y=pos.y;
    m_position.z=pos.z;
}
void Camera::LookAt(const Vector3f &Target,const Vector3f &Pos){
    m_position=Pos;
    m_target=Target;
}
void Camera::Move(Vector3f distance){
    m_position+=distance;
}
Matrix4f Camera::getViewMatrix(){
    m_ViewMatrix.InitCameraTransform(m_position,m_target,m_up);
    return m_ViewMatrix;
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
Matrix4f Camera::getProjectionMatrix(){
    return m_ProjectionMatrix;
}
Vector3f Camera::getPosition(){
    return m_position;
}
Vector3f Camera::getTarget(){
    return m_target;
}
void Camera::UpdatePerspective(int width,int height){
//    m_perspective.Width=width;
//    m_perspective.Height=height;
    setProjection(width, height);
}
Vector3f Camera::OnKeyboard(int key,Vector3f camera_pos,Vector3f camera_target){
    Vector3f distance = Vector3f(0.0f,0.0f,0.0f);
    Vector3f toTarget=camera_target-camera_pos;
    //toTarget.z=0.0f;
    toTarget.Normalize();
    switch(key){
        case GLFW_KEY_UP:{
            distance+=toTarget;
            break;
        }
        case GLFW_KEY_DOWN:{
            distance-=toTarget;
        }
            break;
        case GLFW_KEY_LEFT:{
            Vector3f Left=toTarget.Cross(Vector3f(0.0f,1.0f,0.0f));
            Left.Normalize();
            //Left*=m_speed;
            distance+=Left;
        }
            break;
        case GLFW_KEY_RIGHT:{
            Vector3f Right=Vector3f(0.0f,1.0f,0.0f).Cross(toTarget);
            Right.Normalize();
            //Right*=m_speed;
            distance+=Right;
        }
            break;
        case GLFW_KEY_PAGE_UP:
            distance=Vector3f(0.0f,1.0f,0.0f);
            break;
        case GLFW_KEY_PAGE_DOWN:
            distance=Vector3f(0.0f,-1.0f,0.0f);
            break;
    }
    std::cout<<"Target("<<m_target.x<<","<<m_target.y<<","<<m_target.z<<")"<<std::endl;
    std::cout<<"Position("<<m_position.x<<","<<m_position.y<<","<<m_position.z<<")"<<std::endl<<std::endl;
    return distance;
}
