#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity/Entity.h"
#include "resource/ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class SceneGrid;

class Projectile : public Entity
{
	public:

		enum Type_t
		{
			AlliedBullet,
			EnemyBullet,
			Missile,

			TypeCount
		};


public:
                                    Projectile( SceneGrid* sceneGrid, Type_t type, const TextureHolder& textures );

        void                        GuideTowards(sf::Vector2f position);
        bool                        IsGuided() const;
	virtual Category::Type_t    GetCategory( ) const;
        virtual sf::FloatRect       GetBoundingRect() const;
        float                       GetSpeed() const;
        int                         GetDamage() const;

	
private:

        virtual void                UpdateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void                DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

        Type_t                      m_type;
        sf::Sprite                  m_sprite;
        sf::Vector2f                m_targetDirection;
};

#endif // PROJECTILE_H
