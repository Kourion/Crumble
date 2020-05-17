#pragma once
#include "Engine.h"
#include "Enum.h"

namespace pld {
	class Bolt {
	private:
		float radius = 640 / 2;
		void switchLeftRight();
		void switchUpDown();
	public:
		// Variables:
		bool is_destroyed = false;
		bool is_launched = false;
		float scale_val = 0.05f;
		float destruction_frame = 0.0f;
		int destruction_sprite = 0;
		float speed = 500.0f;
		float scaled_radius = radius * scale_val;
		float drift = 0.5f;
		pld::Directions up_down = pld::Directions::Stationary;
		pld::Directions left_right = pld::Directions::Stationary;
		olc::vf2d scale = { scale_val, scale_val };
		olc::vf2d pos = { 0.0f, 0.0f };
	public:
		// Methods:
		void updateDirection(CollisionType collision);
		int chooseDecal();
		void deactivate();
		void deactivateSilently();
	};
}
