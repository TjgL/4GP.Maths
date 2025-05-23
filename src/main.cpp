#include "opengl-framework/opengl-framework.hpp"
#include "utils.hpp"
#include "particle.h"

int main()
{
    gl::init("Particules!");
    gl::maximize_window();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    std::vector<Particle> particles = std::vector<Particle>(100);

    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto &particle : particles) {
            particle.move();
            particle.render();
        }
    }
}