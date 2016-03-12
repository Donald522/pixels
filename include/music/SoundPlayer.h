#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <list>


class SoundPlayer : private sf::NonCopyable {
public:

                    SoundPlayer();
    void            Play(SoundEffect::ID_t effect);
    void            Play(SoundEffect::ID_t effect, sf::Vector2f pos);

    void            RemoveStoppedSounds();
    void            SetListenerPosition(sf::Vector2f pos);
    sf::Vector2f    GetListenerPosition() const;

private:

    SoundBufferHolder       m_soundBuffers;
    std::list<sf::Sound>    m_sounds;
};

#endif // SOUND_PLAYER_H
