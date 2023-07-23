#include <entt/entt.hpp>
#include <kda_window.h>
#include <kda_logging.h>
#include <kda_graphics.h>
#include <kda_scripts.h>
#include <entt/entt.hpp>

const int WIDTH = 640;
const int HEIGHT = 480;

struct position {
    float x;
    float y;
};

int main(int argc, char* argv[]) {
    entt::registry registry;
    const auto entity = registry.create();
    registry.emplace<position>(entity, 1.f, 1.f);

    kdaWindow::initialize();
    kdaGraphics::initialize(kdaWindow::get_nwh(), WIDTH, HEIGHT);
    kdaScripts::initialize();
    using kdaGraphics::Clear;
    kdaGraphics::setClearColor({Clear::COLOR, Clear::DEPTH}, 0x443355FF, 1.0f, 0);

    bool quit = false;
    kdaGraphics::setViewport(0, 0, WIDTH, HEIGHT);
    while (!quit) {
        kdaGraphics::renderFrame();
        kdaWindow::Input in = kdaWindow::getPollEvent();
        quit = in.quit;
    }

    int finalizeCode = 0;
    finalizeCode = kdaGraphics::finalize();
    finalizeCode = kdaWindow::finalize();

    return finalizeCode;
}