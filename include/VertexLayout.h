#pragma once
#include <vector>



class VertexLayout //this class describes the attributes you have in the data:
{
public:
	std::size_t size() const;  // returns the size in bytes of a single vertex

	void AddVertexAttribute(const char *name, const std::size_t number_of_floats);
	std::vector<VertexAttribute> get_attributes() const;
private:
	std::vector<VertexAttribute> m_Attributes;
};
