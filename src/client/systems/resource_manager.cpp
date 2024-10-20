#include "resource_manager.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::InitImpl() {
    char* pathBuf = SDL_GetBasePath();
    m_appPath = std::string(pathBuf);
    SDL_free(pathBuf);

    return true;
}

void ResourceManager::ShutdownImpl() {
}


template<>
Texture ResourceManager::Get<Texture>(ResourceIdentifier id) {
    return Instance().m_textures.at(id);
}

template<>
ResourceIdentifier ResourceManager::Load<Texture>(const ResourceInfo<Texture>& info) {
    auto& inst = Instance();

    Texture texture;

	ResourceIdentifier id = info.Identifier();
    inst.m_textures.emplace(id, texture);
    return id;
}


template<>
Shader ResourceManager::Get<Shader>(ResourceIdentifier id) {
    return Instance().m_shaders.at(id);
}

template<>
ResourceIdentifier ResourceManager::Load<Shader>(const ResourceInfo<Shader>& info) {
    auto& inst = Instance();

    std::string vertPath = inst.m_appPath + info.VertPath(), fragPath = inst.m_appPath + info.FragPath();
    
	// Create the shaders
	GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertShaderCode;
	std::ifstream vertShaderStream(vertPath.c_str(), std::ios::in);
	if(vertShaderStream.is_open()){
		std::stringstream sstr;
		sstr << vertShaderStream.rdbuf();
		vertShaderCode = sstr.str();
		vertShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string fragShaderCode;
	std::ifstream fragShaderStream(fragPath.c_str(), std::ios::in);
	if(fragShaderStream.is_open()){
		std::stringstream sstr;
		sstr << fragShaderStream.rdbuf();
		fragShaderCode = sstr.str();
		fragShaderStream.close();
	}

	GLint result = GL_FALSE;
	int logLength;

	// Compile Vertex Shader
	char const * vertSourcePtr = vertShaderCode.c_str();
	glShaderSource(vertShaderId, 1, &vertSourcePtr, NULL);
	glCompileShader(vertShaderId);

	// Check Vertex Shader
	glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertShaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0){
		std::vector<char> vertShaderErrorMessage(logLength+1);
		glGetShaderInfoLog(vertShaderId, logLength, NULL, &vertShaderErrorMessage[0]);
		printf("%s\n", &vertShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	char const * fragSourcePtr = fragShaderCode.c_str();
	glShaderSource(fragShaderId, 1, &fragSourcePtr , NULL);
	glCompileShader(fragShaderId);

	// Check Fragment Shader
	glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragShaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0){
		std::vector<char> fragShaderErrorMessage(logLength+1);
		glGetShaderInfoLog(fragShaderId, logLength, NULL, &fragShaderErrorMessage[0]);
		printf("%s\n", &fragShaderErrorMessage[0]);
	}

	// Link the program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);

	// Check the program
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0){
		std::vector<char> programErrorMessage(logLength+1);
		glGetProgramInfoLog(programId, logLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}
	
	glDetachShader(programId, vertShaderId);
	glDetachShader(programId, fragShaderId);
	
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);

	Shader shader = Shader(programId);
	ResourceIdentifier id = info.Identifier();

    inst.m_shaders.emplace(id, shader);
    return id;
}