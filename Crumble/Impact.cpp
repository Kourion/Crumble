#include "Impact.h"

//#############################################################################
//# Auxillary friend functions for "Impact" object:                           #
//#############################################################################

bool pld::operator==(const Impact& lhs, const Impact& rhs)
{
	return (lhs.pos.x == rhs.pos.x) && (lhs.pos.y == rhs.pos.y);
}
