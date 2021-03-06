#include "resource/DataTables.h"
#include "entity/Creature.h"
#include "entity/Pickup.h"
#include "effects/Particle.h"
#include "log/Log.h"
#include "pugixml.hpp"

using namespace std::placeholders;

namespace
{
    const char *aircraftDataFile = "Data/Tables/AircraftData.xml";
    const char *projectileDataFile = "Data/Tables/ProjectileData.xml";
	const char *pickupDataFile = "Data/Tables/PickupData.xml";
	const char *particleDataFile = "Data/Tables/ParticleData.xml";
}

//================================================================================//

const char* CreatureEnumToString(size_t index)
{
    const char *result = "";
    switch (index)
    {
        case Creature::PlayerStarship:
            result = "PlayerStarship";
            break;
        case Creature::AlienEasy:
            result = "AlienEasy";
            break;
        case Creature::AlienMedium:
            result = "AlienMedium";
            break;
        case Creature::AlienTestBoss:
            result = "AlienTestBoss";
            break;
        default:
            break;
    }
    return result;
}

std::size_t CreatureFindStringInEnum(const char *search)
{
    std::size_t index = Creature::TypeCount;
    const char *current = NULL;
    for(int i = 0; i < Creature::TypeCount; ++i)
    {
        current = CreatureEnumToString(i);
		if(!strcmp(search, current))
        {
            index = i;
            break;
        }
    }
    return index;
}

bool AircraftFileWalker_t::for_each(pugi::xml_node& node)
{
	if(!strcmp("data", node.name()))
    {
        for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
        {
			if(!strcmp("hitpoints", attr.name()))
            {
                m_data[m_shipType].hitpoints = attr.as_int();
            }
            else if(!strcmp("speed", attr.name()))
            {
                m_data[m_shipType].speed = attr.as_float();
            }
            else if(!strcmp("fireInterval", attr.name()))
            {
                m_data[m_shipType].fireInterval = sf::seconds(attr.as_float());
            }
            else if(!strcmp("texture", attr.name()))
            {
                m_data[m_shipType].texture = Textures::ID_t(attr.as_int());
            }
        }
    }
	else if(!strcmp("textureRect", node.name()))
    {
        if(!node.attribute("top").empty())
        {
            if(!node.attribute("left").empty())
            {
                if(!node.attribute("width").empty())
                {
                    if(!node.attribute("height").empty())
                    {
                        int top = node.attribute("top").as_int();
                        int left = node.attribute("left").as_int();
                        int width = node.attribute("width").as_int();
                        int height = node.attribute("height").as_int();
                        m_data[m_shipType].textureRect = sf::IntRect(top, left, width, height);
                    }
                }
            }
        }
    }
	else if(!strcmp("directions", node.name()))
    {
        if(std::distance(node.children().begin(), node.children().end()) > 0)
        {
            m_data[m_shipType].directions.clear();
            for(pugi::xml_node dir: node.children("direction"))
            {
                if(!dir.attribute("angle").empty())
                {
                    if(!dir.attribute("dist").empty())
                    {
                        m_data[m_shipType].directions.push_back(Direction(dir.attribute("angle").as_float(), dir.attribute("dist").as_float()));
                    }
                }
            }
        }
    }
    return true; // continue traversal
}


//TODO: FIX texture loading

