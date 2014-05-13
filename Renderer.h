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

		void present();

		SDL_Renderer* handle() const;
	};

}