#include <VertexLayout.h>

const char *AttributeHelper::getAttributeName(const AttributeType t){
    switch (t){
        case AttributeHelper::AttributeType::kColor:
            return "Color";
            break;
        case AttributeHelper::AttributeType::kPosition:
            return "Position";
            break;
        case AttributeHelper::AttributeType::kAttributeCount:
            return "AttributeCount";
            break;
    }
}
AttributeHelper::AttributeType
AttributeHelper::getAttributeType(const char *attribute_name){
    if(strcmp(attribute_name,"Color")==0)
        return AttributeHelper::AttributeType::kColor;
    if(strcmp(attribute_name,"Position")==0)
        return AttributeHelper::AttributeType::kPosition;
    return AttributeHelper::AttributeType::kAttributeCount;
}

void VertexLayout::AddVertexAttribute(const AttributeHelper::AttributeType t, const std::size_t number_of_floats)
{
    VertexAttribute attrib;
    attrib.type = AttributeHelper::getAttributeName(t);
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