std::vector<AircraftData> InitializeAircraftData()
{
    std::vector<AircraftData> data(Creature::TypeCount);

    // values by default
    data[Creature::PlayerStarship].hitpoints = 1000;
    data[Creature::PlayerStarship].speed = 500.f;
    data[Creature::PlayerStarship].fireInterval = sf::seconds(0.8f);
    data[Creature::PlayerStarship].texture = Textures::Entities;
    data[Creature::PlayerStarship].textureRect = sf::IntRect( 126, 0, 120, 120 );

    data[Creature::AlienEasy].hitpoints = 60;
    data[Creature::AlienEasy].speed = 150.f;
    data[Creature::AlienEasy].fireInterval = sf::seconds(100);
    data[Creature::AlienEasy].texture = Textures::Entities;
    data[Creature::AlienEasy].textureRect = sf::IntRect( 247, 0, 114, 200 );
    data[Creature::AlienEasy].directions.push_back(Direction(+45.f, 80.f));
    data[Creature::AlienEasy].directions.push_back(Direction(-45.f, 160.f));
    data[Creature::AlienEasy].directions.push_back(Direction(+45.f, 80.f));

    data[Creature::AlienMedium].hitpoints = 50;
    data[Creature::AlienMedium].speed = 130.f;
    data[Creature::AlienMedium].fireInterval = sf::seconds(100);
    data[Creature::AlienMedium].texture = Textures::Entities;
    data[Creature::AlienMedium].textureRect = sf::IntRect( 0, 0, 125, 238 );
    data[Creature::AlienMedium].directions.push_back(Direction(+45.f,  50.f));
    data[Creature::AlienMedium].directions.push_back(Direction(  0.f,  50.f));
    data[Creature::AlienMedium].directions.push_back(Direction(-45.f, 100.f));
    data[Creature::AlienMedium].directions.push_back(Direction(  0.f,  50.f));
    data[Creature::AlienMedium].directions.push_back(Direction(+45.f,  50.f));

    data[Creature::AlienTestBoss].hitpoints = 300;
    data[Creature::AlienTestBoss].speed = 250.f;
    data[Creature::AlienTestBoss].fireInterval = sf::seconds(3);
    data[Creature::AlienTestBoss].texture = Textures::Entities;
    data[Creature::AlienTestBoss].textureRect = sf::IntRect( 0, 0, 125, 238 );
    data[Creature::AlienTestBoss].directions.push_back( Direction( +90.f, 400.f ) );
    data[Creature::AlienTestBoss].directions.push_back( Direction( -90.f, 800.f ) );
    data[Creature::AlienTestBoss].directions.push_back( Direction( +90.f, 400.f ) );

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(aircraftDataFile);
    if(result) {
        pugi::xml_node ships = doc.child("AircraftData");
        if(ships)
        {
            for(pugi::xml_node ship: ships.children("Ship"))
            {
                if(!ship.attribute("type").empty())
                {
                    std::size_t shipType = CreatureFindStringInEnum(ship.attribute("type").as_string());
                    if(shipType < Creature::TypeCount)
                    {
                        AircraftFileWalker_t shipNodeWalker(data, shipType);
                        ship.traverse(shipNodeWalker);
                    }
                }
            }
        }
    }
    return data;
}

//================================================================================//

const char* ProjectileEnumToString(size_t index)
{
    const char *result = "";
    switch (index)
    {
        case Projectile::AlliedBullet:
            result = "AlliedBullet";
            break;
        case Projectile::EnemyBullet:
            result = "EnemyBullet";
            break;
        case Projectile::Missile:
            result = "Missile";
            break;
        default:
            break;
    }
    return result;
}

std::size_t ProjectileFindStringInEnum(const char *search)
{
    std::size_t index = Projectile::TypeCount;
    const char *current = NULL;
    for(int i = 0; i < Projectile::TypeCount; ++i)
    {
        current = ProjectileEnumToString(i);
		if(!strcmp(search, current))
        {
            index = i;
            break;
        }
    }
    return index;
}

bool ProjectileFileWalker_t::for_each(pugi::xml_node& node)
{
	if(!strcmp("data", node.name()))
	{
		for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
		{
			if(!strcmp("damage", attr.name()))
			{
				m_data[m_bulletType].damage = attr.as_int();
			}
			else if(!strcmp("speed", attr.name()))
			{
				m_data[m_bulletType].speed = attr.as_float();
			}
			else if(!strcmp("texture", attr.name()))
			{
				m_data[m_bulletType].texture = Textures::ID_t(attr.as_int());
			}
		}
	}
	else if(!strcmp("textureRect", node.name()))
	{
		if(!node.attribute("top").empty())
		{
			if(!node.attribute("left").empty())
			{
				if(!node.attribute("width").empty())
				{
					if(!node.attribute("height").empty())
					{
						int top = node.attribute("top").as_int();
						int left = node.attribute("left").as_int();
						int width = node.attribute("width").as_int();
						int height = node.attribute("height").as_int();
						m_data[m_bulletType].textureRect = sf::IntRect(top, left, width, height);
					}
				}
			}
		}
	}
	return true;
}

