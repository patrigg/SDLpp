#include "stdafx.h"
#include "Renderer.h"
#include "Window.h"
#include "Texture.h"

namespace sdl
{
	Renderer::Renderer(const Window& window)
		: m_renderer(SDL_CreateRenderer(window.handle(), -1, SDL_RENDERER_ACCELERATED),
					 SDL_DestroyRenderer)
	{
	}

	void Renderer::copy(Texture& texture, int x, int y, int width, int height)
	{
		SDL_Rect rect {x, y, width, height};
		SDL_RenderCopy(handle(), texture.handle(), nullptr, &rect);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(handle());
	}

	SDL_Renderer* Renderer::handle() const
	{
		return m_renderer.get();
	}
}