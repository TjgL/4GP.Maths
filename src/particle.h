#pragma once


struct Particle {
    Particle();
    void render();

private:
    glm::vec2 position;
    float radius = 0.01f;
    glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
};


