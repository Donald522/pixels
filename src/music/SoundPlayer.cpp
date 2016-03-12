#include "music/SoundPlayer.h"
#include <SFML/Audio/Listener.hpp>

#include <cmath>

namespace
{
    const float listenerZ = 200.0f;
    const float attenuation = 8.0f;
    const float minDistance2D = 200.0f;
    const float minDistance3D = std::sqrt(minDistance2D * minDistance2D + listenerZ * listenerZ);
}

SoundPlayer::SoundPlayer()
: m_soundBuffers()
, m_sounds()
{
    m_soundBuffers.Load(SoundEffect::Button,    "Data/Sounds/Button.wav");
    m_soundBuffers.Load(SoundEffect::Explosion, "Data/Sounds/Explosion.wav");
    m_soundBuffers.Load(SoundEffect::Gunfire,   "Data/Sounds/Gunfire.wav");

    //towards the screen
    sf::Listener::setDirection(0.0f, 0.0f, -1.0f);
}

void SoundPlayer::Play(SoundEffect::ID_t effect)
{
	Play(effect, GetListenerPosition());
}

void SoundPlayer::Play(SoundEffect::ID_t effect, sf::Vector2f pos)
{
    m_sounds.push_back(sf::Sound());

    sf::Sound& sound = m_sounds.back();

    sound.setBuffer(m_soundBuffers.Get(effect));
    sound.setPosition(pos.x, -pos.y, 0.f);
    sound.setAttenuation(attenuation);
    sound.setMinDistance(minDistance3D);

    sound.play();
}

void SoundPlayer::RemoveStoppedSounds()
{
    m_sounds.remove_if( [] (const  sf::Sound& sound)
    {
        return sound.getStatus() == sf::Sound::Stopped;
    }
    );
}

void SoundPlayer::SetListenerPosition(sf::Vector2f pos)
{
    sf::Listener::setPosition(pos.x, -pos.y, listenerZ);
}

sf::Vector2f SoundPlayer::GetListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}
