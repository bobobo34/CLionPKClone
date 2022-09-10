#pragma once
#ifndef POKEMON_HPP
#define POKEMON_HPP
#include "pktypes/pktypes.hpp"
#include "effects/effects.h"
#include <string>
#include <vector>
#include <array>
#include "moves/moves.h"
namespace pokemon {
	//create pokemon struct with array of four moves, name, private level, major_effect, array of minor effects
	struct pokemon {
		std::string name;
		pktypes::pktype type;
		double level;
		effects::major_effects major_effect;
		std::vector<effects::minor_effects> minor_effects;
		std::array<pkmoves::move, 4> moves;
	};
}

#endif