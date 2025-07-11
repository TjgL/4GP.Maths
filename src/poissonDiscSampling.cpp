#include "poissonDiscSampling.h"

#include <algorithm>

#include "glm/common.hpp"
#include "glm/exponential.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "utils.hpp"

namespace poisson {

    std::vector<glm::vec2> generatePoints(float radius, glm::vec2 sampleRegionSize,
                                          int numSamplesBeforeRejection) {
        float cellSize = radius / glm::sqrt(2);

        int width = ceil(sampleRegionSize.y / cellSize);
        std::vector<int> grid(ceil(sampleRegionSize.x / cellSize) * width);

        std::vector<glm::vec2> points;
        std::vector<glm::vec2> spawnPoints;

        spawnPoints.push_back(glm::vec2(sampleRegionSize.x / 2, sampleRegionSize.y / 2));

        while (spawnPoints.size() > 0) {
            int spawnIndex = utils::rand(0, spawnPoints.size() - 1);
            glm::vec2 center = spawnPoints[spawnIndex];

            bool candidateAccepted = false;

            for (int i = 0; i < numSamplesBeforeRejection; i++) {
                float angle = utils::rand(0, 1) * glm::pi<float>() * 2;
                glm::vec2 direction = glm::vec2(cos(angle), sin(angle));
                glm::vec2 candidate = center + direction * utils::rand(radius, radius * 2);

                if (isValid(candidate, sampleRegionSize, cellSize, radius, points, grid)) {
                    points.push_back(candidate);
                    spawnPoints.push_back(candidate);
                    grid[(candidate.y/cellSize) * width + (candidate.x/cellSize)] = points.size();
                    candidateAccepted = true;
                    break;
                }
            }

            if (!candidateAccepted) {
                spawnPoints.erase(spawnPoints.begin() + spawnIndex);
            }
        }

        return points;
    }

    bool isValid(glm::vec2 candidate, glm::vec2 sampleRegionSize, float cellSize, float radius, std::vector<glm::vec2> points, std::vector<int> grid) {
        if (candidate.x >= 0 && candidate.x < sampleRegionSize.x && candidate.y >= 0 && candidate.y < sampleRegionSize.y) {
            int cellx = candidate.x / cellSize;
            int celly = candidate.y / cellSize;

            int searchStartX = std::max(0, cellx - 2);
            int gridHeight = ceil(sampleRegionSize.y / cellSize);
            int searchEndX = std::min(cellx + 2, gridHeight - 1);

            int searchStartY = std::max(0, celly - 2);
            int gridWidth = ceil(sampleRegionSize.x / cellSize);
            int searchEndY = std::min(celly + 2, gridWidth - 1);

            for (int x = searchStartX; x <= searchEndX; x++) {
                for (int y = searchStartY; y <= searchEndY; y++) {
                    int pointIndex = grid[celly * gridWidth + cellx] - 1;
                    if (pointIndex != -1) {
                        float distance = (candidate - points.at(pointIndex)).length();
                        if (distance < radius) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        return false;
    }
} // namespace poisson
