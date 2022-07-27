#pragma once
#include <Math3D.h>
#include <iostream>
class Pipeline{
    public:
    Pipeline();

    public:
    void SetScale(float ScaleX, float ScaleY, float ScaleZ);
    void SetScale(float s);
    void SetScale(Vector3f& scale);
    void SetWorldPos(float x, float y, float z);
    void SetWorldPos(const Vector3f& Pos);
    void SetRotation(float RotateX, float RotateY, float RotateZ);
    void SetRotation(const Vector3f& r);
    void Rotate(float RotateX,float RotateY,float RotateZ);
    void Rotate(const Vector3f r);
    void InitScaleTransform(Matrix4f &ScaleTrans);
    const Matrix4f GetTrans();

    private:
    Vector3f m_scale;
    Vector3f m_worldPos;
    Vector3f m_rotateInfo;
    Matrix4f m_transformation;
};