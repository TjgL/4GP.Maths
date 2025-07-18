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

    std::vector<Particle> particles(100);

    glm::vec2 start{-.3f, -.3f};
    glm::vec2 end{0.5f, 0.5f};
    glm::vec2 ha{-0.2, 0};
    glm::vec2 hb{0.5, -0.2};

    float t = 0;
    for (int i = 0; i < particles.size(); ++i) {
        t += 1.f / particles.size();
        particles[i].position = curve::bezier3(start, end, ha, hb, t);

        glm::vec2 previous = curve::bezier3(start, end, ha, hb, t - 0.001f);
        glm::vec2 tangent = particles[i].position - previous;
        glm::vec2 normal = {-tangent.y, tangent.x};
        particles[i].velocity = glm::normalize(normal) * 0.1f;
    }

    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& particle : particles)
        {
            particle.position += particle.velocity * gl::delta_time_in_seconds();
        }

        curve::draw_parametric([start, end, ha, hb](float t) {
            return curve::bezier3_ber(start, end, ha, hb, t);
        });

        glm::vec2 result = curve::gradient_descent([start, end, ha, hb](float t) {
            return curve::bezier3_ber(start, end, ha, hb, t);
        }, gl::mouse_position(), 0.2f);

        utils::draw_disk(result, 0.02, glm::vec4(1, 0, 0, 0.7));

        utils::draw_disk(start, 0.02, glm::vec4(0.5, 0, 1, 0.7));
        utils::draw_disk(end, 0.02, glm::vec4(0.5, 0, 1, 0.7));
        utils::draw_disk(hb, 0.02, glm::vec4(0.5, 0, 1, 0.7));
        utils::draw_disk(ha, 0.02, glm::vec4(0.5, 0, 1, 0.7));

        for (auto const& particle : particles)
            utils::draw_disk(particle.position, particle.radius(), glm::vec4{particle.color(), 1.f});
    }
}