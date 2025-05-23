#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct Particle {
    Particle();
    void update(float delta_time);
    void move(float delta);
    void render();

    float diameter() const { return radius * 2; }

private:
    glm::vec2 position{};

    float radius = 0.05f;
    float initial_radius = 0.05f;

    glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };

    float speed = .5f;
    float angle = 0;
    glm::vec2 velocity = { 0, 0 };
    float mass = 1.f;

    glm::vec2 direction = { 0, 0 };

    float age = 0.f;
    float maxAge;
};