std::vector<ProjectileData> InitializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::AlliedBullet].damage = 20;
    data[Projectile::AlliedBullet].speed = 600.f;
    data[Projectile::AlliedBullet].texture = Textures::Entities;
    data[Projectile::AlliedBullet].textureRect = sf::IntRect( 208, 121, 3, 14);

    data[Projectile::EnemyBullet].damage = 10;
    data[Projectile::EnemyBullet].speed = 300.f;
    data[Projectile::EnemyBullet].texture = Textures::Entities;
    data[Projectile::EnemyBullet].textureRect = sf::IntRect( 208, 121, 3, 14 );

    data[Projectile::Missile].damage = 200;
    data[Projectile::Missile].speed = 200.f;
    data[Projectile::Missile].texture = Textures::Entities;
    data[Projectile::Missile].textureRect = sf::IntRect( 126, 203, 15, 32 );

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(projectileDataFile);
	if(result)
	{
		pugi::xml_node bullets = doc.child("ProjectileData");
		if(bullets)
		{
			for(pugi::xml_node bullet: bullets.children("Bullet"))
			{
				if(!bullet.attribute("type").empty())
				{
					std::size_t bulletType = ProjectileFindStringInEnum(bullet.attribute("type").as_string());
					if(bulletType < Projectile::TypeCount)
					{
						ProjectileFileWalker_t bulletNodeWalker(data, bulletType);
						bullet.traverse(bulletNodeWalker);
					}
				}
			}
		}
	}

    return data;
}

//================================================================================//

const char* PickupEnumToString(size_t index)
{
	const char *result = "";
	switch (index)
	{
		case Pickup::HealthRefill:
			result = "HealthRefill";
			break;
		case Pickup::MissileRefill:
			result = "MissileRefill";
			break;
		case Pickup::FireSpread:
			result = "FireSpread";
			break;
		case Pickup::FireRate:
			result = "FireRate";
			break;
		default:
			break;
	}
	return result;
}

std::size_t PickupFindStringInEnum(const char *search)
{
	std::size_t index = Pickup::TypeCount;
	const char *current = NULL;
	for(int i = 0; i < Pickup::TypeCount; ++i)
	{
		current = PickupEnumToString(i);
		if(!strcmp(search, current))
		{
			index = i;
			break;
		}
	}
	return index;
}

bool PickupFileWalker_t::for_each(pugi::xml_node& node)
{
	if(!strcmp("data", node.name()))
	{
		for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
		{
			if(!strcmp("texture", attr.name()))
			{
				m_data[m_pickupType].texture = Textures::ID_t(attr.as_int());
			}
			if(!strcmp("action", attr.name()))
			{
				if(m_pickupType == Pickup::HealthRefill)
				{
					int health = attr.as_int();
					m_data[m_pickupType].action = [=] (Creature& a) { a.Repair(health); };
				}
				else if(m_pickupType == Pickup::MissileRefill)
				{
					int missiles = attr.as_int();
					m_data[m_pickupType].action = std::bind(&Creature::CollectMissiles, _1, missiles);
				}
			}
		}
	}
	else if(!strcmp("textureRect", node.name()))
	{
		if(!node.attribute("top").empty())
		{
			if(!node.attribute("left").empty())
			{
				if(!node.attribute("width").empty())
				{
					if(!node.attribute("height").empty())
					{
						int top = node.attribute("top").as_int();
						int left = node.attribute("left").as_int();
						int width = node.attribute("width").as_int();
						int height = node.attribute("height").as_int();
						m_data[m_pickupType].textureRect = sf::IntRect(top, left, width, height);
					}
				}
			}
		}
	}
	return true;
}

