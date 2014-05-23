#pragma once
namespace sdl
{
	class Application
	{
		Application(const Application& rhs) = delete;
		Application operator=(const Application& rhs) = delete;
	public:
		Application();
		~Application();
	};
}


