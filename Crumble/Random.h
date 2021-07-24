#pragma once
#include <stdint.h>
#include <random>

//#############################################################################
//# Implementation of a non crypto RNG, using xoroshiro:                      #
//#############################################################################

namespace pld {
	class Random {
	private:
		uint64_t s[2];
		bool initialised = false;
		static inline uint64_t rotl(const uint64_t x, int k) {
			return (x << k) | (x >> (64 - k));
		}
	public:
		Random(uint64_t seed) {
			s[0] = 145731560926067 + seed;
			s[1] = 852339143976053 + seed;
			initialised = true;
		};
		uint64_t operator()(void) {
			const uint64_t s0 = s[0];
			uint64_t s1 = s[1];
			const uint64_t result = rotl(s0 * 5, 7) * 9;

			s1 ^= s0;
			s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
			s[1] = rotl(s1, 37); // c

			return result;
		}
		int operator()(int min, int max) {
			if (max <= min) { return min; }
			return ((*this)() % ((int64_t)max - min + 1)) + min;
		}
		double operator()(double min, double max) {
			if (max <= min) { return min; }
			return ((double)(*this)() / (double)(0x7FFFFFFF)) * (max - min) + min;
		}
		bool operator()(bool a) {
			return ((*this)() & (1 << 16) );
		}

		bool isInit() {
			return initialised;
		}
	};
}
