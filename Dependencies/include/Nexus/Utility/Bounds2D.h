#pragma once

namespace Nexus
{
	/* A utility bounding box class used in the QuadTree types.*/
	class Bounds2D
	{
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
		/* Returns the x component of the bounds as a non-constant value. */
		float X();
		/* Returns the y component of the bounds as a non-constant value. */
		float Y();
		/* Returns the width component of the bounds as a non-constant value. */
		float Width();
		/* Returns the height component of the bounds as a non-constant value. */
		float Height();

		/* Returns the x component of the bounds as a constant value. */
		[[nodiscard]] float X() const;
		/* Returns the y component of the bounds as a constant value. */
		[[nodiscard]] float Y() const;
		/* Returns the width component of the bounds as a constant value. */
		[[nodiscard]] float Width() const;
		/* Returns the height component of the bounds as a constant value. */
		[[nodiscard]] float Height() const;

		/**
		 * Sets the x location component of the bounds to the passed value.
		 * @param _x The new x location of the bounds.
		 */
		void SetX(float _x);
		/**
		 * Sets the y location component of the bounds to the passed value.
		 * @param _y The new y location of the bounds.
		 */
		void SetY(float _y);
		/**
		 * Sets the width component of the bounds to the passed value.
		 * @param _w The new width of the bounds.
		 */
		void SetWidth(float _w);
		/**
		 * Sets the height component of the bounds to the passed value.
		 * @param _h The new height of the bounds.
		 */
		void SetHeight(float _h);

	public:
		bool operator==(const Bounds2D& _other) const;
		bool operator!=(const Bounds2D& _other) const;

		Bounds2D& operator=(const Bounds2D& _other);
		Bounds2D& operator=(Bounds2D&& _other) noexcept;

	private:
		/* The horizontal location of the bounds. */
		float m_x;
		/* The vertical location of the bounds. */
		float m_y;
		/* The horizontal size of the bounds. */
		float m_width;
		/* The vertical size of the bounds. */
		float m_height;

	};
}