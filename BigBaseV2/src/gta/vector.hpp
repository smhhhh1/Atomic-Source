#pragma once
namespace big {
#pragma pack(push, 1)
	typedef struct
	{
		float x;
		DWORD _paddingx;
		float y;
		DWORD _paddingy;
		float z;
		DWORD _paddingz;
	} tVector3;
#pragma pack(pop)
#pragma pack(push, 1)
	struct Color
	{
		std::uint8_t r{ 255 };
		std::uint8_t g{ 255 };
		std::uint8_t b{ 255 };
		std::uint8_t a{ 255 };
	};
#pragma pack(pop)
#pragma pack(push, 1)
	struct Vector2
	{
		float x{};
		float y{};
	};
#pragma pack(pop)
}

namespace rage
{
	struct vector2
	{
		float x{};
		float y{};
	};

#pragma pack(push, 1)
	class scrVector
	{
	public:
		scrVector() = default;

		float Length() const { return sqrt(x * x + y * y + z * z); }

		scrVector(float x, float y, float z) :
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char m_padding1[0x04];
	public:
		float y{};
	private:
		char m_padding2[0x04];
	public:
		float z{};
	private:
		char m_padding3[0x04];
	};
#pragma pack(pop)
}
namespace rage
{
	template<typename T>
	union vector3
	{
		T data[3];
		struct { T x, y, z; };
	};

	template<typename T>
	union vector4
	{
		T data[4];
		struct { T x, y, z, w; };
	};

	typedef vector3<float> fvector3;
	typedef vector4<float> fvector4;
}
