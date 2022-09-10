#pragma once
#ifndef EFFECTS_H
#define EFFECTS_H
#include "pktypes/pktypes.hpp"
#include "moves/moves.h"
#include "pokemon/pokemon.hpp"

namespace effects {
    enum class major_effects;
    enum class minor_effects;

    template<major_effects Effect>
    constexpr void apply_major(pokemon::pokemon &enemy);

    template<minor_effects Effect>
    constexpr void apply_minor(pokemon::pokemon &enemy);
}
#endif