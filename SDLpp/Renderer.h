#pragma once
#include <memory>

struct SDL_Renderer;

namespace sdl
{
	class Window;
	class Texture;

	class Renderer
	{
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_renderer;
	public:
		Renderer(const Window& window);

		void copy(Texture& texture, int x, int y, int width, int height);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void present();

		SDL_Renderer* handle() const;
	};

}