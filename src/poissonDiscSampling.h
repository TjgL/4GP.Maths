#pragma once
#include <vector>

#include "glm/vec2.hpp"

namespace poisson {
    bool isValid(glm::vec2 candidate, glm::vec2 sampleRegionSize, float cellSize, float radius, std::vector<glm::vec2> points, std::vector<int> grid);
    std::vector<glm::vec2> generatePoints(float radius, glm::vec2 sampleRegionSize, int numSamplesBeforeRejection = 30);
}
