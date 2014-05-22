#include "GLContext.h"
#include "Window.h"
#include <SDL.h>

namespace sdl
{
	GLContext::GLContext(const Window& window)
		: context(SDL_GL_CreateContext(window.handle()), SDL_GL_DeleteContext)
	{
		if (!context)
		{
			throw std::exception("could not create OpenGL context.");
		}
	}
	
	void GLContext::makeCurrent(const Window& window)
	{
		SDL_GL_MakeCurrent(window.handle(), context.get());
	}

	void GLContext::setVersion(int major, int minor)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	}
}
