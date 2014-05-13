#include "stdafx.h"
#include "Texture.h"
#include "Renderer.h"

namespace sdl
{

	namespace {
		SDL_TextureAccess toNativeAccess(Texture::Access access)
		{
			return static_cast<SDL_TextureAccess>(access);
		}

		Uint32 toNativeFormat(Texture::Format format)
		{
			switch (format)
			{
			case Texture::RGB8:
					return SDL_PIXELFORMAT_RGB888;
				default:
					throw std::exception("pixelformat not supported");
			}
		}
	}

	Texture::Texture(const Renderer& renderer, Format format, Access access, int width, int height)
		: m_texture(SDL_CreateTexture(renderer.handle(), toNativeFormat(format), toNativeAccess(access), width, height),
					SDL_DestroyTexture),
		m_width(width),
		m_height(height)
	{
	}

	Texture::LockedPixels::LockedPixels(Texture* texture, int x, int y, int width, int height)
		: m_texture(texture), m_x(x), m_y(y), m_width(width), m_height(height)
	{
		SDL_Rect rect{ x, y, width, height };
		SDL_LockTexture(m_texture->m_texture.get(), &rect, &m_pixels, &m_pitch);
	}

	Texture::LockedPixels::~LockedPixels()
	{
		unlock();
	}

	Texture::LockedPixels Texture::lock()
	{
		return lock(0, 0, m_width, m_height);
	}

	Texture::LockedPixels Texture::lock(int x, int y, int width, int height)
	{
		return LockedPixels(this, x, y, width, height);
	}

	Texture::LockedPixels::LockedPixels(LockedPixels&& rhs)
	{
		copy(rhs);
		rhs.clear();
	}

	Texture::LockedPixels& Texture::LockedPixels::operator= (LockedPixels&& rhs)
	{
		unlock();
		copy(rhs);
		rhs.clear();
		return *this;
	}

	void Texture::LockedPixels::unlock()
	{
		if (m_texture)
		{
			SDL_UnlockTexture(m_texture->m_texture.get());
		}
	}

	void Texture::LockedPixels::copy(const LockedPixels& rhs)
	{
		m_texture = rhs.m_texture;
		m_pitch = rhs.m_pitch;
		m_pixels = rhs.m_pixels;
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_width = rhs.m_width;
		m_height = rhs.m_height;
	}

	void Texture::LockedPixels::clear()
	{
		m_texture = nullptr;
		m_pitch = 0;
		m_pixels = nullptr;
		m_x = 0;
		m_y = 0;
		m_width = 0;
		m_height = 0;
	}

	SDL_Texture* Texture::handle() const
	{
		return m_texture.get();
	}

	Texture::Texture(Texture&& rhs)
		: m_texture(std::move(rhs.m_texture))
	{
		m_width = std::move(rhs.m_width);
		m_height = std::move(rhs.m_height);
	}

	Texture& Texture::operator = (Texture&& rhs)
	{
		m_texture = std::move(rhs.m_texture);
		m_width = std::move(rhs.m_width);
		m_height = std::move(rhs.m_height);

		return *this;
	}

	int Texture::width() const
	{
		return m_width;
	}

	int Texture::height() const
	{
		return m_height;
	}
}