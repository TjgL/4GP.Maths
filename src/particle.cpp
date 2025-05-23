#include "particle.h"

#include "constants.h"
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

    age = utils::rand(5.f, 15.f);
}

void Particle::move() {
    glm::vec2 moveDirection = direction * speed;
    glm::vec2 gravity = constants::GRAVITY * mass;

    glm::vec2 dragForce = -constants::AIR_RESISTANCE * velocity;
    glm::vec2 acceleration = (gravity + moveDirection + dragForce) / mass;

    velocity += acceleration * gl::delta_time_in_seconds();
    position += velocity * gl::delta_time_in_seconds();
}

void Particle::render() {
    utils::draw_disk(position, radius, color);
}
