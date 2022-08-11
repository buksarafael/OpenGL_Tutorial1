#include <ShadersProgram.h>
#include <UniformList.h>

void UniformIntegerNode::set_uniform(ShadersProgram *shader) {
  shader->setUniform(uniform, value);
}

void UniformFloatNode::set_uniform(ShadersProgram *shader) {
  shader->setUniform(uniform, value);
}

void UniformVector2fNode::set_uniform(ShadersProgram *shader) {
  shader->setUniform(uniform, value);
}

void UniformVector3fNode::set_uniform(ShadersProgram *shader) {
  shader->setUniform(uniform, value);
}

void UniformMatrix4fNode::set_uniform(ShadersProgram *shader) {
  shader->setUniform(uniform, value);
}