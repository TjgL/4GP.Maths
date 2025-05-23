#pragma once
#include "glm/vec3.hpp"

namespace maths {
    float lerp(float a, float b, float t);
    glm::vec3 lerp(glm::vec3 const& a, glm::vec3 const& b, float t);
}
