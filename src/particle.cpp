#include "opengl-framework/opengl-framework.hpp"
#include "particle.h"

Particle::Particle() {
    float x = utils::rand(-gl::window_aspect_ratio(), gl::window_aspect_ratio());
    float y = utils::rand(-1, 1);
    position = glm::vec2(x, y);
}

void Particle::render() {
    utils::draw_disk(position, radius, color);
}
