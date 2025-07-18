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

    glm::vec2 bezier2(const glm::vec2 a, const glm::vec2 b, const glm::vec2 handle, const float t) {
        const glm::vec2 aToH = bezier1(a, handle, t);
        const glm::vec2 hToB = bezier1(handle, b, t);

        return bezier1(aToH, hToB, t);
    }

    glm::vec2 bezier3(const glm::vec2 a, const glm::vec2 b, const glm::vec2 ha, const glm::vec2 hb, const float t) {
        const glm::vec2 aToHb = bezier2(a, hb, ha, t);
        const glm::vec2 haToB = bezier2(ha, b, hb, t);

        return bezier1(aToHb, haToB, t);
    }

    glm::vec2 bezier2_ber(const glm::vec2 a, const glm::vec2 b, const glm::vec2 handle, const float t) {
        return ((1 - t) * (1 - t)) * a + (2 * t * (1 - t)) * handle + (t * t) * b;
    }
}