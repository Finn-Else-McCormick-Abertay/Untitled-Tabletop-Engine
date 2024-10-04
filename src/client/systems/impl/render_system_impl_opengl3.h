#pragma once

#include <systems/render_system.h>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <string>

class RenderSystemImplOpenGl3 : public IRenderSystem
{
public:
    virtual bool Init() override;
    virtual void Shutdown() override;

    void CreateContext(SDL_Window* window);

    virtual void Render() override;
    virtual void ImGuiRender() override;

private:
    SDL_Window* p_window = nullptr;
    SDL_GLContext m_glContext;
    std::string m_glslVersion;

    GLuint m_vertexBuffer;
    GLuint m_shaderProgram;
    GLuint m_matrixId;
    GLuint LoadShaders(const char* vertPath, const char* fragPath);
};