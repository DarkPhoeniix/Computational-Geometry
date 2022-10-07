#include "OBJReader.h"

#include <sstream>
#include <fstream>
#include <list>

namespace
{
    std::list<std::string> getLines(const std::string& filename)
    {
        std::ifstream inputStream(filename);

        if (!inputStream.is_open())
        {
            throw std::invalid_argument("Can't open file for reading: " + filename);
        }

        std::list<std::string> lines;
        std::string line;

        while (std::getline(inputStream, line))
        {
            if (!line.empty())
            {
                lines.push_back(line);
            }
        }

        return lines;
    }

    glm::vec3 parseVertex(const std::string& line)
    {
        glm::vec3 vertex;
        std::istringstream stream(line.substr(2));

        stream >> vertex.x >> vertex.y >> vertex.z;

        return vertex;
    }

    std::vector<unsigned int> parseIndices(const std::string& line)
    {
        std::vector<unsigned int> indices;
        unsigned int index;
        std::istringstream stream(line.substr(2));

        for (size_t i = 0; i < 3; ++i)
        {
            stream >> index;
            indices.push_back(index);
        }

        return indices;
    }
}

std::vector<Vertex> OBJReader::readFile(const std::string& filename)
{
    std::vector<Vertex> vertices;

    std::vector<glm::vec3> points;
    std::vector<unsigned int> indices;

    std::list<std::string> lines = getLines(filename);
    for (const auto& line : lines)
    {
        if (line.substr(0, 2) == "v ")
        {
            points.push_back(parseVertex(line));
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::vector<unsigned int> temp = parseIndices(line);
            std::copy(temp.begin(), temp.end(), std::back_inserter(indices));
        }
    }

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        glm::vec3 normal = glm::normalize(glm::cross(points[indices[i + 1]] - points[indices[i]], points[indices[i + 2]] - points[indices[i]]));

        vertices.emplace_back(points[indices[i]], normal);
        vertices.emplace_back(points[indices[i + 1]], normal);
        vertices.emplace_back(points[indices[i + 2]], normal);
    }

    return vertices;
}
