#ifndef SCENEGRID_H
#define SCENEGRID_H

#include "entity/Entity.h"
#include "nodes/SceneNode.h"
#include <vector>

class Entity;


class SceneGrid {
public:
							SceneGrid();

	void					Add( Entity* obj );
	void					Clear();
	std::vector<Entity*>	GetObjects() const;

	void					CalcCollision( std::set<Entity::Pair_t>& collisionPairs );
	void					SetView( sf::FloatRect rect );

	static const size_t		cellCount_t;

private:
	void					CheckCellCollisions( size_t cellX, size_t cellY, std::set<SceneNode::Pair_t>& collisionPairs );
	void					CollectCellObjects( size_t cellX, size_t cellY, std::vector<Entity*>& objects ); 

	sf::FloatRect										m_viewRect;

	std::vector< std::vector< std::vector<Entity*> >>	m_cells;
	std::vector<Entity*>								m_objects;

};

#endif // SCENEGRID_H