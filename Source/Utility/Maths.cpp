#include <Nexus/Utility/Maths.h>

#include <corecrt_math.h>

namespace Nexus
{
	bool Maths::Compare(const float _x, const float _y)
	{
		return fabsf(_x - _y) <= (EPSILON + 0.000001f) * fmaxf(1.f, fmaxf(fabsf(_x), fabsf(_y)));
	}
}
