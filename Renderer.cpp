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

	void Renderer::drawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(handle(), x1, y1, x2, y2);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(handle());
	}

	SDL_Renderer* Renderer::handle() const
	{
		return m_renderer.get();
	}

	void Renderer::drawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		SDL_SetRenderDrawColor(handle(), r, g, b, a);
	}
}