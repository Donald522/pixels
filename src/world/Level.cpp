//
// Created by ubu on 26.03.16.
//

#include "world/Level.h"



Level::Level()
{

}

void Level::SetLevelLength(float length)
{
    m_levelLength = length;
}

void Level::SetSpawnPosition(sf::Vector2f pos)
{
    m_spawnPosition = pos;
}

void Level::SetView(sf::View view)
{
    m_view = view;
}

void Level::SetScroolSpeed(float speed)
{
    m_scrollSpeed = speed;
}

bool Level::LoadFromFile(const std::string fileName)
{
    //TODO:
    return false;
}

void Level::AddEnemy( Creature::Type_t type, float relX, float relY )
{
    //LogInfo( "Add enemy: type = " + std::to_string( type ) + ", X = " + std::to_string( relX ) + ", Y = " + std::to_string( relY ) );
    SpawnPoint_t spawn(type, m_spawnPosition.x + relX, m_spawnPosition.y - relY);
    m_enemySpawnPoints.push_back(spawn);
}
