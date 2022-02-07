#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Math/Vector2.h"
#include "Vector3.h"

TEST_CASE("Testing Vector2 functionality")
{
	SUBCASE("Construction")
	{
		/// Default constructor
		const Vector2 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);

		/// Constructor from components
		const Vector2 v1(9.1f, -3.0f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);

		/// Constructor from components
		const Vector2 v2(4.3f);
		CHECK(v2.x == 4.3f);
		CHECK(v2.y == 4.3f);

		/// Copy construction
		Vector2 v3(v2);
		CHECK(v2.x == v3.x);
		CHECK(v2.y == v3.y);

		/// Zero all the components of the vector
		v3.Clear();
		CHECK(v0.x == v3.x);
		CHECK(v0.y == v3.y);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector2 v0(2.3f, 3.7f);
		const Vector2 v1(-6.6f, 1.2f);
		const float factor = 3.5f;
		Vector2 v2;

		/// Returns the value of the given vector added to this.
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);

		/// Returns the value of the given vector subtracted from this.
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);

		SUBCASE("Vector and scalar multiplication.")
		{
			/// Returns a copy of this vector scaled the given value.
			v2 = v1 * factor;
			CHECK(v2.x == v1.x * factor);
			CHECK(v2.y == v1.y * factor);

			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
			v2 = factor * v0;
			CHECK(v2.x == v0.x * factor);
			CHECK(v2.y == v0.y * factor);
		}

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == v0.x / factor);
		CHECK(v2.y == v0.y / factor);

		SUBCASE("Dot product calculation.")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			const float dot = v0 * v1;
			CHECK(-10.74f == dot);

			const float calculatedDot = v0.Dot(v1);
			CHECK(dot == calculatedDot);
		}

		/// Adds the given vector to this.
		SUBCASE("Adds the given vector to this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 += v0;
			CHECK(v3.x == v0.x + 3.0f);
			CHECK(v3.y == v0.y + -4.0f);
		}

		/// Subtracts the given vector from this
		SUBCASE("Subtracts the given vector from this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 -= v1;
			CHECK(v3.x == 3.0f - v1.x);
			CHECK(v3.y == -4.0f - v1.y);
		}

		/// Multiplies this vector by the given scalar
		SUBCASE("Multiplies this vector by the given scalar.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 *= factor;
			CHECK(v3.x == 3.0f * factor);
			CHECK(v3.y == -4.0f * factor);
		}
	}

	SUBCASE("Logical operators")
	{
		/// Checks if the two vectors have identical components
		const float x = 2.93f;
		const float y = 4.39f;
		Vector2 v0(x, y);
		Vector2 v1(x, y);
		Vector2 v2(y, x);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}

	SUBCASE("Length operations")
	{
		Vector2 v0(3.0f, 4.0f);

		/// Gets the magnitude of this vector
		const float vectorLenght = v0.Magnitude();
		CHECK(vectorLenght == 5.0f);

		/// Gets the squared magnitude of this vector
		const float vectorLenghtSq = v0.SquareMagnitude();
		CHECK(vectorLenghtSq == 25.0f);

		/// Limits the size of the vector to the given maximum
		v0.Trim(2.5f);
		CHECK(2.5f == v0.Magnitude());

		/// Returns the normalised version of a vector
		Vector2 v1 = v0;
		Vector2 v2 = v1.Unit();
		CHECK(v1 == v0);
		CHECK(1.0f == v2.Magnitude());

		/// Turns a non-zero vector into a vector of unit length
		v0.Normalize();
		CHECK(1.0f == v0.Magnitude());
	}
}

