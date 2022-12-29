#pragma once
#include "pointers.hpp"
namespace big
{
	

	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetForegroundWindow() == g_pointers->m_hwnd)
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}

		return false;
	}
	class MemoryStreamBuf : public std::streambuf
	{
	public:
		MemoryStreamBuf(char* array, std::size_t size)
		{
			std::fill_n(array, size, '\0');
			std::streambuf::setp(array, array + size - 1);
		}

		template <std::size_t size>
		MemoryStreamBuf(char(&array)[size]) :
			MemoryStreamBuf(&array[0], size)
		{
		}
	};

	/**
	 * \brief An input/output stream that uses a char[] buffer
	 */
	class MemoryStringStream : virtual MemoryStreamBuf, public std::iostream
	{
	public:
		MemoryStringStream(char* array, std::size_t size) :
			MemoryStreamBuf(array, size),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}

		template <std::size_t size>
		MemoryStringStream(char(&array)[size]) :
			MemoryStreamBuf(array),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}
	};

	/**
	 * \brief A MemoryStringStream with a built in buffer
	 */
	template <std::size_t N>
	class MemoryStringStreamWithBuffer : public MemoryStringStream
	{
	public:
		MemoryStringStreamWithBuffer() :
			MemoryStringStream(m_Buffer)
		{}
	private:
		char m_Buffer[N];
	};

	inline constexpr char ToLower(const char c)
	{
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}

	class Timer
	{
	public:
		explicit Timer(std::chrono::milliseconds delay) :
			m_Timer(std::chrono::high_resolution_clock::now()),
			m_Delay(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(delay))
		{
		}

		bool Update()
		{
			auto now = std::chrono::high_resolution_clock::now();
			if ((now.time_since_epoch() - m_Timer.time_since_epoch()).count() >= m_Delay.count())
			{
				m_Timer = now;
				return true;
			}

			return false;
		}

		void SetDelay(std::chrono::milliseconds delay)
		{
			m_Delay = delay;
		}
	private:
		std::chrono::high_resolution_clock::time_point m_Timer;
		std::chrono::high_resolution_clock::duration m_Delay;
	};
	/**
 * \brief Calculates JOAAT hash of string at compile time
 */
	template <std::size_t CharCount>
	struct ConstexprJooat
	{
		char data[CharCount];

		template <std::size_t... Indices>
		constexpr ConstexprJooat(const char* str, std::index_sequence<Indices...>) :
			data{ (str[Indices])... }
		{
		}

		constexpr std::uint32_t GetHash()
		{
			std::uint32_t hash = 0;

			for (std::size_t i = 0; i < CharCount; ++i)
			{
				hash += ToLower(data[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}

			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);

			return hash;
		}
	};

	/**
	 * \brief Hashes a string with the Jenkins-one-at-a-time hash function
	 * \param str The string to be hashed
	 * \return Hash of str
	 */
	inline constexpr std::uint32_t Joaat(const char* str)
	{
		std::uint32_t hash = 0;
		while (*str)
		{
			hash += ToLower(*str++);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

#	define CONSTEXPR_JOAAT_IMPL(x) (::big::ConstexprJooat<sizeof(x) - 1>((x), std::make_index_sequence<sizeof(x) - 1>()).GetHash())
#	define CONSTEXPR_JOAAT(x) (std::integral_constant<std::uint32_t, CONSTEXPR_JOAAT_IMPL(x)>::value)

}
