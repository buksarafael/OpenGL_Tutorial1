#pragma once
#include <Math3D.h>
#include <iostream>
#include <GLFW/glfw3.h>
class Camera{
    public:
    Camera();
    public:
    //setters
    void LookAt(const Vector3f &Target,const Vector3f &Pos);
    void LookAt(float x, float y, float z);
    void Move(Vector3f distance);
    void SetPosition(float x,float y, float z);
    void SetPosition(Vector3f pos);
    void UpdatePerspective(int width,int height);
    void setProjection(PersProjInfo &p);
    void setProjection(float width,float height);
    //getters
    // const Vector3f getPosition() const;
    const Vector3f getTarget() const;
    const Matrix4f getProjectionMatrix() const;
    const Matrix4f getViewMatrix() const;
    const float getYaw() const;


    void onYaw(float rad);
    void onPitch(float rad);
    void updateCamera();
    void moveUp(const double speed);
    void moveSide(const double speed);
    void moveForward(const double speed);

    private:
    Vector3f m_target;
    Vector3f m_up;
    float m_yaw;
    float m_pitch;
    PersProjInfo m_perspective;
    Matrix4f m_ProjectionMatrix;
    Matrix4f m_ViewMatrix;
    //Vector3f m_position;
    float m_FOV=90.f;
    float m_zNear=1.0f;
    float m_zFar=1000000.0f;
    float m_Distance=200.0f;
};