TEST_CASE("Testing Vector3 functionality")
{
	SUBCASE("Construction")
	{
		/// The default constructor creates a zero vector.
		const Vector v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);
		CHECK(v0.z == 0.0f);

		/// Creates a vector with the given components
		const Vector v1(6.1f, -4.0f, 8.4f);
		CHECK(v1.x == 6.1f);
		CHECK(v1.y == -4.0f);
		CHECK(v1.z == 8.4f);

		/// Zero all the components of the vector
		Vector v2(v1);
		v2.Clear();
		CHECK(v0.x == v2.x);
		CHECK(v0.y == v2.y);
		CHECK(v0.z == v2.z);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector v0(2.3f, 3.7f, 4.4f);
		const Vector v1(-6.6f, 1.2f, 2.3f);
		const float factor = 3.5f;
		Vector v2;

		/// Returns the value of the given vector added to this
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);

		/// Returns the value of the given vector subtracted from this
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);

		/// Returns a copy of this vector scaled the given value
		v2 = v1 * factor;
		CHECK(v2.x == v1.x * factor);
		CHECK(v2.y == v1.y * factor);
		CHECK(v2.z == v1.z * factor);

		/// Returns a copy of this vector scaled the inverse of the value

		/// Returns the negative this vector
		Vector v3(-1.0, 2.0, 3.0);
		v3.negative();
		CHECK(v3.x == 1.0);
		CHECK(v3.y == -2.0);
		CHECK(v3.z == -3.0);

		/// Adds the given vector to this
		Vector v5(-1.0, 2.0, 3.0);
		Vector v4(2.0, 4.0, 3.0);
		v5 += v4;
		CHECK(v5.x == v4.x - 1.0f);
		CHECK(v5.y == v4.y + 2.0f);
		CHECK(v5.z == v4.z + 3.0f);

		/// Subtracts the given vector from this
		Vector v6(-1.0, 2.0, 3.0);
		Vector v7(2.0, 4.0, 3.0);
		v6 -= v7;
		CHECK(v6.x == -1.0 - v7.x);
		CHECK(v6.y == 2.0 - v7.y);
		CHECK(v6.z == 3.0 - v7.z);

		/// Multiplies this vector by the given scalar
		v7 *= 2.0;
		CHECK(v7.x == 2.0 * 2.0);
		CHECK(v7.y == 4.0 * 2.0);
		CHECK(v7.z == 3.0 * 2.0);


		SUBCASE("Vector products")
		{
			Vector v0(1.0f, 2.0f, -3.0f);
			Vector v1(2.0f, 3.0f, 4.0f);
			Vector v2(17.0f, -10.0f, -1.0f);

			/// Calculates and returns the dot product of this with the given vector
			CHECK(-4.0 == dot(v0, v1));

			/// Calculates and returns the cross product of this vector with the given vector
			Vector v3;
			v3 = cross(v0, v1);
			CHECK(v3.x == v2.x);
			CHECK(v3.y == v2.y);
			CHECK(v3.z == v2.z);

		}

		SUBCASE("Length operations")
		{
			Vector v0(1.0f, 2.0f, -2.0f);
			Vector v1(1.4f, 2.8f, -2.6f);

			///  Gets the magnitude of this vector
			CHECK(std::sqrt(9.0f) == v0.length());

			///  Gets the squared magnitude of this vector
			CHECK(9.0f == v0.length2());

			/// Turns a non-zero vector into a vector of unit length
			v0.normalize();
			CHECK(1.0f == v0.length());

			/// Returns the normalised version of a vector
			CHECK(1.0f == v1.normalized().length());
		}
	}

	SUBCASE("Logical operations")
	{
		const float x = 2.93f;
		const float y = 4.39f;
		const float z = 3.27f;
		Vector v0(x, y, z);
		Vector v1(x, y, z);
		Vector v2(y, x, z);

		/// Checks if the two vectors have identical components
		CHECK(v0 == v1);

		/// Checks if the two vectors have non-identical components
		CHECK(v2 != v0);
	}
}


TEST_CASE("Testing Matrix33 functionality")
{
	SUBCASE("Construction")
	{
		/// Construct a new matrix from explicit values
		/// Construct a new identity matrix

		/// Creates an identity matrix
		/// Creates a translation matrix
		/// Creates a scale matrix
		/// Creates a uniform scale matrix

		/// Creates a rotation matrix around an arbitrary axis (angle in radians)
		/// Creates a rotation matrix around the x axis (angle in radians)
		/// Creates a rotation matrix around the y axis (angle in radians)
		/// Creates a rotation matrix around the z axis (angle in radians)
	}

	SUBCASE("Mathematical operations")
	{
		/// Matrix addition
		/// Matrix subtraction
		/// Matrix multiplication

		SUBCASE("Inversion")
		{
			/// Get the determinant of this matrix
			/// Inverts this matrix
			/// Transposes this matrix
		}
	}

	/// Get the x axis 
	/// Get the y axis 
	/// Get the z axis 
}

TEST_CASE("Testing Matrix44 functionality")
{
	SUBCASE("Construction")
	{
		/// Construct a new matrix from explicit values
		/// Construct a new identity matrix

		/// Creates an identity matrix
		/// Creates a translation matrix
		/// Creates a scale matrix
		/// Creates a uniform scale matrix

		/// Creates a rotation matrix around an arbitrary axis (angle in radians)
		/// Creates a rotation matrix around the x axis (angle in radians)
		/// Creates a rotation matrix around the y axis (angle in radians)
		/// Creates a rotation matrix around the z axis (angle in radians)
		/// Creates an orthographic projection matrix
		/// Creates a frustum projection matrix
		/// Creates a perspective projection matrix from camera settings
		/// Creates a look at matrix, usually a view matrix  
	}

	SUBCASE("Mathematical operations")
	{
		/// Matrix addition
		/// Matrix subtraction
		/// Matrix multiplication

		SUBCASE("Inversion")
		{
			/// Get the determinant of this matrix
			/// Inverts this matrix
			/// Transposes this matrix
		}
	}

	SUBCASE("Transformation")
	{
		/// Transform the given vector by this matrix.
		/// Transform the direction vector of this matrix
	}

	/// Retrieve translation part of the matrix
	/// Set the translation of the matrix
	/// Get the x orientation axis 
	/// Get the y orientation axis 
	/// Get the z orientation axis 

	/// Sets the orientation of the matrix to the orthogonal basis vector
}

