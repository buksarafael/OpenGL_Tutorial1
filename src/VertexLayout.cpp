#include <VertexLayout.h>


void VertexLayout::AddVertexAttribute(const char *name, const std::size_t number_of_floats)
{
    VertexAttribute attrib;
    attrib.name = name;
    attrib.number_of_floats = number_of_floats;
    m_Size += number_of_floats * sizeof(float);
    m_Attributes.push_back(attrib);

}

std::size_t VertexLayout::size() const
{
    return m_Size;
}

const std::vector<VertexAttribute>& VertexLayout::get_attributes() const
{
    return m_Attributes;
}