#include "resource/DataTables.h"
#include "entity/Creature.h"
#include "entity/Projectile.h"
#include "entity/Pickup.h"
#include "effects/Particle.h"
#include "log/Log.h"

using namespace std::placeholders;

std::vector<AircraftData> InitializeAircraftData()
{
	std::vector<AircraftData> data(Creature::TypeCount);

	data[Creature::PlayerStarship].hitpoints = 1000;
	data[Creature::PlayerStarship].speed = 500.f;
	data[Creature::PlayerStarship].fireInterval = sf::seconds(0.8f);
	data[Creature::PlayerStarship].texture = Textures::Entities;
	data[Creature::PlayerStarship].textureRect = sf::IntRect( 126, 0, 120, 120 );

	data[Creature::AlienEasy].hitpoints = 60;
	data[Creature::AlienEasy].speed = 150.f;
	data[Creature::AlienEasy].texture = Textures::Entities;
	data[Creature::AlienEasy].textureRect = sf::IntRect( 247, 0, 114, 200 );
	data[Creature::AlienEasy].directions.push_back(Direction(+45.f, 80.f));
	data[Creature::AlienEasy].directions.push_back(Direction(-45.f, 160.f));
	data[Creature::AlienEasy].directions.push_back(Direction(+45.f, 80.f));
	data[Creature::AlienEasy].fireInterval = sf::seconds(100);

	data[Creature::AlienMedium].hitpoints = 50;
	data[Creature::AlienMedium].speed = 130.f;
	data[Creature::AlienMedium].texture = Textures::Entities;
	data[Creature::AlienMedium].textureRect = sf::IntRect( 0, 0, 125, 238 );
	data[Creature::AlienMedium].directions.push_back(Direction(+45.f,  50.f));
	data[Creature::AlienMedium].directions.push_back(Direction(  0.f,  50.f));
	data[Creature::AlienMedium].directions.push_back(Direction(-45.f, 100.f));
	data[Creature::AlienMedium].directions.push_back(Direction(  0.f,  50.f));
	data[Creature::AlienMedium].directions.push_back(Direction(+45.f,  50.f));
	data[Creature::AlienMedium].fireInterval = sf::seconds(100);

	data[Creature::AlienTestBoss].hitpoints = 300;
	data[Creature::AlienTestBoss].speed = 250.f;
	data[Creature::AlienTestBoss].texture = Textures::Entities;
	data[Creature::AlienTestBoss].textureRect = sf::IntRect( 0, 0, 125, 238 );
	data[Creature::AlienTestBoss].directions.push_back( Direction( +90.f, 400.f ) );
	data[Creature::AlienTestBoss].directions.push_back( Direction( -90.f, 800.f ) );
	data[Creature::AlienTestBoss].directions.push_back( Direction( +90.f, 400.f ) );
	data[Creature::AlienTestBoss].fireInterval = sf::seconds( 3 );

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
