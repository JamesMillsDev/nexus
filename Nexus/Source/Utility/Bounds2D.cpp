#include <Nexus/Utility/Bounds2D.h>

#include <cfloat>
#include <corecrt_math.h>

namespace Nexus
{
	bool Compare(const float _x, const float _y)
	{
		return fabsf(_x - _y) <= (FLT_EPSILON + 0.000001f) * fmaxf(1.f, fmaxf(fabsf(_x), fabsf(_y)));
	}

	Bounds2D::Bounds2D()
		: m_x{ 0.f }, m_y{ 0.f }, m_width{ 1.f }, m_height{ 1.f }
	{
	}

	Bounds2D::Bounds2D(const float _x, const float _y, const float _w, const float _h)
		: m_x{ _x }, m_y{ _y }, m_width{ _w }, m_height{ _h }
	{
	}

	Bounds2D::Bounds2D(const Bounds2D& _other) = default;

	Bounds2D::Bounds2D(Bounds2D&& _other) noexcept
		: m_x{ _other.m_x }, m_y{ _other.m_y }, m_width{ _other.m_width }, m_height{ _other.m_height }
	{
		_other.m_x = 0.f;
		_other.m_y = 0.f;
		_other.m_width = 0.f;
		_other.m_height = 0.f;
	}

	Bounds2D::~Bounds2D() = default;

	float Bounds2D::X()
	{
		return m_x;
	}

	float Bounds2D::Y()
	{
		return m_y;
	}

	float Bounds2D::Width()
	{
		return m_width;
	}

	float Bounds2D::Height()
	{
		return m_height;
	}

	float Bounds2D::X() const
	{
		return m_x;
	}

	float Bounds2D::Y() const
	{
		return m_y;
	}

	float Bounds2D::Width() const
	{
		return m_width;
	}

	float Bounds2D::Height() const
	{
		return m_height;
	}

	void Bounds2D::SetX(const float _x)
	{
		m_x = _x;
	}

	void Bounds2D::SetY(const float _y)
	{
		m_y = _y;
	}

	void Bounds2D::SetWidth(const float _w)
	{
		m_width = _w;
	}

	void Bounds2D::SetHeight(const float _h)
	{
		m_height = _h;
	}

	bool Bounds2D::operator==(const Bounds2D& _other) const
	{
		return Compare(m_x, _other.m_x) && Compare(m_y, _other.m_y) &&
			Compare(m_width, _other.m_width) && Compare(m_height, _other.m_height);
	}

	bool Bounds2D::operator!=(const Bounds2D& _other) const
	{
		return !(*this == _other);
	}

	Bounds2D& Bounds2D::operator=(const Bounds2D& _other) = default;

	Bounds2D& Bounds2D::operator=(Bounds2D&& _other) noexcept
	{
		if (*this == _other)
			return *this;

		m_x = _other.m_x;
		m_y = _other.m_y;
		m_width = _other.m_width;
		m_height = _other.m_height;

		_other.m_x = 0.f;
		_other.m_y = 0.f;
		_other.m_width = 0.f;
		_other.m_height = 0.f;

		return *this;
	}
}
