#pragma once
#include <memory>

struct SDL_Texture;

namespace sdl
{
	class Renderer;

	class Texture
	{
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> m_texture;
		int m_width;
		int m_height;

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
	public:
		enum Format
		{
			RGB8
		};

		enum Access
		{
			Static,
			Streaming//,
			//Target
		};

		Texture(const Renderer& renderer, Format format, Access access, int width, int height);
		Texture(Texture&& rhs);
		Texture& operator = (Texture&& rhs);

		int width() const;
		int height() const;

		template<typename T>
		class Rows;

		class LockedPixels
		{
			Texture* m_texture;
			friend class Texture;
			void* m_pixels;
			int m_pitch;
			int m_width;
			int m_height;
			int m_x;
			int m_y;

			LockedPixels(Texture* texture, int x, int y, int width, int height);
			LockedPixels(const LockedPixels& rhs);
			LockedPixels& operator=(const LockedPixels& rhs);

			void unlock();
			void copy(const LockedPixels& rhs);
			void clear();

		public:
			LockedPixels(LockedPixels&& rhs);

			LockedPixels& operator=(LockedPixels&& rhs);
			~LockedPixels();

			template <typename T>
			Rows<T> rows();
		};

		template <typename T>
		class Rows
		{
			LockedPixels& m_lockedPixels;

		public:
			Rows(LockedPixels& lockedPixels)
				: m_lockedPixels(lockedPixels)
			{
			}

			class Row
			{
				T* m_begin;
				T* m_end;
				int m_offset;

			public:
				Row(T* pixels, int width, int offset)
					: m_begin(pixels), m_end(pixels + width), m_offset(offset)
				{
				}

				T* begin()
				{
					return m_begin;
				}

				T* end()
				{
					return m_end;
				}

				Row& operator += (int rhs)
				{
					m_begin = (T*)(((uint8_t*)m_begin) + m_offset * rhs);
					m_end = (T*)(((uint8_t*)m_end) + m_offset * rhs);
					return *this;
				}

				Row& operator -= (int rhs)
				{
					m_begin = (T*)(((uint8_t*)m_begin) - m_offset * rhs);
					m_end = (T*)(((uint8_t*)m_end) - m_offset * rhs);
					return *this;
				}


				Row& operator ++ ()
				{
					m_begin = (T*)(((uint8_t*)m_begin) + m_offset);
					m_end = (T*)(((uint8_t*)m_end) + m_offset);
					return *this;
				}

				Row& operator -- ()
				{
					m_begin = (T*)(((uint8_t*)m_begin) - m_offset);
					m_end = (T*)(((uint8_t*)m_end) - m_offset);
					return *this;
				}
				Row operator ++ (int)
				{
					Row tmp(*this);
					operator++();
					return tmp;
				}

				Row operator -- (int)
				{
					Row tmp(*this);
					operator--();
					return tmp;
				}

				bool operator == (const Row& rhs)
				{
					return m_begin == rhs.m_begin;
				}

				bool operator != (const Row& rhs)
				{
					return !operator==(rhs);
				}

				Row& operator*()
				{
					return *this;
				}
				
				Row operator+(int rhs)
				{
					return typename Texture::Rows<T>::Row(*this) += rhs;
				}

				
				Row operator-(int rhs)
				{
					return typename Texture::Rows<T>::Row(*this) -= rhs;
				}
			};

			Row begin()
			{
				return Row(static_cast<T*>(m_lockedPixels.m_pixels), m_lockedPixels.m_width, m_lockedPixels.m_pitch);
			}

			Row end()
			{
				return begin() + m_lockedPixels.m_height;
			}
		};


		LockedPixels lock();
		LockedPixels lock(int x, int y, int width, int height);

		SDL_Texture* handle() const;
	};

	template<typename T>
	Texture::Rows<T> Texture::LockedPixels::rows()
	{
		return Texture::Rows<T>(*this);
	}

}