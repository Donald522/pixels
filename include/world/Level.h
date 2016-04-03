//
// Created by ubu on 26.03.16.
//

#ifndef PIXELS_LEVEL_H
#define PIXELS_LEVEL_H

#include "entity/Creature.h"

#include <SFML/Graphics/View.hpp>


class Level {
public:

    struct SpawnPoint_t {
        SpawnPoint_t(Creature::Type_t type, float x, float y)
                : type(type), x(x), y(y) {
        }

        Creature::Type_t type;
        float x;
        float y;
    };

public:

                    Level();

    void            SetLevelLength(float length);
    void            SetSpawnPosition(const sf::Vector2f pos);
    void            SetView(sf::View view);
    void            SetScroolSpeed(float speed);

    float           GetLength() const;
    sf::Vector2f    GetSpawnPosition() const;
    sf::View        GetView() const;
    float           GetScroolSpeed() const;

    std::vector<SpawnPoint_t>& GetSpawnPoints();

    void            MoveView(float x, float y);


    //TODO: add support
    bool    LoadFromFile(const std::string fileName);
    void    AddEnemy( Creature::Type_t type, float relX, float relY );

    void Build();


private:

    sf::FloatRect               m_worldBounds;
    sf::Vector2f                m_spawnPosition;
    sf::View                    m_view;

    float                       m_scrollSpeed;
    float                       m_levelLength;

    std::vector<SpawnPoint_t>   m_enemySpawnPoints;
    std::vector<Creature *>     m_activeEnemies;
};


#endif //PIXELS_LEVEL_H