std::vector<PickupData> InitializePickupData()
{
    std::vector<PickupData> data(Pickup::TypeCount);

    data[Pickup::HealthRefill].texture = Textures::Entities;
    data[Pickup::HealthRefill].textureRect = sf::IntRect( 167, 121, 40, 40);
    data[Pickup::HealthRefill].action = [] (Creature& a) { a.Repair(50); };

    data[Pickup::MissileRefill].texture = Textures::Entities;
    data[Pickup::MissileRefill].textureRect = sf::IntRect( 167, 162, 40, 40 );
    data[Pickup::MissileRefill].action = std::bind(&Creature::CollectMissiles, _1, 5);

    data[Pickup::FireSpread].texture = Textures::Entities;
    data[Pickup::FireSpread].textureRect = sf::IntRect( 126, 162, 40, 40 );
    data[Pickup::FireSpread].action = std::bind(&Creature::IncreaseSpread, _1);

    data[Pickup::FireRate].texture = Textures::Entities;
    data[Pickup::FireRate].textureRect = sf::IntRect( 126, 121, 40, 40 );
    data[Pickup::FireRate].action = std::bind(&Creature::IncreaseFireRate, _1);

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(pickupDataFile);
	if(result)
	{
		pugi::xml_node pickups = doc.child("PickupData");
		if(pickups)
		{
			for(pugi::xml_node pickup: pickups.children("Pickup"))
			{
				if(!pickup.attribute("type").empty())
				{
					std::size_t pickupType = PickupFindStringInEnum(pickup.attribute("type").as_string());
					if(pickupType < Pickup::TypeCount)
					{
						PickupFileWalker_t pickupNodeWalker(data, pickupType);
						pickup.traverse(pickupNodeWalker);
					}
				}
			}
		}
	}
    return data;
}

//================================================================================//

const char* ParticleEnumToString(size_t index)
{
	const char *result = "";
	switch (index)
	{
		case Particle::Propellant:
			result = "Propellant";
			break;
		case Particle::Smoke:
			result = "Smoke";
			break;
		case Particle::EnginePower:
			result = "EnginePower";
			break;
		default:
			break;
	}
	return result;
}

std::size_t ParticleFindStringInEnum(const char *search)
{
	std::size_t index = Particle::ParticleCount;
	const char *current = NULL;
	for(int i = 0; i < Particle::ParticleCount; ++i)
	{
		current = ParticleEnumToString(i);
		if(!strcmp(search, current))
		{
			index = i;
			break;
		}
	}
	return index;
}

bool ParticleFileWalker_t::for_each(pugi::xml_node& node)
{
	if(!strcmp("data", node.name()))
	{
		for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
		{
			if(!strcmp("lifetime", attr.name()))
			{
				m_data[m_particleType].lifetime = sf::seconds(attr.as_float());
			}
		}
	}
	else if(!strcmp("color", node.name()))
	{
		if(!node.attribute("red").empty())
		{
			if(!node.attribute("green").empty())
			{
				if(!node.attribute("blue").empty())
				{
					int red = node.attribute("red").as_int();
					int green = node.attribute("green").as_int();
					int blue = node.attribute("blue").as_int();
					int alpha = 255;
					if(!node.attribute("alpha").empty())
					{
						alpha = node.attribute("alpha").as_int();
					}
					m_data[m_particleType].color = sf::Color(red, green, blue);
				}
			}
		}
	}
	return true;
}

std::vector<ParticleData> InitializeParticleData()
{
    std::vector<ParticleData> data( Particle::ParticleCount );

	data[Particle::Propellant].color = sf::Color( 50, 230, 230 );
    data[Particle::Propellant].lifetime = sf::seconds( 0.5f );

    data[Particle::Smoke].color = sf::Color( 90, 90, 90 );
    data[Particle::Smoke].lifetime = sf::seconds( 1.0f );

    data[Particle::EnginePower].color = sf::Color( 50, 150, 230 );
    data[Particle::EnginePower].lifetime = sf::seconds( 0.2f );

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(particleDataFile);
	if(result)
	{
		pugi::xml_node particles = doc.child("ParticleData");
		if(particles)
		{
			for(pugi::xml_node particle: particles.children("Particle"))
			{
				if(!particle.attribute("type").empty())
				{
					std::size_t particleType = ParticleFindStringInEnum(particle.attribute("type").as_string());
					if(particleType < Particle::ParticleCount)
					{
						ParticleFileWalker_t particleNodeWalker(data, particleType);
						particle.traverse(particleNodeWalker);
					}
				}
			}
		}
	}

    return data;
}

//================================================================================//
