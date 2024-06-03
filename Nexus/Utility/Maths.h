#pragma once

#define EPSILON 1.192092896e-07f
#define PI 3.1415926535f

// ReSharper disable CppInconsistentNaming
typedef unsigned int uint;
typedef unsigned long long ullong;
// ReSharper restore CppInconsistentNaming

namespace Nexus
{
	class Maths
	{
	public:
		static bool Compare(float _x, float _y);

	};
}