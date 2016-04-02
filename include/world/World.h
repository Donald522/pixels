#ifndef WORLD_H
#define WORLD_H

#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"
#include "nodes/SceneNode.h"
#include "nodes/SpriteNode.h"
#include "entity/Creature.h"
#include "system/CommandQueue.h"
#include "system/Command.h"
#include "effects/BloomEffect.h"
#include "music/SoundPlayer.h"
#include "world/Level.h"

#include "system/Config.h"
#include "system/SceneGrid.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <array>
#include <queue>



// Forward declaration
namespace sf
{
	class RenderTarget;
}

class World : private sf::NonCopyable
{
	public:

        explicit							World(sf::RenderTarget& outTarget, FontHolder& fonts, SoundPlayer& sounds, Config_t& cfg);

		void								Update(sf::Time dt);
		void								Draw();
		
		CommandQueue&						GetCommandQueue();

		bool 								HasAlivePlayer() const;
		bool 								HasPlayerReachedEnd() const;

		size_t								GetEntititisCount() const;

		void								ScrollStop( );
		void								ScrollResume( );
        void                                SetScrollSpeed(float speed);
        float                               GetScrollSpeed() const;

	private:

        void                                LoadLevel();
		void								LoadTextures();
		void								AdaptPlayerPosition();
		void								AdaptPlayerVelocity();
		void								HandleCollisions();
        void                                UpdateSounds();
		
		void								BuildScene();
		void								AddEnemies();
		void								AddEnemy( Creature::Type_t type, float relX, float relY );
		void								SpawnEnemies();
		void								DestroyEntitiesOutsideView();
		void								GuideMissiles();
		sf::FloatRect						GetViewBounds() const;
		sf::FloatRect						GetBattlefieldBounds() const;

	private:

		enum Layer_t
		{
			Background,
			LowerAir,
			UpperAir,
			LayerCount
		};

		struct SpawnPoint_t 
		{
			SpawnPoint_t( Creature::Type_t type, float x, float y )
			: type(type)
			, x(x)
			, y(y)
			{
			}

			Creature::Type_t type;
			float x;
			float y;
		};


	private:

		sf::RenderTarget&					m_target;
		sf::RenderTexture					m_sceneTexture;
		sf::View							m_worldView;
		TextureHolder						m_textures;
		FontHolder&							m_fonts;
        SoundPlayer&                        m_sounds;


		SceneGrid							m_sceneGrid;

		SceneNode							m_sceneGraph;
		std::array<SceneNode*, LayerCount>	m_sceneLayers;
		CommandQueue						m_commandQueue;


		sf::FloatRect						m_worldBounds;
		sf::Vector2f						m_spawnPosition;
		float								m_scrollSpeed;
		Creature*							m_playerAircraft;

		std::vector<SpawnPoint_t>			m_enemySpawnPoints;
		std::vector<Creature*>				m_activeEnemies;

		BloomEffect							m_bloomEffect;
		bool 								m_useBloomEffect;


        Level                               m_level;

};

#endif // WORLD_H
