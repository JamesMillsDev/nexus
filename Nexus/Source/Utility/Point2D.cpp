#include <Nexus/Utility/Point2D.h>

namespace Nexus
{
	Point2D Point2D::one = { 1.f };
	Point2D Point2D::zero = { 0.f };
	Point2D Point2D::half = { .5f };

	Point2D::Point2D()
		: x{ 0.f }, y{ 0.f }
	{
	}

	Point2D::Point2D(const float _scalar)
		: x{ _scalar }, y{ _scalar }
	{
	}

	Point2D::Point2D(const float _x, const float _y)
		: x{ _x }, y{ _y }
	{
	}

	Point2D::Point2D(float _values[POINT_2D_SIZE])
	{
		for(uint i = 0; i < POINT_2D_SIZE; ++i)
			data[i] = _values[i];
	}

	Point2D::Point2D(const Point2D& _other) = default;

	Point2D::Point2D(Point2D&& _other) noexcept
		: x{ _other.x }, y{ _other.y }
	{
		_other.x = 0.f;
		_other.y = 0.f;
	}

	Point2D::~Point2D() = default;

	bool Point2D::operator==(const Point2D& _other) const
	{
		return Maths::Compare(x, _other.x) && Maths::Compare(y, _other.y);
	}

	bool Point2D::operator!=(const Point2D& _other) const
	{
		return !(*this == _other);
	}

	Point2D Point2D::operator-(const Point2D& _other) const
	{
		return { x - _other.x, y - _other.y };
	}

	Point2D& Point2D::operator-=(const Point2D& _other)
	{
		if (*this == _other)
			return *this;

		x -= _other.x;
		y -= _other.y;

		return *this;
	}

	Point2D Point2D::operator+(const Point2D& _other) const
	{
		return { x + _other.x, y + _other.y };
	}

	Point2D& Point2D::operator+=(const Point2D& _other)
	{
		if (*this == _other)
			return *this;

		x += _other.x;
		y += _other.y;

		return *this;
	}

	Point2D& Point2D::operator=(const Point2D& _other) = default;

	Point2D& Point2D::operator=(Point2D&& _other) noexcept
	{
		if (*this == _other)
			return *this;

		x = _other.x;
		y = _other.y;

		_other.x = 0.f;
		_other.y = 0.f;

		return *this;
	}
}
