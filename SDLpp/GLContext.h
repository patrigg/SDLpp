#pragma once
#include <memory>

namespace sdl
{
	class Window;

	class GLContext
	{
		std::unique_ptr<void, void(*)(void*)> context;
	public:
		GLContext(const Window& window);

		void makeCurrent(const Window& window);
		static void setVersion(int major, int minor);
		
	};

}