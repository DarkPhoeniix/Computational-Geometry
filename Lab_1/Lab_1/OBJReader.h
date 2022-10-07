#pragma once

#include "Vertex.h"

#include <glm.hpp>

#include <vector>
#include <string>

class OBJReader
{
public:
	static std::vector<Vertex> readFile(const std::string& filename);
};
