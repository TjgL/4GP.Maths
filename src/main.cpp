#include "glm/ext/scalar_constants.hpp"
#include "opengl-framework/opengl-framework.hpp"
#include "utils.hpp"

#include <iostream>

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

struct HitInfo {
    glm::vec2 position;
    glm::vec2 normal;
};

struct Segment {
    glm::vec2 start;
    glm::vec2 end;

    float width{0.01f};

    glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);

    Segment(glm::vec2 start, glm::vec2 end) : start(start), end(end) {
    }

    glm::vec2 direction() const { return end - start; }
};

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

bool testSegmentIntersect(const Segment& a, const Segment& b, HitInfo& hit);

int main()
{
    gl::init("Particules!");
    gl::maximize_window();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    std::vector<Particle> particles(100);
    Segment fixedSegment(glm::vec2(-0.8f, 0.3f), glm::vec2(0.4f, 0.7f));
    Segment mouseSegment(glm::vec2(-.1f, -0.5f), glm::vec2(0.3f, 0.4f));
    bool editStart = false;

    std::vector<Segment*> segments({&fixedSegment, &mouseSegment});

    auto camera = gl::Camera{};
    gl::set_events_callbacks({
        camera.events_callbacks(),
        {
            .on_mouse_pressed = [&](gl::MousePressedEvent const& e) {
                std::cout << "Mouse pressed " << std::endl;
                mouseSegment.start = gl::mouse_position();
            },
        },
    });

    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        mouseSegment.end = gl::mouse_position();

        for (auto& particle : particles)
        {
            // particle.age += gl::delta_time_in_seconds();

            auto forces = glm::vec2{0.f};

            // Gravity
            // forces += glm::vec2{0.f, -1.f} * particle.mass;

            // Air friction
            // forces += -particle.velocity * 1.f;

            // Follow mouse
            // forces += (gl::mouse_position() - particle.position);

            for (auto const& segment : segments) {
                HitInfo hitInfo{};
                Segment movement{particle.position, particle.position + particle.velocity * gl::delta_time_in_seconds()};

                if (testSegmentIntersect(*segment, movement, hitInfo)) {
                    particle.velocity = glm::reflect(particle.velocity, glm::normalize(hitInfo.normal));
                }
            }

            particle.velocity += forces / particle.mass * gl::delta_time_in_seconds();
            particle.position += particle.velocity * gl::delta_time_in_seconds();
        }

        std::erase_if(particles, [&](Particle const& particle) { return particle.age > particle.lifespan; });

        utils::draw_line(fixedSegment.start, fixedSegment.end, fixedSegment.width, fixedSegment.color);
        utils::draw_line(mouseSegment.start, mouseSegment.end, mouseSegment.width, mouseSegment.color);

        for (auto const& particle : particles)
            utils::draw_disk(particle.position, particle.radius(), glm::vec4{particle.color(), 1.f});

        HitInfo hitInfo{};
        bool hasHit = testSegmentIntersect(fixedSegment, mouseSegment, hitInfo);
        if (hasHit) {
            utils::draw_line(hitInfo.position, hitInfo.position + hitInfo.normal * 0.1f, 0.01f, glm::vec4{1.f, 0.f, 0.f, 1.f});
            glm::vec2 reflect = glm::reflect(mouseSegment.direction(),  glm::normalize(hitInfo.normal));
            utils::draw_line(hitInfo.position, hitInfo.position +reflect * 2.f, 0.01f, glm::vec4{0.f, 1.f, 0.f, 1.f});
        }
    }
}


bool testSegmentIntersect(const Segment& a, const Segment& b, HitInfo& hit) {
    glm::vec2 d1 = a.direction();
    glm::vec2 d2 = b.direction();
    glm::mat2 matrice = glm::mat2(d1, -d2);

    glm::vec2 vector = b.start - a.start;
    glm::vec2 t = glm::inverse(matrice) * vector;

    if (t.x > 0.f && t.x < 1.f && t.y > 0.f && t.y < 1.f) {
        float dx = a.end.x - a.start.x;
        float dy = a.end.y - a.start.y;
        glm::vec2 normal = glm::vec2(-dy, dx);

        hit.position = t.x * d1 + a.start;
        hit.normal = normal;
        return true;
    }

    return false;
}