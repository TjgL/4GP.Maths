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

    glm::vec2 point_on_circle(float t) {
        return glm::vec2(cos(2 * glm::pi<float>() * t), sin(2 * glm::pi<float>() * t));
    }
}