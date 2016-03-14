#include "world/World.h"
#include "entity/Projectile.h"
#include "entity/Pickup.h"
#include "nodes/TextNode.h"
#include "nodes/ParticleNode.h"
#include "util/Utility.h"
#include "log/Log.h"


#include <SFML/Graphics/RenderWindow.hpp>


#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

namespace {
	const float worldLength			= 15000.0f;
	const float worldScrollSpeed	= -100.0f;
}


World::World( sf::RenderTarget& outTarget, FontHolder& fonts, SoundPlayer& sounds )
: m_target( outTarget )
, m_sceneTexture()
, m_worldView( outTarget.getDefaultView() )
, m_fonts( fonts )
, m_textures()
, m_sounds(sounds)
, m_sceneGrid()
, m_sceneGraph()
, m_sceneLayers()
, m_worldBounds( 0.f, 0.f, m_worldView.getSize().x, worldLength )
, m_spawnPosition( m_worldView.getSize().x / 2.f, m_worldBounds.height - m_worldView.getSize().y / 2.f )
, m_scrollSpeed( worldScrollSpeed )
, m_playerAircraft( nullptr )
, m_enemySpawnPoints()
, m_activeEnemies()
{
	m_sceneTexture.create( m_target.getSize().x, m_target.getSize().y );

	LoadTextures();
	BuildScene();


	m_worldView.setCenter(m_spawnPosition);
}

void World::Update(sf::Time dt)
{
	// Scroll the world
	m_worldView.move(0.f, m_scrollSpeed * dt.asSeconds());	
	m_playerAircraft->SetVelocity( 0.f, 0.f );

	DestroyEntitiesOutsideView();
	GuideMissiles();

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!m_commandQueue.IsEmpty())
		m_sceneGraph.OnCommand(m_commandQueue.Pop(), dt);
	AdaptPlayerVelocity();

	HandleCollisions();

	m_sceneGraph.RemoveWrecks();
	SpawnEnemies();

	m_sceneGraph.Update(dt, m_commandQueue);
	AdaptPlayerPosition();

	UpdateSounds();
}

void World::Draw()
{
	bool useBloom = false;
	if ( useBloom )
	{
		m_sceneTexture.clear();
		m_sceneTexture.setView( m_worldView );
		m_sceneTexture.draw( m_sceneGraph );
		m_sceneTexture.display();
		m_bloomEffect.Apply( m_sceneTexture, m_target );
	}
	else
	{
		m_target.setView( m_worldView );
		m_target.draw( m_sceneGraph );
	}
}

CommandQueue& World::GetCommandQueue()
{
	return m_commandQueue;
}

bool World::HasAlivePlayer() const
{
	return !m_playerAircraft->IsMarkedForRemoval();
} 

bool World::HasPlayerReachedEnd() const
{																																						
	return !m_worldBounds.contains( m_playerAircraft->getPosition() );
}

size_t  World::GetEntititisCount( ) const
{
	return m_sceneGraph.GetChildCount( );
}

void World::ScrollStop()
{
	m_scrollSpeed = 0.0f;
}

void World::ScrollResume( )
{
	m_scrollSpeed = worldScrollSpeed;
}

void World::SetScrollSpeed(float speed)
{
	m_scrollSpeed = speed;
}

float World::GetScrollSpeed( ) const
{
	return m_scrollSpeed;
}

void World::LoadTextures()
{
	m_textures.Load(Textures::Entities,			"Data/Textures/Entities.png");
	m_textures.Load(Textures::Space,			"Data/Textures/tileable-classic-nebula-space-patterns-3.jpg");
	m_textures.Load(Textures::Particle,			"Data/Textures/Particle.png" );
	m_textures.Load(Textures::Explosion,		"Data/Textures/Explosion.png" );
}

void World::AdaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds = GetViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = m_playerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	m_playerAircraft->setPosition(position);
}

void World::AdaptPlayerVelocity()
{
	sf::Vector2f velocity = m_playerAircraft->GetVelocity();

	// Moving diagonally -> reduce velocity
	if ( velocity.x != 0.f && velocity.y != 0.f )
	{
		m_playerAircraft->SetVelocity( velocity / std::sqrt( 2.f ) );
	}

	// Add scrolling velocity
	m_playerAircraft->Accelerate(0.f, m_scrollSpeed);
}

