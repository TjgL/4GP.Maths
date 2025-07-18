#pragma once

#include <functional>


#include "glm/vec2.hpp"

namespace curve {
    void draw_parametric(std::function<glm::vec2(float)> const& parametric);

    glm::vec2 point_on_circle(float t);
}
