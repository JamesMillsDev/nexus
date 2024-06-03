#pragma once

#include <Nexus/Utility/Maths.h>

namespace Nexus
{
	constexpr uint POINT_2D_SIZE = 2;

	class Point2D
	{
	public:
		union
		{
			struct  // NOLINT(clang-diagnostic-nested-anon-types)
			{
				float x;
				float y;
			};

			float data[POINT_2D_SIZE];
		};

	public:
		static Point2D one;
		static Point2D zero;
		static Point2D half;

	public:
		Point2D();
		Point2D(float _scalar);
		Point2D(float _x, float _y);
		Point2D(float _values[POINT_2D_SIZE]);

		Point2D(const Point2D& _other);
		Point2D(Point2D&& _other) noexcept;

		~Point2D();

	public:
		bool operator==(const Point2D& _other) const;
		bool operator!=(const Point2D& _other) const;

		Point2D operator-(const Point2D& _other) const;
		Point2D& operator-=(const Point2D& _other);

		Point2D operator+(const Point2D& _other) const;
		Point2D& operator+=(const Point2D& _other);

		Point2D operator*(float _other) const;
		Point2D& operator*=(float _other);

		Point2D& operator=(const Point2D& _other);
		Point2D& operator=(Point2D&& _other) noexcept;

	};
}