bool MatchesCategories(SceneNode::Pair_t& colliders, Category::Type_t type1, Category::Type_t type2)
{
	unsigned int category1 = colliders.first->GetCategory();
	unsigned int category2 = colliders.second->GetCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::HandleCollisions()
{
	std::set<SceneNode::Pair_t> collisionPairs;
	//m_sceneGraph.CheckSceneCollision(m_sceneGraph, collisionPairs);
	
	m_sceneGrid.SetView( GetViewBounds( ) );
	m_sceneGrid.CalcCollision( collisionPairs );

	for (SceneNode::Pair_t pair : collisionPairs)
	{
		if (MatchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
		{
			auto& player = static_cast<Creature&>(*pair.first);
			auto& enemy = static_cast<Creature&>(*pair.second);

			// Collision: Player damage = enemy's remaining HP
			player.Damage(enemy.GetHitpoints());
			enemy.Destroy();
		}

		else if (MatchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		{
			auto& player = static_cast<Creature&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			// Apply pickup effect to player, destroy projectile
			pickup.Apply(player);
			pickup.Destroy();
		}

		else if (MatchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			  || MatchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
			auto& creature = static_cast<Creature&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			// Apply projectile damage to Creature, destroy projectile
			creature.Damage( projectile.GetDamage( ) );
			projectile.Destroy();
		}
	}
	m_sceneGrid.Clear( );
}

void World::UpdateSounds()
{
	m_sounds.SetListenerPosition(m_playerAircraft->GetWorldPosition());
	m_sounds.RemoveStoppedSounds();
}

void World::BuildScene()
{
	LogInfo( "Building scene:" );
	// Initialize the different layers
	LogInfo( "Initialize layers" );
	for ( std::size_t i = 0; i < LayerCount; ++i )
	{
		Category::Type_t category = ( i == LowerAir ) ? Category::SceneAirLayer : Category::None;
		SceneNode::Ptr_t layer( new SceneNode( category ) );
		m_sceneLayers[i] = layer.get( );

		m_sceneGraph.AttachChild( std::move( layer ) );
	}


	//  tiled background
	LogInfo("Tiled background texture");
	sf::Texture& texture = m_textures.Get(Textures::Space);
	sf::IntRect textureRect(m_worldBounds);
	texture.setRepeated(true);

	//  background sprite
	LogInfo( "Background sprite" );
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(m_worldBounds.left, m_worldBounds.top);
	m_sceneLayers[Background]->AttachChild(std::move(backgroundSprite));

	// player's creature
	LogInfo( "Player's creature" );
	std::unique_ptr<Creature> player(new Creature(&m_sceneGrid, Creature::PlayerStarship, m_textures, m_fonts));
	m_playerAircraft = player.get();
	m_playerAircraft->setPosition(m_spawnPosition);
	m_sceneLayers[UpperAir]->AttachChild( std::move( player ) );


	LogInfo( "Engine power" );
	std::unique_ptr<ParticleNode> propellantPlayerNode( new ParticleNode( Particle::EnginePower, m_textures ) );
	m_sceneLayers[UpperAir]->AttachChild( std::move( propellantPlayerNode ) );

	// particle node
	LogInfo( "Particle node" );
	std::unique_ptr<ParticleNode> smokeNode( new ParticleNode( Particle::Smoke, m_textures ) );
	m_sceneLayers[LowerAir]->AttachChild( std::move( smokeNode ) );

	// propellant particle
	LogInfo( "Propellant particle" );
	std::unique_ptr<ParticleNode> propellantNode( new ParticleNode( Particle::Propellant, m_textures ) );
	m_sceneLayers[LowerAir]->AttachChild( std::move( propellantNode ) );

	AddEnemies();

	LogInfo( "Finished building scene" );
}

void World::AddEnemies()
{
	// Add enemies to the spawn point container

	LogInfo( "Adding enemies");
	float startPos = 700.0f;

	AddEnemy( Creature::AlienTestBoss, 0.0f, 750.0f );
	
	for ( float x = startPos; startPos < worldLength; startPos += 150.0f )
	{
		size_t enemyCount = RandomInt( 5 );
		for ( size_t i = 0; i < enemyCount; ++i )
		{
			Creature::Type_t enemyType = Creature::Type_t( RandomInt( 2 ) + 1 );
			float posX = static_cast<float>(RandomInt( 800 ) - 400);
			AddEnemy( enemyType, posX, startPos );

		}
	}
	LogInfo( "Finished adding enemies" );

	// Sort all enemies according to their y value, such that lower enemies are checked first for spawning
	std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(), [] (SpawnPoint_t lhs, SpawnPoint_t rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::AddEnemy( Creature::Type_t type, float relX, float relY )
{
	LogInfo( "Add enemy: type = " + std::to_string( type ) + ", X = " + std::to_string( relX ) + ", Y = " + std::to_string( relY ) );
	SpawnPoint_t spawn(type, m_spawnPosition.x + relX, m_spawnPosition.y - relY);
	m_enemySpawnPoints.push_back(spawn);
}

void World::SpawnEnemies()
{
	// Spawn all enemies entering the view area (including distance) this frame

	if ( GetViewBounds( ).top > m_spawnPosition.x - 700.0f && GetViewBounds( ).top <= m_spawnPosition.x - 850.0f )
		ScrollStop();

	while (!m_enemySpawnPoints.empty()
		&& m_enemySpawnPoints.back().y > GetBattlefieldBounds().top)
	{
		SpawnPoint_t spawn = m_enemySpawnPoints.back();
		if (spawn.type == Creature::AlienTestBoss)
		{
			std::cout << "BOSS\n";
			SetScrollSpeed(-20);
		}
		
		std::unique_ptr<Creature> enemy( new Creature( &m_sceneGrid, spawn.type, m_textures, m_fonts ) );
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);
		m_sceneLayers[UpperAir]->AttachChild( std::move( enemy ) );

		// Enemy is spawned, remove from the list to spawn
		m_enemySpawnPoints.pop_back();
	}
}

void World::DestroyEntitiesOutsideView()
{
	Command_t command;
	command.category = Category::Projectile | Category::EnemyAircraft | Category::Pickup;
	command.action = DerivedAction<Entity>([this] (Entity& e, sf::Time)
	{
		if (!GetBattlefieldBounds().intersects(e.GetBoundingRect()))
			e.Destroy();
	});

	m_commandQueue.Push(command);
}

void World::GuideMissiles()
{
	// Setup command that stores all enemies in m_activeEnemies
	Command_t enemyCollector;
	enemyCollector.category = Category::EnemyAircraft;
	enemyCollector.action = DerivedAction<Creature>([this] (Creature& enemy, sf::Time)
	{
		if ( !enemy.IsDestroyed( ) )
			m_activeEnemies.push_back(&enemy);
	});

	// Setup command that guides all missiles to the enemy which is currently closest to the player
	Command_t missileGuider;
	missileGuider.category = Category::AlliedProjectile;
	missileGuider.action = DerivedAction<Projectile>([this] (Projectile& missile, sf::Time)
	{
		// Ignore unguided bullets
        if (!missile.IsGuided())
			return;

		float minDistance = std::numeric_limits<float>::max();
		Creature* closestEnemy = nullptr;

		// Find closest enemy
		for ( Creature* enemy : m_activeEnemies )
		{
            float enemyDistance = NodeDistance(missile, *enemy);

			if (enemyDistance < minDistance)
			{
				closestEnemy = enemy;
				minDistance = enemyDistance;
			}
		}

		if (closestEnemy)
            missile.GuideTowards(closestEnemy->GetWorldPosition());
	});

	// Push commands, reset active enemies
	m_commandQueue.Push(enemyCollector);
	m_commandQueue.Push(missileGuider);

	// 0 active enemies = resume scrolling
	if ( m_activeEnemies.size() == 0 )
		ScrollResume();

	m_activeEnemies.clear();
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize());
}

sf::FloatRect World::GetBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = GetViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;


	return bounds;
}

