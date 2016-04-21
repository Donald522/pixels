#ifndef DATATABLES_H
#define DATATABLES_H

#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "pugixml.hpp"

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

	float	angle;
	float	distance;
};

struct AircraftData
{
	int			hitpoints;
	float			speed;
	Textures::ID_t		texture;
	sf::IntRect		textureRect;
	sf::Time		fireInterval;
	std::vector<Direction>	directions;
};

struct ProjectileData
{
	int			damage;
	float			speed;
	Textures::ID_t		texture;
	sf::IntRect		textureRect;
};

struct PickupData
{
	std::function<void(Creature&)>	action;
	Textures::ID_t			texture;
	sf::IntRect			textureRect;
};

struct ParticleData {
	sf::Color	color;
	sf::Time	lifetime;
};

struct AircraftFileWalker_t: pugi::xml_tree_walker
{
    AircraftFileWalker_t(std::vector<AircraftData> &data, std::size_t type)
    : m_data(data)
    , m_shipType(type)
    {
    }
    virtual bool for_each(pugi::xml_node& node);
private:
    std::vector<AircraftData>&	      m_data;
    const std::size_t		      m_shipType;

};

struct ProjectileFileWalker_t: pugi::xml_tree_walker
{
    ProjectileFileWalker_t(std::vector<ProjectileData> &data, std::size_t type)
    : m_data(data)
    , m_bulletType(type)
    {
    }
    virtual bool for_each(pugi::xml_node& node);
private:
    std::vector<ProjectileData>& 	m_data;
    const std::size_t			m_bulletType;

};

struct PickupFileWalker_t: pugi::xml_tree_walker
{
    PickupFileWalker_t(std::vector<PickupData> &data, std::size_t type)
    : m_data(data)
    , m_pickupType(type)
    {
    }
    virtual bool for_each(pugi::xml_node& node);
private:
    std::vector<PickupData>&		m_data;
    const std::size_t			m_pickupType;

};

const char* CreatureEnumToString(size_t index);
std::size_t CreatureFindStringInEnum(const char *search);

const char* ProjectileEnumToString(size_t index);
std::size_t ProjectileFindStringInEnum(const char *search);

const char* PickupEnumToString(size_t index);
std::size_t PickupFindStringInEnum(const char *search);

const char* ParticleEnumToString(size_t index);
std::size_t ParticleFindStringInEnum(const char *search);

std::vector<AircraftData>	InitializeAircraftData();
std::vector<ProjectileData>	InitializeProjectileData();
std::vector<PickupData>		InitializePickupData();
std::vector<ParticleData>	InitializeParticleData();

#endif // DATATABLES_H
