#include <Nexus/Utility/Bounds2D.h>
#include <Nexus/Utility/Point2D.h>

#include <algorithm>

namespace Nexus
{
	Bounds2D::Bounds2D()
		: pos{ Point2D::zero }, size{ Point2D::zero }
	{
	}

	Bounds2D::Bounds2D(const float _x, const float _y, const float _w, const float _h)
		: pos{ _x, _y }, size{ _w, _h }
	{
	}

	Bounds2D::Bounds2D(const Bounds2D& _other) = default;

	Bounds2D::Bounds2D(Bounds2D&& _other) noexcept
		: pos{ std::move(_other.pos) }, size{ std::move(_other.size) }
	{
		_other.pos = Point2D::zero;
		_other.size = Point2D::zero;
	}

	Bounds2D::~Bounds2D() = default;

	bool Bounds2D::Contains(const float _x, const float _y) const
	{
		return _x > pos.x && _y > pos.y && _x < pos.x + size.x && _y < pos.y + size.y;
	}

	bool Bounds2D::Contains(const Point2D& _point) const
	{
		return Contains(_point.x, _point.y);
	}

	bool Bounds2D::Overlaps(const Bounds2D& _other) const
	{
		const Point2D vec = pos - _other.pos;
		const Point2D overlap = _other.size + size - Point2D{ fabsf(vec.x), fabsf(vec.y) };

		return overlap.x > 0 && overlap.y > 0;
	}

	bool Bounds2D::operator==(const Bounds2D& _other) const
	{
		return pos == _other.pos && size == _other.size;
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

		pos = std::move(_other.pos);
		size = std::move(_other.size);

		return *this;
	}
}
