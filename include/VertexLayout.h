#pragma once
#include <vector>

struct VertexAttribute {

  const char *name = nullptr;

  std::size_t number_of_floats=0;

  // std::size_t offset;
};

class VertexLayout //this class describes the attributes you have in the data:
{
public:
	std::size_t size() const;  // returns the size in bytes of a single vertex

	void AddVertexAttribute(const char *name, const std::size_t number_of_floats);
	const std::vector<VertexAttribute>& get_attributes() const;
	
private:
	std::vector<VertexAttribute> m_Attributes;
	std::size_t m_Size=0;
};
