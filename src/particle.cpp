#include "particle.h"

#include "constants.h"
#include "maths.h"
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

    maxAge = utils::rand(2.f, 10.f);
    initial_radius = radius;
}

void Particle::update(float delta_time) {
    age += delta_time;

    radius = maths::lerp(initial_radius, 0, glm::max(maxAge - 2, age) / maxAge);

    move(delta_time);
    render();
}

void Particle::move(float delta) {
    glm::vec2 moveDirection = direction * speed;
    glm::vec2 gravity = constants::GRAVITY * mass;

    glm::vec2 acceleration = (gravity + moveDirection) / mass;
    acceleration += -velocity * constants::AIR_RESISTANCE;

    velocity += acceleration * gl::delta_time_in_seconds();
    position += velocity * gl::delta_time_in_seconds();
}

void Particle::render() {
    utils::draw_disk(position, radius, color);
}
