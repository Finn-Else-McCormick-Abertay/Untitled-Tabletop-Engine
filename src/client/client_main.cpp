#include <SDL.h>
//#include <SDL_syswm.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <systems/window_system.h>
#include <systems/impl/window_system_impl_sdl2.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

int main(int argc, char *argv[]) {
    WindowSystemImplSDL2 windowSystem;

    if (!windowSystem.Init()) {
        return -1;
    }

    // Main loop
    while (!windowSystem.ShouldClose())
    {
        windowSystem.Update();
    }

    windowSystem.Shutdown();

    return 0;
}