#pragma once

#include <Nexus/Utility/Point2D.h>

namespace Nexus
{
	/* A utility bounding box class used in the QuadTree types.*/
	class Bounds2D
	{
	public:
		/* The location of the bounds. */
		Point2D pos;
		/* The size of the bounds. */
		Point2D size;

	public:
		/* Default constructor. Sets x and y to 0, and width and height to 1 */
		Bounds2D();
		/**
		 * Sets the default values of the bounds to the passed values.
		 * @param _x The new value of the x component.
		 * @param _y The new value of the y component.
		 * @param _w The new value of the width component.
		 * @param _h The new value of the height component.
		 */
		Bounds2D(float _x, float _y, float _w, float _h);

		Bounds2D(const Bounds2D& _other);
		Bounds2D(Bounds2D&& _other) noexcept;
		~Bounds2D();

	public:
		/**
		 * Checks if a passed point is within the bounds of the Bounds2D.
		 * @param _x The x position of the point we are testing against.
		 * @param _y The y position of the point we are testing against.
		 */
		[[nodiscard]] bool Contains(float _x, float _y) const;
		/**
		 * Checks if a passed point is within the bounds of the Bounds2D.
		 * @param _point The point we are testing against.
		 */
		[[nodiscard]] bool Contains(const Point2D& _point) const;
		/**
		 * Checks if a passed Bounds2D overlaps with this one.
		 * @param _other The bounding box we are checking against.
		 */
		[[nodiscard]] bool Overlaps(const Bounds2D& _other) const;

	public:
		bool operator==(const Bounds2D& _other) const;
		bool operator!=(const Bounds2D& _other) const;

		Bounds2D& operator=(const Bounds2D& _other);
		Bounds2D& operator=(Bounds2D&& _other) noexcept;

	};
}
