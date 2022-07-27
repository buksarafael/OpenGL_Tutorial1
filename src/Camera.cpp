#include <Camera.h>
Camera::Camera(){
    m_position = Vector3f(0.0f,0.0f,0.0f);
    m_target   = Vector3f(0.0f,0.0f,1.0f);
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
Matrix4f Camera::getProjectionMatrix(){
    return m_ProjectionMatrix;
    
}
void Camera::UpdatePerspective(int width,int height){
    m_perspective.Width=width;
    m_perspective.Height=height;
}
void Camera::OnKeyboard(int key){
    switch(key){
        case GLFW_KEY_UP:{
            m_position+=(m_target*m_speed);
            break;
        }
        case GLFW_KEY_DOWN:{
            m_position-=(m_target*m_speed);
        }
            break;
        case GLFW_KEY_LEFT:{
            Vector3f Left=m_target.Cross(m_up);
            Left.Normalize();
            Left*=m_speed;
            m_position+=Left;
        }
            break;
        case GLFW_KEY_RIGHT:{
            Vector3f Right=m_up.Cross(m_target);
            Right.Normalize();
            Right*=m_speed;
            m_position+=Right;
        }
            break;
        case GLFW_KEY_PAGE_UP:
            //m_target.y+=m_speed;
            m_position.y+=m_speed;
            break;
        case GLFW_KEY_PAGE_DOWN:
            //m_target.y-=m_speed;
            m_position.y-=m_speed;
            break;
        case GLFW_KEY_KP_ADD:
            m_speed+=0.1f;
            std::cout<<"Changed speed to "<<m_speed<<std::endl;
            break;
        case GLFW_KEY_KP_SUBTRACT:{
            m_speed-=0.1f;
            if(m_speed<0.1f){
                m_speed=0.1f;
            }
            std::cout<<"Changed speed to "<<m_speed<<std::endl;
        }
            break;
    }
    std::cout<<"Target("<<m_target.x<<","<<m_target.y<<","<<m_target.z<<")"<<std::endl;
    std::cout<<"Position("<<m_position.x<<","<<m_position.y<<","<<m_position.z<<")"<<std::endl<<std::endl;
}