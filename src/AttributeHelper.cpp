#include <VertexAttribute.h>
#include <AttributeHelper.h>

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
