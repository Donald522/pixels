#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "resource/ResourceIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable{
public:

			MusicPlayer();

    void	Play( Music::ID_t theme );
    void	Stop();

    void    SetLoop(bool loop);

    void	SetPaused( bool paused );
    void	SetVolume( float volume );

private:

    sf::Music							m_music;
    std::map<Music::ID_t, std::string>	m_fileNames;

    float								m_volume;
};

#endif // MUSIC_PLAYER_H

