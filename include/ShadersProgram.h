#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <OpenGL/gl3.h>
#include <Math3D.h>
#include <UniformHelper.h>
#include <set>
#include <string>
#include <functional>

enum class BlendingFunc{
	NONE = 0,

  	src_COLOR,
  	ONE_MINUS_SRC_COLOR,
  	DST_COLOR,
  	ONE_MINUS_DST_COLOR,
  	SRC_ALPHA,
  	ONE_MINUS_SRC_ALPHA,
  	DST_ALPHA,
  	ONE_MINUS_DST_ALPHA,
  	CONSTANT_COLOR,
  	ONE_MINUS_CONSTANT_COLOR,
  	CONSTANT_ALPHA,
  	ONE_MINUS_CONSTANT_ALPHA,

  	Count
};

struct BlendingState{
	bool enabled= false;
	BlendingFunc source_func = BlendingFunc::NONE;
	BlendingFunc dest_func = BlendingFunc::NONE;
	bool equals(const BlendingState &cmp) const;
	bool operator==(const BlendingState &other) const;
	bool operator!=(const BlendingState &other) const;
	bool operator<(const BlendingState &other) const;
};


class ShadersProgram
{
public:
	ShadersProgram();
	~ShadersProgram();


public:
	bool create(const std::array<const char *, 2> &files);
	bool create(const char *vs,const char *fs);
	GLint getUniformPosition(UniformHelper::UniformType uniform);
	void setUniform(UniformHelper::UniformType,int value);
	void setUniform(UniformHelper::UniformType,float value);
	void setUniform(UniformHelper::UniformType,Vector2f& vec2f);
	void setUniform(UniformHelper::UniformType,Vector3f& vec3f);
	void setUniform(UniformHelper::UniformType,Vector4f& vec4f);
	void setUniform(UniformHelper::UniformType,Matrix4f& mat4f);
	void bindShaders();
	void initUniforms();

	

	inline void setBlendingState(BlendingState &blend){
		m_BlendingState = blend;
	}
	inline const BlendingState &getBlendingState() const{
		return m_BlendingState;
	}
	bool operator<(const ShadersProgram &other);
	bool operator!=(const ShadersProgram &other);

public: 
	GLuint m_ShaderProgram=0;

private:
	std::array<GLuint,(std::size_t)UniformHelper::UniformType::kUniformCount>m_Uniforms;
	BlendingState m_BlendingState;

};