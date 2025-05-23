#include "particle.h"

#include "constants.h"
#include "glm/ext/scalar_constants.hpp"
#include "opengl-framework/opengl-framework.hpp"
#include "utils.hpp"

Particle::Particle() {
    float xPos = utils::rand(-gl::window_aspect_ratio(), gl::window_aspect_ratio());
    float yPos = utils::rand(-1, 1);
    position = glm::vec2(xPos, yPos);

    angle = utils::rand(-180.f, 180.f);

    float longSide = utils::rand(.1f, 10.f);
    float xDir = longSide * cos(angle);
    float yDir = longSide * sin(angle);
    direction = glm::normalize(glm::vec2(xDir, yDir));
}

void Particle::move() {
    float viscosity = 1 * pow(10, -3);
    glm::vec2 fluidSpeed = glm::vec2(0, .5f);
    glm::vec2 fluidForce = -3 * glm::pi<float>() * viscosity * diameter() * fluidSpeed;

    glm::vec2 moveDirection = direction * speed;
    glm::vec2 gravity = constants::gravity * mass;
    glm::vec2 acceleration = (gravity + moveDirection + fluidForce) / mass;

    velocity += acceleration * gl::delta_time_in_seconds();
    position += velocity * gl::delta_time_in_seconds();
}

void Particle::render() {
    utils::draw_disk(position, radius, color);
}
