#include "entity/Entity.h"
#include "system/SceneGrid.h"
#include <cassert>


Entity::Entity(SceneGrid* sceneGrid, int hitpoints )
: m_sceneGrid( sceneGrid )
, m_velocity()
, m_hitpoints(hitpoints)
{
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::SetVelocity(float vx, float vy)
{
	m_velocity.x = vx;
	m_velocity.y = vy;
}

sf::Vector2f Entity::GetVelocity() const
{
	return m_velocity;
}

void Entity::Accelerate(sf::Vector2f velocity)
{
	m_velocity += velocity;
}

void Entity::Accelerate(float vx, float vy)
{
	m_velocity.x += vx;
	m_velocity.y += vy;
}

int Entity::GetHitpoints() const
{
	return m_hitpoints;
}

void Entity::Repair(int points)
{
	assert(points > 0);

	m_hitpoints += points;
}

void Entity::Damage(int points)
{
	assert(points > 0);

	m_hitpoints -= points;
}


void Entity::Destroy()
{
	m_hitpoints = 0;
}

void Entity::Remove( )
{
	Destroy( );
}


bool Entity::IsDestroyed( ) const
{
	return m_hitpoints <= 0;
}

void Entity::UpdateCurrent(sf::Time dt, CommandQueue&)
{	
	move(m_velocity * dt.asSeconds());
	m_sceneGrid->Add( this );
}
