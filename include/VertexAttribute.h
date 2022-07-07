#pragma once
#include <iostream>

struct VertexAttribute{
	VertexAttribute(): nr_of_floats(0){}
	const char* name;
	std::size_t nr_of_floats;
};
