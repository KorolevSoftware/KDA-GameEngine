#include "kda_graphics.h"
#include "kda_graphics.h"
#include <bgfx/bgfx.h>
#include "bgfx_utils.h"
#include <bgfx/platform.h>
#include <kda_graphics.h>
#include <kda_scripts.h>
#include <ranges>

namespace kdaGraphicsPrivate {
    static kdaGraphics::Program activeProgram;
}


namespace kdaGraphics {

    void regScripts() {
        auto snameSpace = kdaScripts::createNameSpace("graphics");

        snameSpace["clear_color"] = [](std::vector<Clear> clear, uint32_t rgba, float depth, uint8_t stencil) {
            setClearColor(clear, rgba, depth, stencil);
        };

        snameSpace["setViewport"] = setViewport;
        snameSpace["setViewport"] = setViewport;
    }

	int initialize(void* nwt, uint16_t width, uint16_t height) {
        regScripts();
        bgfx::PlatformData pd;
        // and give the pointer to the window to pd
        pd.nwh = nwt;

        // Tell bgfx about the platform and window
        bgfx::setPlatformData(pd);
        // Render an empty frame
        bgfx::renderFrame();

        bgfx::Init init;
        init.platformData = pd;
        init.type = bgfx::RendererType::OpenGL;
        init.resolution.width = width;
        init.resolution.height = height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        bgfx::init(init);
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);
		return 0;
	}

    void setViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
        bgfx::setViewRect(0, x, y, width, height);
    }

    void setClearColor(std::span<Clear> flags, uint32_t rgba, float depth, uint8_t stencil) {
        uint16_t bgfxFlag = 0;

        for (auto i : flags) {
            if (i == Clear::COLOR) {
                bgfxFlag |= BGFX_CLEAR_COLOR;
            }
            else if (i == Clear::DEPTH) {
                bgfxFlag |= BGFX_CLEAR_DEPTH;
            }
            else if (i == Clear::STENCIL) {
                bgfxFlag |= BGFX_CLEAR_STENCIL;
            }
        }
        bgfx::setViewClear(0, bgfxFlag, rgba, depth, stencil);
        bgfx::touch(0);
    }

    void setVertexBuffer(BufferVertex buffer) {
        bgfx::VertexBufferHandle bgfx_buffer = { buffer };
        bgfx::setVertexBuffer(0, bgfx_buffer);
    }

    void setIndexBuffer(BufferIndex buffer) {
        bgfx::IndexBufferHandle bgfx_buffer = { buffer };
        bgfx::setIndexBuffer(bgfx_buffer);
    }

    void setProgram(Program program) {
        kdaGraphicsPrivate::activeProgram = program;
    }

    const Shader createShader(ShaderType type, std::span<const std::byte> shaderBin) {
        return bgfx::createShader(bgfx::makeRef(shaderBin.data(), shaderBin.size())).idx;
    }

    BufferVertex createVertexBuffer(const BufferLayoutDeclaration& declaration, std::span<float> data) {
        bgfx::VertexLayout layout;
        layout = layout.begin(); // Begin VertexLayout
        for (auto dec : declaration.declaration) {
            bgfx::Attrib::Enum atrib = bgfx::Attrib::Enum::Count;
            bgfx::AttribType::Enum atribType = bgfx::AttribType::Enum::Count;

            switch (dec.type) {
                using enum AttribType;
            case Float:
                atribType = bgfx::AttribType::Enum::Float;
                break;

            case Byte:
                atribType = bgfx::AttribType::Enum::Uint8;
                break;

            case Int:
                atribType = bgfx::AttribType::Enum::Int16;
                break;

            default:
                assert("erroe bgfx::AttribType::Enum");
                break;
            }

            switch (dec.attrib) {
                using enum Attrib;
            case Position:
                atrib = bgfx::Attrib::Enum::Position;
                break;

            case Color0:
                atrib = bgfx::Attrib::Enum::Color0;
                break;

            default:
                assert("erroe bgfx::Attrib::Enum");
                break;
            }
           
            layout.add(atrib, dec.count, atribType, dec._normalized);
        }
        layout.end();// End VertexLayout
        const bgfx::Memory *mem = bgfx::makeRef(data.data(), data.size()*sizeof(data[0]));
        return bgfx::createVertexBuffer(mem, layout).idx;
    }

    BufferIndex createIndexBuffer(std::span<const std::byte> data) {
        return bgfx::createIndexBuffer(bgfx::makeRef(data.data(), data.size() * sizeof(data[0]))).idx;
    }

    void setViewProjection(std::span<const float> view, std::span<const float> projection) {
        bgfx::setViewTransform(0, view.data(), projection.data());
    }

    void drawArray() {
        bgfx::ProgramHandle bgfx_program = { kdaGraphicsPrivate::activeProgram };
        bgfx::submit(0, bgfx_program);
    }

    void drawElements() {
        bgfx::setState(
            BGFX_STATE_WRITE_R
            | BGFX_STATE_WRITE_G
            | BGFX_STATE_WRITE_B
            | BGFX_STATE_WRITE_A
        );
        bgfx::ProgramHandle program_handler { kdaGraphicsPrivate::activeProgram };
        bgfx::submit(0, program_handler);
    }

    Program createProgramGraphic(Shader vertex, Shader pixel) {
        bgfx::ShaderHandle vertex_handler { vertex };
        bgfx::ShaderHandle pixel_handler { pixel };
        return bgfx::createProgram(vertex_handler, pixel_handler).idx;
    }
    Program createProgramCompute(Shader compute) {
        bgfx::ShaderHandle compute_handler { compute };
        return bgfx::createProgram(compute_handler).idx;
    }

    Texture createTexture(int32_t width, int32_t height, TextureFormat format, std::span<const std::byte> data) {
        bgfx::TextureFormat::Enum bgfxFormat = bgfx::TextureFormat::Enum::Count;
       
        switch (format) {
            using enum TextureFormat;
            using bgfxTF = bgfx::TextureFormat::Enum;

        case BGRA8:
            bgfxFormat = bgfxTF::RGBA8;
            break;

        case RGB8:
            bgfxFormat = bgfxTF::RGB8;
            break;

        default:
            assert("error format");
            break;
        }
        return bgfx::createTexture2D(width, height, false, 1, bgfxFormat, BGFX_SAMPLER_POINT, bgfx::makeRef(data.data(), data.size())).idx;
    }

    void setTransform(std::span<const float> transform) {
        bgfx::setTransform(transform.data());
    }

    void renderFrame() {
        bgfx::frame();
    }

	int finalize() {
        bgfx::shutdown();
        return 0;
	}
}