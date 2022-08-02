#pragma once
#include <iostream>
struct AttributeHelper{
	enum AttributeType
    {
        kPosition = 0,
        kColor,
        kUV,
        kAttributeCount
    };
    static const char* getAttributeName(const AttributeType t);
    static AttributeType getAttributeType(const char * attribute_name);
};