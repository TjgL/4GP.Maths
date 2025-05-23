#include "glm/vec3.hpp"
#include "maths.h"

glm::vec3 maths::lerp(glm::vec3 const &a, glm::vec3 const &b, float t) {
    return (b - a) * t + a;
}

float maths::lerp(const float a, const float b, const float t) {
    return (b - a) * t + a;
}