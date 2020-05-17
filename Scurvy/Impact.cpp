#include "Impact.h"

bool pld::operator==(const Impact& lhs, const Impact& rhs)
{
	return (lhs.pos.x == rhs.pos.x) && (lhs.pos.y == rhs.pos.y);
}
