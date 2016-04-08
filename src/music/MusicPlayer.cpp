#include "music/MusicPlayer.h"


MusicPlayer::MusicPlayer()
: m_music()
, m_fileNames()
, m_volume(25.0f)
{
	m_fileNames[Music::MenuTheme]       = "Data/Music/MenuTheme.ogg";
	m_fileNames[Music::MissionTheme]    = "Data/Music/MissionTheme.ogg";
}

void MusicPlayer::Play( Music::ID_t theme )
{
    if (!m_music.openFromFile(m_fileNames[theme]))
    {
        //_LOG_ERR("Can't open music " + m_fileNames[theme].c_str());
		//throw std::runtime_error("Music " + m_fileNames[theme] + " could not be opened.");
        return;
    }
    m_music.setVolume((m_volume));
    m_music.setLoop(true);
    m_music.play();
}

void MusicPlayer::Stop()
{
    m_music.stop();
}


void MusicPlayer::SetLoop(bool loop)
{
    m_music.setLoop(loop);
}

void MusicPlayer::SetPaused( bool paused )
{
    if (paused)
        m_music.pause();
    else
        m_music.play();
}

void MusicPlayer::SetVolume( float volume )
{
    volume = volume < 0.0f ? 0.0f : volume;
    volume = volume > 100.0f ? 100.0f : volume;

    m_music.setVolume(volume);
}

