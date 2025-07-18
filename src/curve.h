#pragma once

#include <functional>


#include "glm/vec2.hpp"

namespace curve {
    void draw_parametric(std::function<glm::vec2(float)> const& parametric);

    glm::vec2 point_on_circle(float t);
    glm::vec2 point_on_heart(float t);

    glm::vec2 bezier1(glm::vec2 a, glm::vec2 b, float t);
    glm::vec2 bezier2(const glm::vec2 a, const glm::vec2 b, const glm::vec2 handle, const float t);
    glm::vec2 bezier3(const glm::vec2 a, const glm::vec2 b, const glm::vec2 ha, const glm::vec2 hb, const float t);
}
