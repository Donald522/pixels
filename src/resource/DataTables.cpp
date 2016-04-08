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
}

const char* EnumToString(size_t index)
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

int FindStringInEnum(const char *search)
{
    int index = -1;
    const char *current = NULL;
    for(int i = 0; i < Creature::TypeCount; ++i)
    {
        current = EnumToString(i);
        if(strcmp(search, current) == 0)
        {
            index = i;
            beak;
        }
    }
    return index;
}

using namespace std::placeholders;

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

    // load values from xml
    pugi::xml_document doc;
    bool noInfo = false;
    bool errFlag = false;
    pugi::xml_node currentShip;
    pugi::xml_parse_result result = doc.load_file(aircraftDataFile);

    if(pugi::xml_node mesh = doc.child("AircraftData")) {
        for(int i = 0; i < Creature::TypeCount; ++i) {
            switch (i) {
                case Creature::PlayerStarship:
                    if(currentShip = mesh.child("PlayerStarship"));
                    else {
                        noInfo = true;
                    }
                    break;
                case Creature::AlienEasy:
                    if(currentShip = mesh.child("AlienEasy"));
                    else {
                        noInfo = true;
                    }
                    break;
                case Creature::AlienMedium:
                    if(currentShip = mesh.child("AlienMedium"));
                    else {
                        noInfo = true;
                    }
                    break;
                case Creature::AlienTestBoss:
                    if(currentShip = mesh.child("AlienTestBoss"));
                    else {
                        noInfo = true;
                    }
                    break;
                default:
                    break;
            }
            if(!noInfo) {
                if(pugi::xml_node hits = currentShip.child("hitpoints")) {
                    if(!hits.attribute("value").empty()) {
                        data[i].hitpoints = hits.attribute("value").as_int();
                    }
                }
                if(pugi::xml_node speed = currentShip.child("speed")) {
                    if(!speed.attribute("value").empty()) {
                        data[i].speed = speed.attribute("value").as_float();
                    }
                }
                if(pugi::xml_node fireInt = currentShip.child("fireInterval")) {
                    if(!fireInt.attribute("value").empty()) {
                        data[i].fireInterval = sf::seconds(fireInt.attribute("value").as_float());
                    }
                }
                if(pugi::xml_node texture = currentShip.child("texture")) {
                    if(!texture.attribute("value").empty()) {
                        data[i].texture = Textures::ID_t(texture.attribute("value").as_int());
                    }
                }
                if(pugi::xml_node texture = currentShip.child("textureRect")) {
                    std::vector<int> textureCoord;
                    textureCoord.reserve(4);
                    for(pugi::xml_node stream = texture.child("stream"); stream; stream = stream.next_sibling()) {
                        if(!stream.attribute("value").empty()) {
                            textureCoord.push_back(stream.attribute("value").as_int());
                        }
                        else {
                            errFlag = true;
                            break;
                        }
                    }
                    if(!errFlag) {
                        data[i].textureRect = sf::IntRect(textureCoord[0], textureCoord[1],
                                textureCoord[2], textureCoord[3]);
                    }
                    else {
                        errFlag = false;
                    }
                }
                if(pugi::xml_node motion = currentShip.child("Motion")) {
                    std::vector<std::pair<float, float>> moveParams;
                    moveParams.reserve(10);
                    for(pugi::xml_node dir = motion.child("Direction"); dir; dir = dir.next_sibling()) {
                        if(pugi::xml_node stream = dir.child("stream")) {
                            if(!stream.attribute("value").empty()) {
                                float angle = stream.attribute("value").as_float();
                                stream = stream.next_sibling();
                                if(!stream) {
                                    errFlag = true;
                                    break;
                                }
                                if(!stream.attribute("value").empty()) {
                                    float dist = stream.attribute("value").as_float();
                                    moveParams.push_back(std::make_pair(angle, dist));
                                }
                                else {
                                    errFlag = true;
                                    break;
                                }
                            }
                            else {
                                errFlag = true;
                                break;
                            }
                        }
                    }
                    if(!errFlag) {
                        for(auto &it : moveParams) {
                            data[i].directions.push_back(Direction(it.first, it.second));
                        }
                    }
                    else {
                        errFlag = false;
                    }
                }
            }
            else {
                noInfo = false;
            }
        }
    }
	return data;
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

	return data;
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

	return data;
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

	return data;
}
