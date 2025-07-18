#include <functional>

#include "glm/ext/scalar_constants.hpp"
#include "glm/vec2.hpp"
#include "utils.hpp"


namespace curve {
    void draw_parametric(std::function<glm::vec2(float)> const& parametric) {
        int step = 100;
        glm::vec2 previous = parametric(0);

        for (float t = 0; t < 1; t += 1.f / step) {
            glm::vec2 current = parametric(t);
            utils::draw_line(previous, current, 0.01, glm::vec4(1, 0, 0, 1));
            previous = current;
        }
    }

    glm::vec2 point_on_circle(const float t) {
        return glm::vec2(cos(2 * glm::pi<float>() * t), sin(2 * glm::pi<float>() * t));
    }

    glm::vec2 point_on_heart(const float t) {
        return glm::vec2(glm::sqrt(2) * (sin(t) * sin(t) * sin(t)),
                -(cos(t) * cos(t) * cos(t)) - (cos(t) * cos(t)) + 2 * cos(t)) * 0.25f;
    }

    glm::vec2 bezier1(const glm::vec2 a, const glm::vec2 b, const float t) {
        return (b - a) * t + a;
    }
}