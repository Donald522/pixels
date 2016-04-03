#include "entity/Pickup.h"
#include "resource/DataTables.h"
#include "system/CommandQueue.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>


namespace
{
	const std::vector<PickupData> Table = InitializePickupData();
}

Pickup::Pickup(SceneGrid* sceneGrid, Type_t type, const TextureHolder& textures )
: Entity( sceneGrid, 1 )
, m_type(type)
, m_sprite(textures.Get(Table[type].texture), Table[type].textureRect)
{
	_LOG_INFO( "Create pickup: type = " + std::to_string( type ) );
	CenterOrigin(m_sprite);
}

Category::Type_t Pickup::GetCategory( ) const
{
	return Category::Pickup;
}

sf::FloatRect Pickup::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(m_sprite.getGlobalBounds());
}

void Pickup::Apply(Creature& player) const
{
	Table[m_type].action(player);
}

void Pickup::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

