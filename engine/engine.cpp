#include <entt/entt.hpp>
#include <kda_window.h>
#include <kda_logging.h>
#include <kda_graphics.h>
#include <kda_scripts.h>
#include <string_view>
#include <unordered_map>
#include <span>
#include <fstream>
#include <filesystem>

const int WIDTH = 640;
const int HEIGHT = 480;

struct Position {
    float x;
    float y;
};

struct Rotation {
    float x;
    float y;
};

struct scriptUpdate {};
struct scriptFinal {};
struct scriptInit {};

struct Transform {
    Position pos;
    Rotation rot;
};

struct GameObject {
    std::vector<entt::registry::entity_type> components;
};

template<auto>
struct tag final {};

std::vector<std::byte> loadFile(std::filesystem::path path) {
    std::basic_ifstream<std::byte, std::char_traits<std::byte>> ifs(path, std::ios::binary);
    return { std::istreambuf_iterator<std::byte> { ifs }, {} };
}

std::array<float, 21> vertex = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
};

std::array<uint32_t, 3> index = {
    1,2,3
};

int main(int argc, char* argv[]) {
    entt::registry registry;
    const auto entity = registry.create();
    registry.emplace<scriptUpdate>(entity);
    registry.emplace<scriptFinal>(entity);
    registry.emplace<scriptInit>(entity);
    const auto entity2 = registry.create();
    registry.emplace<Transform>(entity2);
    auto view = registry.view<scriptUpdate>();

    kdaWindow::initialize();
    kdaGraphics::initialize(kdaWindow::get_nwh(), WIDTH, HEIGHT);
    kdaScripts::initialize();

    using kdaGraphics::Clear;
    std::array<Clear, 2> clear{ Clear::COLOR, Clear::DEPTH };
    kdaGraphics::setClearColor(clear, 0x443355FF, 1.0f, 0);


    kdaGraphics::setViewport(0, 0, WIDTH, HEIGHT);
    // test
    kdaScripts::runScript("graphics.clear_color({0 ,1},  0x4433FFFF, 1.0, 0)");
    kdaGraphics::BufferLayoutDeclaration decl;
    decl.declaration.emplace_back(kdaGraphics::Attrib::Position, 3, kdaGraphics::AttribType::Float);
    decl.declaration.emplace_back(kdaGraphics::Attrib::Color0, 4, kdaGraphics::AttribType::Float);
    auto vertex_buffer = kdaGraphics::createVertexBuffer(decl, vertex);
    auto index_buffer = kdaGraphics::createIndexBuffer(index);

    auto fragment_shader_b = loadFile("e:/Project/Develop_2023/KDA-GameEngine/shaders/pixel.b");
    auto vertex_shader_b = loadFile("e:/Project/Develop_2023/KDA-GameEngine/shaders/vertex.b");
    
    auto vertex_shader_cm = kdaGraphics::createShader(kdaGraphics::ShaderType::Vertex, vertex_shader_b);
    auto fragment_shader_cm = kdaGraphics::createShader(kdaGraphics::ShaderType::Pixel, fragment_shader_b);
    auto program_cm = kdaGraphics::createProgramGraphic(vertex_shader_cm, fragment_shader_cm);

    bool quit = false;
    while (!quit) {
        kdaWindow::Input in = kdaWindow::getPollEvent();
        quit = in.quit;
        kdaGraphics::setVertexBuffer(vertex_buffer);
        kdaGraphics::setProgram(program_cm);
        kdaGraphics::drawElements();
        kdaGraphics::renderFrame();
    }

    int finalizeCode = 0;
    finalizeCode = kdaGraphics::finalize();
    finalizeCode = kdaWindow::finalize();

    return finalizeCode;
}