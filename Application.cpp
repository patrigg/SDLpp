#include "Application.h"
#include <SDL.h>

namespace sdl
{
	Application::Application()
	{
		SDL_Init(0);
	}


	Application::~Application()
	{
		SDL_Quit();
	}
}