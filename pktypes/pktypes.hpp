#pragma once
#ifndef PK_TYPES 
#define PK_TYPES
#include <tuple>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>	
#include <iostream>
#include <map>
#include <array>

namespace pktypes {
	/*
	//  namespace for anything to do with the pokemon types
	//	pktype enum is all of the types
	//	typepair is the typedef that will be included in each pokemon
	//	weaknesses, resistances, and immunities are hashmaps of all of the types a certain type defends weakly, stongly, etc.
	//	
	//	CalculateDMG takes in a move type and the defending type pair and returns the damage multiplier
	*/
	enum class pktype {
		normal,
		fire,
		water,
		grass,
		electric,
		ice,
		fighting,
		poison,
		ground,
		flying,
		psychic,
		bug,
		rock,
		ghost,
		dark,
		dragon,
		steel,
		fairy,
		typeless
	};
	constexpr std::array types{
		"normal",
		"fire",
		"water",
		"grass",
		"electric",
		"ice",
		"fighting",
		"poison",
		"ground",
		"flying",
		"psychic",
		"bug",
		"rock",
		"ghost",
		"dark",
		"dragon",
		"steel",
		"fairy",
		"typeless"
	};
	
	using typepair = std::pair<pktype, pktype>;
	using enum pktype;
	using ptypeset = std::set<pktype>;

	const std::unordered_map<pktype, ptypeset> weaknesses = {
		{normal, ptypeset{fighting} },
		{fire, ptypeset{water, ground, rock}},
		{water, ptypeset{electric, grass}},
		{grass, ptypeset{fire, bug, ice, poison, flying}},
		{electric, ptypeset{ground}},
		{ice, ptypeset{fire, fighting, rock, steel}},
		{fighting, ptypeset{flying, psychic, fairy}},
		{poison, ptypeset{ground, psychic}},
		{ground, ptypeset{water, grass, ice}},
		{flying, ptypeset{ice, electric, rock}},
		{psychic, ptypeset{bug, dark, ghost}},
		{bug, ptypeset{fire, rock, flying}},
		{rock, ptypeset{water, grass, fighting, ground, steel}},
		{ghost, ptypeset{ghost, dark}},
		{dark, ptypeset{fighting, fairy, bug}},
		{dragon, ptypeset{ice, dragon, fairy}},
		{steel, ptypeset{ground, fire, fighting}},
		{fairy, ptypeset{poison, steel}}
	};
	const std::unordered_map<pktype, ptypeset> resistances = {
			{normal, ptypeset{} },
			{fire, ptypeset{fire, grass, ice, bug, steel, fairy}},
			{water, ptypeset{fire, water, ice, steel}},
			{grass, ptypeset{water, electric, grass, ground}},
			{electric, ptypeset{electric, flying, steel}},
			{ice, ptypeset{ice}},
			{fighting, ptypeset{bug, rock, dark}},
			{poison, ptypeset{grass, fighting, poison, bug, fairy}},
			{ground, ptypeset{poison, rock}},
			{flying, ptypeset{grass, fighting, bug}},
			{psychic, ptypeset{fighting, psychic}},
			{bug, ptypeset{grass, fighting, ground}},
			{rock, ptypeset{normal, fire, poison, flying}},
			{ghost, ptypeset{poison, bug}},
			{dark, ptypeset{ghost, dark}},
			{dragon, ptypeset{fire, water, electric, grass}},
			{steel, ptypeset{normal, grass, ice, flying, psychic, bug, rock, dragon, steel, fairy}},
			{fairy, ptypeset{fighting, bug, dark}}
	};	
	const std::unordered_map<pktype, ptypeset> immunities = {
		{normal, ptypeset{ghost} },
		{fire, ptypeset{}},
		{water, ptypeset{}},
		{grass, ptypeset{}},
		{electric, ptypeset{}},
		{ice, ptypeset{}},
		{fighting, ptypeset{}},
		{poison, ptypeset{}},
		{ground, ptypeset{electric}},
		{flying, ptypeset{ground}},
		{psychic, ptypeset{}},
		{bug, ptypeset{}},
		{rock, ptypeset{}},
		{ghost, ptypeset{normal, fighting}},
		{dark, ptypeset{psychic}},
		{dragon, ptypeset{}},
		{steel, ptypeset{poison}},
		{fairy, ptypeset{dragon}}
	};

	inline bool isWeakAgainst(pktype& defendingtype, pktype& atktype) {
		auto& weakness = weaknesses.at(defendingtype);
		// weakness is found, return true (not the end)
		return weakness.find(atktype) != weakness.end();
	}
	inline bool isResistant(pktype& defendingtype, pktype& atktype) {
		auto& resistance = resistances.at(defendingtype);
		// weakness is found, return true (not the end)
		return resistance.find(atktype) != resistance.end();
	}
	inline bool isImmune(pktype& defendingtype, pktype& atktype) {
		auto& immunity = immunities.at(defendingtype);
		// weakness is found, return true (not the end)
		return immunity.find(atktype) != immunity.end();
	}
	inline double CalculateDMGSingle(pktype& atk, pktype& def) {
		if (def == typeless || atk == typeless) return 1;

		if (isImmune(def, atk)) return 0;
		else if (isWeakAgainst(def, atk)) return 2;
		else if (isResistant(def, atk)) return 0.5;
		else return 1;
	}
	inline double CalculateDMG(pktype& atktype, typepair& def) {
		double multiplier{ 1 };
		multiplier *= CalculateDMGSingle(atktype, def.first);
		multiplier *= CalculateDMGSingle(atktype, def.second);
		return multiplier;
	}
	
	const ptypeset getWeaknesses(typepair& type) {
		auto [first, second] = type;
		auto firstweaknesses = weaknesses.at(first);
		auto secondweaknesses = weaknesses.at(second);
		auto totalweaknesses{ firstweaknesses };
		totalweaknesses.insert(secondweaknesses.begin(), secondweaknesses.end());
		return totalweaknesses;
	}
	const ptypeset getImmunities(typepair& type) {
		auto [first, second] = type;
		auto firstImmunities = immunities.at(first);
		auto secondImmunities = immunities.at(second);
		auto totalweaknesses{ firstImmunities };
		totalweaknesses.insert(secondImmunities.begin(), secondImmunities.end());
		return totalweaknesses;
	}
	const ptypeset getResistances(typepair& type) {
		auto [first, second] = type;
		auto firstresistances = resistances.at(first);
		auto secondresistances = resistances.at(second);
		auto totalweaknesses{ firstresistances };
		totalweaknesses.insert(secondresistances.begin(), secondresistances.end());
		return totalweaknesses;
	}
	const int WeaknessCount(typepair& type) {
		int count{};
		auto weaknesses{ getWeaknesses(type) };
		auto resistances{ getResistances(type) };
		auto immunities{ getImmunities(type) };
		for (auto& weakness : weaknesses) {
			if (resistances.find(weakness) != resistances.end() || immunities.find(weakness) != immunities.end()) continue;
			else ++count;
		}
		return count;
	}
	inline bool isWeakAgainst(typepair& defendingtype, pktype& atktype) {
		if (CalculateDMG(atktype, defendingtype) > 1) return true;
		else return false;
	}
	inline bool isResistant(typepair& defendingtype, pktype& atktype) {
		return CalculateDMG(atktype, defendingtype) < 1 ? true : false;
	}
	inline bool isImmune(typepair& defendingtype, pktype& atktype) {
		return CalculateDMG(atktype, defendingtype) == 0 ? true : false;
	}
}


#endif