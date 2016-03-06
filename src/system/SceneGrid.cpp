#include "system/SceneGrid.h"
#include <iostream>

const size_t SceneGrid::cellCount_t = 4u;

SceneGrid::SceneGrid()
: m_objects()
, m_cells()
{
	m_cells.resize( cellCount_t );
	for ( auto& i : m_cells )
	{
		i.resize( cellCount_t  );
	}


}

void SceneGrid::Add( Entity* obj )
{

	sf::Vector2f local = obj->getPosition() - sf::Vector2f( m_viewRect.left, m_viewRect.top );

	if ( local.x <= 0 || local.x >= m_viewRect.width ||
		local.y <= 0 || local.y >= m_viewRect.height )
		return;



	float cellSizeX = ( m_viewRect.width / static_cast< float >( cellCount_t ));
	float cellSizeY = ( m_viewRect.height / static_cast< float >( cellCount_t ));

	size_t cellX = static_cast< size_t >( local.x / cellSizeX );
	size_t cellY = static_cast< size_t >( local.y / cellSizeY );


	//std::cout << "Cell = " << cellX << ", " << cellY << '\n';
	//std::cout << "local = " << local.x  << ", " << local.y << '\n';
	//std::cout << "view = (" << m_viewRect.top << ", " << m_viewRect.left << ", " << m_viewRect.width << ", " << m_viewRect.height << '\n';

	m_cells[cellX][cellY].push_back( obj );

	//m_objects.push_back( obj );
}

void SceneGrid::Clear()
{
	//std::cout << "Clear, size = " << m_cells[0][0].size( ) << '\n';

	//m_objects.clear(); 

	for ( auto& i : m_cells )
	for ( auto& j : i )
		j.clear();
	
}

std::vector<Entity*> SceneGrid::GetObjects() const
{
	return m_objects;
}



void SceneGrid::CalcCollision( std::set<Entity::Pair_t>& collisionPairs )
{
	for ( size_t cellX = 0; cellX < cellCount_t; ++cellX )
	{
		for ( size_t cellY = 0; cellY < cellCount_t; ++cellY )
		{
			//std::vector<Entity*> objects;
			std::set<SceneNode::Pair_t> cellCollisionPairs;
			CheckCellCollisions( cellX, cellY, cellCollisionPairs );
			collisionPairs.insert( cellCollisionPairs.begin(), cellCollisionPairs.end() );
		}
	}
}

	//for ( auto& i : m_objects )
	//{
	//	for ( auto& j : m_objects )
	//	{
	//		if ( i != j )
	//		{
	//			//std::cout << "i, j = " << i << ", " << j << '\n';
	//			if ( i->GetBoundingRect().intersects( j->GetBoundingRect() ) )
	//			{
	//				collisionPairs.insert( std::minmax( i, j ) );
	//				std::cout << "Collision\n";
	//			}
	//		}
	//	}
	//}


void SceneGrid::CheckCellCollisions( size_t cellX, size_t cellY, std::set<SceneNode::Pair_t>& collisionPairs )
{
	for ( auto& i : m_cells[cellX][cellY] )
	{
		if (!i->IsDestroyed( ))
		for ( auto& j : m_cells[cellX][cellY] )
		{
			if ( !j->IsDestroyed( ) )
			if ( i != j )
			{
				if ( i->GetBoundingRect( ).intersects( j->GetBoundingRect( ) ) )
				{
					collisionPairs.insert( std::minmax( i, j ) );
					//std::cout << "Collision\n";
				}
			}
		}
	}
}

void SceneGrid::CollectCellObjects( size_t cellX, size_t cellY, std::vector<Entity*>& objects )
{
	objects = m_cells[cellX][cellY];
}

void SceneGrid::SetView( sf::FloatRect rect )
{
	m_viewRect = rect;
}

//void SceneNode::CheckSceneCollision( SceneNode& sceneGraph, std::set<Pair_t>& collisionPairs )
//{
//	CheckNodeCollision( sceneGraph, collisionPairs );
//
//	for ( Ptr_t& child : sceneGraph.m_children )
//		CheckSceneCollision( *child, collisionPairs );
//}
//
//void SceneNode::CheckNodeCollision( SceneNode& node, std::set<Pair_t>& collisionPairs )
//{
//	if ( this != &node && collision( *this, node ) && !IsDestroyed( ) && !node.IsDestroyed( ) )
//		collisionPairs.insert( std::minmax( this, &node ) );
//
//	for ( Ptr_t& child : m_children )
//		child->CheckNodeCollision( node, collisionPairs );
//}
