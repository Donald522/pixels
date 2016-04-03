//
// Created by ubu on 26.03.16.
//

#include "world/Level.h"
#include "pugixml.hpp"


Level::Level()
{

}

void Level::SetLevelLength(float length)
{
    m_levelLength = length;
}

void Level::SetSpawnPosition(const sf::Vector2f pos)
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

float Level::GetLength() const
{
    return  m_levelLength;
}

sf::Vector2f Level::GetSpawnPosition() const
{
    return m_spawnPosition;
}

sf::View Level::GetView() const
{
    return m_view;
}

float Level::GetScroolSpeed() const
{
    return m_scrollSpeed;
}

std::vector<Level::SpawnPoint_t>& Level::GetSpawnPoints()
{
    return m_enemySpawnPoints;
}


void Level::MoveView(float x, float y)
{
    m_view.move(x, y);
}

bool Level::LoadFromFile(const std::string fileName)
{
    //TODO:
    pugi::xml_document doc;
    pugi::xml_parse_result res =  doc.load_file(fileName.c_str());
    if (res != pugi::status_ok)
    {
        //error loading file
        return false;
    }

    pugi::xml_node root = doc.root();
    return false;
}

void Level::AddEnemy( Creature::Type_t type, float relX, float relY )
{
    //LogInfo( "Add enemy: type = " + std::to_string( type ) + ", X = " + std::to_string( relX ) + ", Y = " + std::to_string( relY ) );
    SpawnPoint_t spawn(type, m_spawnPosition.x + relX, m_spawnPosition.y - relY);
    m_enemySpawnPoints.push_back(spawn);}

void Level::Build()
{
    // sort enemy spawn points
    std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(), [] (SpawnPoint_t lhs, SpawnPoint_t rhs)
    {
        return lhs.y < rhs.y;
    });

    assert(m_levelLength > 0);
    assert(m_view.getSize() != sf::Vector2f());
}
