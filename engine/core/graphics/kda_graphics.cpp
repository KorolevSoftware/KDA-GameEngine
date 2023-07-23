#include <bgfx/bgfx.h>
#include "bgfx_utils.h"
#include <bgfx/platform.h>
#include <kda_graphics.h>

namespace kdaGraphics {

	int initialize(void* nwt, uint16_t width, uint16_t height) {
        bgfx::PlatformData pd;
        // and give the pointer to the window to pd
        pd.nwh = nwt;

        // Tell bgfx about the platform and window
        bgfx::setPlatformData(pd);
        // Render an empty frame
        bgfx::renderFrame();

        bgfx::Init init;
        init.platformData = pd;
        init.type = bgfx::RendererType::Count;
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

    void setClearColor(std::initializer_list<Clear> flags, uint32_t rgba, float depth, uint8_t stencil) {
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

    void renderFrame() {
        bgfx::frame();
    }

	int finalize() {
        bgfx::shutdown();
        return 0;
	}
}