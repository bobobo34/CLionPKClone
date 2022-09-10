#include "effects.h"

namespace effects {
    enum class major_effects {
        poison,
        burn,
        frozen,
        paralyze,
        sleep,
        toxic
    };
    enum class minor_effects{
        curse,
        confusion,
        attraction,
        flinch,
        trapped,
        leech_seed,
        nightmare,
        taunt,
        torment,
        perish_song
    };

    template<major_effects Effect>
	constexpr void apply_major(pokemon::pokemon& enemy) {
		enemy.major_effect = Effect;
	}
    template<minor_effects Effect>
    constexpr void apply_minor(pokemon::pokemon& enemy) {
        enemy.minor_effects.push(Effect);
    }
}