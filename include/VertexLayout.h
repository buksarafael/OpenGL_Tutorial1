#pragma once
#include <iostream>
#include <vector>

struct AttributeHelper{
	enum AttributeType
    {
        kPosition = 0,
        kColor,
        kAttributeCount
    };
    static const char* getAttributeName(const AttributeType t);
    static AttributeType getAttributeType(const char * attribute_name);
};

struct VertexAttribute {

  const char *type = nullptr;

  std::size_t number_of_floats=0;

};

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
