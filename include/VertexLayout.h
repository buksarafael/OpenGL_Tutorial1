#pragma once
#include <iostream>
#include <AttributeHelper.h>
#include <VertexAttribute.h>
#include <vector>

class VertexLayout //this class describes the attributes you have in the data:
{
public:
	std::size_t size() const;  // returns the size in bytes of a single vertex

	void AddVertexAttribute(const AttributeHelper::AttributeType t, const std::size_t number_of_floats);
	const std::vector<VertexAttribute>& get_attributes() const;
	
private:
	std::vector<VertexAttribute> m_Attributes;
	std::size_t m_Size=0;
};
