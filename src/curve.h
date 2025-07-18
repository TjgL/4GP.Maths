#pragma once

#include <functional>


#include "glm/vec2.hpp"


namespace curve {
    void draw_parametric(std::function<glm::vec2(float)> const& parametric);

    glm::vec2 point_on_circle(float t);
    glm::vec2 point_on_heart(float t);

    glm::vec2 bezier1(glm::vec2 a, glm::vec2 b, float t);
    glm::vec2 bezier2(glm::vec2 a, glm::vec2 b, glm::vec2 handle, float t);
    glm::vec2 bezier3(glm::vec2 a, glm::vec2 b, glm::vec2 ha, glm::vec2 hb, float t);

    glm::vec2 bezier2_ber(glm::vec2 a, glm::vec2 b, glm::vec2 handle, float t);
    glm::vec2 bezier3_ber(glm::vec2 a, glm::vec2 b, glm::vec2 ha, glm::vec2 hb, float t);

    glm::vec2 get_derivative(float start, std::function<glm::vec2(float)> const &parametric);
    float gradient_descent(std::function<glm::vec2(float)> const &parametric, glm::vec2 point, float start,
                           float rate = 0.01f, int max_iter = 100, float tolerance = 0.0001f);
}
