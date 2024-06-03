#include <Nexus/Collections/HashFunctions.h>

namespace Nexus
{
	uint BKDR(const char* _str)
	{
		uint hash = 0;
		for (const char* c = _str; *c != '\0'; ++c)
			hash = hash * 1313 + *c;

		return hash;
	}

	uint ELF(const char* _str)
	{
		unsigned int hash = 0, x = 0;
		for (const char* c = _str; *c != '\0'; ++c)
		{
			hash = (hash << 4) + *c;
			if ((x = hash & 0xF0000000L) != 0) 
			{
				hash ^= (x >> 24);
				hash &= ~x;
			}
		}
		return (hash & 0x7FFFFFFF);
	}
}
