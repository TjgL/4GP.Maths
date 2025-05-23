#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct Particle {
    Particle();
    void move();
    void render();

private:
    glm::vec2 position{};
    float radius = 0.01f;
    glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };

    float speed = 1.f;
    float angle = 0;

    glm::vec2 direction = { 0, 0 };
};


