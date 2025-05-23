#include "particle.h"

#include "opengl-framework/opengl-framework.hpp"
#include "utils.hpp"


Particle::Particle() {
    float xPos = utils::rand(-gl::window_aspect_ratio(), gl::window_aspect_ratio());
    float yPos = utils::rand(-1, 1);
    position = glm::vec2(xPos, yPos);

    speed = utils::rand(0.1f, 1.f);
    angle = utils::rand(-180.f, 180.f);

    float longSide = utils::rand(.1f, 10.f);
    float xDir = longSide * cos(angle);
    float yDir = longSide * sin(angle);
    direction = glm::normalize(glm::vec2(xDir, yDir));
}

void Particle::move() {
    position += direction * speed * gl::delta_time_in_seconds();
}

void Particle::render() {
    utils::draw_disk(position, radius, color);
}
