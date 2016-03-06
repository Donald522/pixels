#ifndef DATATABLES_H
#define DATATABLES_H

#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class Creature;

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int								hitpoints;
	float							speed;
	Textures::ID_t					texture;
	sf::IntRect						textureRect;
	sf::Time						fireInterval;
	std::vector<Direction>			directions;
};

struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::ID_t					texture;
	sf::IntRect						textureRect;
};

struct PickupData
{
	std::function<void(Creature&)>	action;
	Textures::ID_t					texture;
	sf::IntRect						textureRect;
};

struct ParticleData {
	sf::Color	color;
	sf::Time	lifetime;
};


std::vector<AircraftData>	InitializeAircraftData();
std::vector<ProjectileData>	InitializeProjectileData();
std::vector<PickupData>		InitializePickupData();
std::vector<ParticleData>	InitializeParticleData();

#endif // DATATABLES_H
