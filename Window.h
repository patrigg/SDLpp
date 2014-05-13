#pragma once
#include <memory>
#include <string>
#include "GLContext.h"

struct SDL_Window;

namespace sdl
{
	class Window
	{
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window;
	public:
		enum Flags{
			Fullscreen = 0x00000001,         /**< fullscreen window */
			OpenGL = 0x00000002,             /**< window usable with OpenGL context */
			Shown = 0x00000004,              /**< window is visible */
			Hidden = 0x00000008,             /**< window is not visible */
			Borderless = 0x00000010,         /**< no window decoration */
			Resizable = 0x00000020,          /**< window can be resized */
			Minimized = 0x00000040,          /**< window is minimized */
			Maximized = 0x00000080,          /**< window is maximized */
			InputGrabbed = 0x00000100,      /**< window has grabbed input focus */
			InputFocus = 0x00000200,        /**< window has input focus */
			MouseFocus = 0x00000400,        /**< window has mouse focus */
			FullscreenDesktop = (Fullscreen | 0x00001000),
			Foreign = 0x00000800,            /**< window not created by SDL */
			AllowHighDPI = 0x00002000       /**< window should be created in high-DPI mode if supported */
		};

		Window(const std::string& title, int x, int y, int width, int height, Flags flags);

		SDL_Window* handle() const;

		void swap();
	};

	Window::Flags operator|(Window::Flags lhs, Window::Flags rhs);
	Window::Flags operator&(Window::Flags lhs, Window::Flags rhs);
}
