#pragma once
#include "Engine.h"

//#############################################################################
//# Impact data struct, keeps track of all impacts and their animations:      #
//#############################################################################

namespace pld {
	class Impact {
	public:
		olc::vf2d pos = { 0, 0 };
		int sprite = 0;
		float frames = 0.0f;
		bool to_be_deleted = false;
		Impact(olc::vf2d pos) {
			this->pos = pos;
		}
		bool operator== (const Impact& that) const {
			return (this->pos.x == that.pos.x) && (this->pos.y == that.pos.y);
		}
		friend bool operator== (const Impact& lhs, const Impact& rhs);
		void operator = (const Impact& that) {
			this->pos = that.pos;
			this->sprite = that.sprite;
			this->to_be_deleted = that.to_be_deleted;
		}
	};
}
