#include "stdafx.h"
#include "Window.h"

namespace sdl
{
	namespace {
		SDL_WindowFlags toNativeFlags(Window::Flags flags)
		{
			return static_cast<SDL_WindowFlags>(flags);
		}
	}

	Window::Window(const std::string& title, int x, int y, int width, int height, Flags flags)
		: m_window(SDL_CreateWindow(title.c_str(), x, y, width, height, toNativeFlags(flags)), SDL_DestroyWindow)
	{
		if (!m_window)
		{
			throw std::exception("could not create window");
		}
	}

	Window::Flags operator|(Window::Flags lhs, Window::Flags rhs)
	{
		return (Window::Flags)((uint32_t)lhs | rhs);
	}

	Window::Flags operator&(Window::Flags lhs, Window::Flags rhs)
	{
		return (Window::Flags)((uint32_t)lhs & rhs);
	}

	void Window::swap()
	{
		SDL_GL_SwapWindow(m_window.get());
	}

	SDL_Window* Window::handle() const
	{
		return m_window.get();
	}
}