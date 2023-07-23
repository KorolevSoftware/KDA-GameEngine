#include <SDL.h>
#include <SDL_syswm.h>
#include <kda_window.h>
#include <kda_logging.h>

namespace kdaWindow {
    const int WIDTH = 640;
    const int HEIGHT = 480;

    SDL_Window* window = nullptr;

    void* get_nwh() {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            ILogger::critical("Window could not get_nwh");
            return nullptr;
        }
        return wmi.info.win.window;
    }

    int initialize() {
        //Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL) {
            ILogger::critical("Window could not be created! SDL_Error:");
        }
        ILogger::info("created SDL Window");
        return 0;
    }

    int finalize() {
        // Free up window
        SDL_DestroyWindow(window);
        // Shutdown SDL
        SDL_Quit();
        return 0;
    }

    Input getPollEvent() {
        bool quit = false;
        SDL_Event currentEvent;
        while (SDL_PollEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                quit = true;
            }
        }
        return { quit };
    }
}