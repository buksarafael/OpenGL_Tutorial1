#pragma once
#include <Math3D.h>
#include <iostream>
class Pipeline{
    public:
    Pipeline();

    public:
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void Scale(float s);
    void Scale(Vector3f& scale);
    void WorldPos(float x, float y, float z);
    void WorldPos(const Vector3f& Pos);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    void Rotate(const Vector3f& r);
    void InitScaleTransform(Matrix4f &ScaleTrans);
    void InitRotateTransform(Matrix4f &RotateTrans);
    void InitTranslationTransform(Matrix4f &TranslationTrans);
    void InitProjectionTransform(Matrix4f &ProjectionTrans);
    const Matrix4f GetTrans();

    private:
    Vector3f m_scale;
    Vector3f m_worldPos;
    Vector3f m_rotateInfo;
    Matrix4f m_transformation;
};