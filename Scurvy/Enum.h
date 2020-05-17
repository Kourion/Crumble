#pragma once

namespace pld {
	enum class State {
		Titlescreen,
		Level,
		LevelUp,
		Ease,
		Highscore,
		Settings
	};

	enum class PaddleShape {
		Flat,
		Welled,
		Pyramid
		//??? Need creative ideas ...
	};

	enum class Directions {
		Up,
		Down,
		Left,
		Right,
		Stationary
	};

	enum class CollisionType {
		Ceiling,
		Floor,
		WallLeft,
		WallRight,
		Frame,
		Wall,
		Paddle,
		BoxTop,
		BoxSide,
		Water,
		NoCollision
	};

	enum class Ease {
		Normal,
		Hard,
		BoR // Bottle of Rum
	};

}
