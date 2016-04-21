#ifndef PICKUP_H
#define PICKUP_H

#include "entity/Entity.h"
#include "system/Command.h"
#include "resource/ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>


class Creature;
class SceneGrid;

class Pickup : public Entity
{
public:

	enum Type_t
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		TypeCount
        };
	Pickup(SceneGrid* sceneGrid, Type_t type, const TextureHolder& textures);

	virtual Category::Type_t    GetCategory() const;
        virtual sf::FloatRect       GetBoundingRect() const;

        void                        Apply(Creature& player) const;

protected:

	virtual void                DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	Type_t                      m_type;
        sf::Sprite                  m_sprite;
};

#endif // PICKUP_H
