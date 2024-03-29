/******************************************************************************
*
* COPYRIGHT Vin�cius G. Mendon�a ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vin�cius G.Mendon�a prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autoriza��o 
* a priori de Vin�cius G. Mendon�a
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribui��o seguindo a licen�a Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

/* Vin�cius Godoy de Mendon�a */
#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <iostream>
#include "MathUtil.h"

namespace math
{
    /**
        This class represents a 2 coordinate space mathematical vector.
        All operations expected for a vector, like sum, subtraction, product,
        dot product and normalization are provided.

		Also, a set of useful functions are also provided, to more complex operations
		like reflex, truncation, distance. Functions also provide a non-mutable version
		of methods.
    */
    class Vector2D
    {
        public:
            float x;
            float y;
			
            /** Builds a NULL vector */
            Vector2D();
            /** Builds a vector based in it's x and y components */
            explicit Vector2D(float aX, float anY);

            /** Builds a vector based in a two dimensional array */
            explicit Vector2D(float xy[2]);

            /** Builds a vector based in it's size (magnitude) and angle 
			with x axis (counter-clockwise) */
            static Vector2D newBySizeAngle(float size, float radians);

            /** Changes the x and y values */
            Vector2D& set(float x, float y);

            /** Changes the x and y values */
            Vector2D& set(const Vector2D& other);

            /** Changes the x and y values */
            Vector2D& set(const float xy[2]);

            /** Retrieves the size of this vector squared */
            float sizeSqr() const;

            /** Retrieves this vector magnitude */
            float size() const;

            /** Returns the relative angle of the vector in relation to the x
			 * axis, in a counter-clockwise rotation. That is, 90 degrees is
             * a vector pointing up and 0 degrees is a vector pointing right. 
			 */
            float angle() const;

            /** Rotates this vector in counter-clockwise direction */
            Vector2D& rotate(float radians);

            /** Sets this vector size to 1. */
            Vector2D& normalize();

			/** Sets this vector size */
			Vector2D& resize(float size);

            /** Adds this vector to another vector */
            Vector2D& operator += (const Vector2D& other);

            /** Subtracts this vector from another vector */
            Vector2D& operator -= (const Vector2D& other);

            /** Multiplies the magnitude of this vector to a constant */
            Vector2D& operator *= (float c);

            /** Divides this vector magnitude by a constant*/
            Vector2D& operator /= (float c);

            /** Negates this vector.
            * Same as rotating the vector in 180� but much faster. */
            Vector2D operator -(void) const;
            Vector2D operator +(const Vector2D& other) const;
            Vector2D operator -(const Vector2D& other) const;

            Vector2D operator *(float c) const;
            Vector2D operator /(float c) const;

            float operator[] (long index) const;
            float& operator[] (long index);

            bool operator ==(const Vector2D& other) const;
			bool operator !=(const Vector2D& other) const;			
			
			/**
			 * Returns the dot product between this vector and the other one.
			 */
            float dot(const Vector2D& other) const;

			/**
			 * Return the relative angle between 2 vectors.
			 * For normalized vectors, prefer the dot product instead.
			 */
            float relativeAngleBetween(const Vector2D other) const;

			/**
			 * Returns true if it's the zero vector (size == 0)
			 */
			inline bool isZero() const { return equals(x, 0) && equals(y, 0); }

			/**
			 * Returns true if it's a unit vector (size == 1)
			 */
			inline bool isUnit() const { return equals(size(), 1); }
    };

	Vector2D operator*(float scalar, const Vector2D& vector);

	/**
	 * @return the squared distance between two vectors
	 * @see distance
	 */
	inline float distanceSqr(const Vector2D& p1, const Vector2D& p2)
	{
		return (p1 - p2).sizeSqr();
	}

	/**
	 * @return the distance between two vectors
	 * @see distanceSqr
	 */
	inline float distance(const Vector2D& p1, const Vector2D& p2)
	{
		return (p1 - p2).size();
	}
	
	/**
	 * Test if two vectors are orthogonal to each other.
	 * Two vector are orthogonal if the angle between than is 90� or if any 
	 * them is the zero vector.
	 * @return True if they are orthogonal.
	 */
	inline bool areOrthogonal(const Vector2D& a, const Vector2D& b)
	{
		return equals(a.dot(b), 0);
	}

	/**
	 * @return the counter-clockwise perpenticular copy of vector of v. 
	 */
	inline Vector2D perp(const Vector2D& v)
	{
		return Vector2D(-v.y, v.x);
	}

	/**
	 * @return the dot product between the perpendicular of a and the vector b.
	 * @see perp(const Vector2D&)
	 */
	inline float perpDot(const Vector2D& a, const Vector2D& b)
	{
		return perp(a).dot(b);
	}

	/**
	 * Returns a clockwise direction rotated copy of v.
	 * @param v The vector to rotate
	 * @param radians The angle, in radians.
	 * @return A rotated copy of v.
	 */
	inline Vector2D rotate(const Vector2D& v, float radians)
	{
		return Vector2D(v).rotate(radians);
	}

	/**
	 * @return a resized copy of v.
	 */
	inline Vector2D resize(const Vector2D& v, float size)
	{
		return Vector2D(v).resize(size);
	}

	/**
	 * @param v A vector
	 * @param size Maximum size of the returning vector
	 * 
	 * @return If the size if v is greater than size, returns
	 * a resized version of v with the specified size. Otherwise
	 * just return a copy of v.
	 */
	inline Vector2D truncate(const math::Vector2D& v, float size)
	{					
		return (v.sizeSqr() > size * size) ? resize(v, size) : v;
	}

	/**
	 * @return a normalized copy of the given vector
	 */
	inline Vector2D normalize(const Vector2D& v) 
	{ 
		return Vector2D(v).normalize(); 
	}

	/**
	 * @param ray The ray to reflect
	 * @param normal Surface normal
	 * @return The reflection vector
	 */
	inline Vector2D reflect(const Vector2D& ray, const Vector2D& normal) 
	{
		return ray - 2 * ray.dot(normal) * normal;
	}

	std::ostream& operator<<(std::ostream& output, const Vector2D& p);
}


#endif

