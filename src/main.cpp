#include "curve.h"
#include "glm/ext/scalar_constants.hpp"
#include "opengl-framework/opengl-framework.hpp"
#include "utils.hpp"


float easeInOut(float x, float power)
{
    if (x < 0.5)
    {
        return 0.5 * pow(2 * x, power);
    }
    else
    {
        return 1 - 0.5 * pow(2 * (1 - x), power);
    }
}

struct Particle {
    glm::vec2 position{
        utils::rand(-gl::window_aspect_ratio(), +gl::window_aspect_ratio()),
        utils::rand(-1.f, +1.f),
    };

    glm::vec2 velocity;

    float mass{utils::rand(1.f, 2.f)};

    float age{0.f};
    float lifespan{utils::rand(3.f, 5.f)};

    glm::vec3 start_color{
        utils::rand(0.f, 1.f),
        utils::rand(0.f, 1.f),
        utils::rand(0.f, 1.f),
    };
    glm::vec3 end_color{
        utils::rand(0.f, 1.f),
        utils::rand(0.f, 1.f),
        utils::rand(0.f, 1.f),
    };

    glm::vec3 color() const
    {
        return glm::mix(start_color, end_color, easeInOut(relative_age(), 4.f));
    }

    float radius() const
    {
        return 0.01f;
        return std::min(lifespan - age, 2.f) / 2.f * 0.03f;
    }

    float relative_age() const
    {
        return age / lifespan;
    }

    Particle()
    {
        float const initial_angle = utils::rand(0.f, 2.f * glm::pi<float>());

        velocity = {
            0.2f * std::cos(initial_angle),
            0.2f * std::sin(initial_angle),
        };
    }
};

struct Plane {
    glm::vec2 origin = glm::vec2(0.25f, -0.2f);
    glm::vec2 xDir = glm::vec2(0.35, 0);
    glm::vec2 yDir = glm::vec2(.75, .6);

    Plane(glm::vec2 const& origin, glm::vec2 const& xDir, glm::vec2 const& yDir) :
        origin(origin), xDir(xDir), yDir(yDir) {}

    Plane() = default;

    [[nodiscard]] glm::vec2 randomPointInPlane() const {
        return origin + xDir * utils::rand(-1.f, 1.f) + yDir * utils::rand(-1.f, 1.f);
    }
};

glm::vec2 getRandomPointInCircle(float radius, const Plane& plane, int depth = 0) {
    glm::vec2 point = plane.randomPointInPlane();
    if (glm::length(point - plane.origin) > radius) {
        return getRandomPointInCircle(radius, plane, depth + 1);
    }
    return point;
}

int main()
{
    gl::init("Particules!");
    gl::maximize_window();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    std::vector<Particle> particles(10000);

    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        curve::draw_parametric(curve::point_on_circle);
    }
}