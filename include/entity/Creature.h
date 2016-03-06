#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "entity/Entity.h"
#include "system/Command.h"
#include "resource/ResourceIdentifiers.h"
#include "entity/Projectile.h"
#include "nodes/TextNode.h"
#include "animation/Animation.h"

#include <SFML/Graphics/Sprite.hpp>


class SceneGrid;

class Creature : public Entity {
public:

	enum Type_t {
		PlayerStarship,
		AlienEasy,
		AlienMedium,
		AlienTestBoss,
		TypeCount
	};

public:

                                Creature( SceneGrid* sceneGrid, Type_t type, const TextureHolder& textures, const FontHolder& fonts );

	virtual Category::Type_t	GetCategory( ) const;
	virtual sf::FloatRect		GetBoundingRect( ) const;
	virtual bool 				IsMarkedForRemoval( ) const;
	bool						IsAllied( ) const;
	Creature::Type_t			GetType() const;
	float						GetSpeed( ) const;

	void						IncreaseFireRate( );
	void						IncreaseSpread( );
	void						CollectMissiles( unsigned int count );

	void 						Fire( );
	void						LaunchMissile( );

	virtual void				Remove( );


private:

	virtual void				DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void 				UpdateCurrent( sf::Time dt, CommandQueue& commands );
	void						UpdateMovementPattern( sf::Time dt );
	void						CheckPickupDrop( CommandQueue& commands );
	void						CheckProjectileLaunch( sf::Time dt, CommandQueue& commands );

	void						CreateBullets( SceneNode& node, const TextureHolder& textures ) const;
    void						CreateProjectile( SceneNode& node, Projectile::Type_t type, float xOffset, float yOffset, const TextureHolder& textures) const;
	void						CreatePickup( SceneNode& node, const TextureHolder& textures ) const;

	void						UpdateTexts( );


private:

	Type_t						m_type;
	sf::Sprite					m_sprite;
	Animation					m_explosion;
	bool						m_spawnedPickup;
	Command_t 					m_fireCommand;
	Command_t					m_missileCommand;
	sf::Time					m_fireCountdown;
	bool 						m_isFiring;
	bool						m_isLaunchingMissile;

	bool						m_showExplosion;

	int							m_fireRateLevel;
	int							m_spreadLevel;
	int							m_missileAmmo;

	Command_t 					m_dropPickupCommand;
	float						m_travelledDistance;
	std::size_t					m_directionIndex;
	TextNode*					m_healthDisplay;
	TextNode*					m_missileDisplay;
};

#endif // AIRCRAFT_H
