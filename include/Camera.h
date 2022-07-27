#pragma once
#include <Math3D.h>
#include <iostream>
#include <GLFW/glfw3.h>
class Camera{
    public:
    Camera();
    public:
    void LookAt(const Vector3f &Target,const Vector3f &Pos);
    void Move(Vector3f distance);
    void SetPosition(float x,float y, float z);
    void SetPosition(Vector3f pos);
    void UpdatePerspective(int width,int height);
    void setProjection(PersProjInfo &p);
    void OnKeyboard(int key);
    Matrix4f getProjectionMatrix();
    Matrix4f getViewMatrix();

    private:
    PersProjInfo m_perspective;
    Matrix4f m_ProjectionMatrix;
    Matrix4f m_ViewMatrix;
    Vector3f m_position;
    Vector3f m_target;
    Vector3f m_up;
    float m_speed=1.0f;
};