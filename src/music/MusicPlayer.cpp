#include "music/MusicPlayer.h"



MusicPlayer::MusicPlayer()
: m_music()
, m_fileNames()
, m_volume(0.0f)
{
	m_fileNames[Music::MenuTheme] = "Data/Music/13 It Only Takes One Shot (From the.mp3";
	m_fileNames[Music::MissionTheme] = "Data/Music/06 My Least Favorite Life( From the.mp3";
}

void MusicPlayer::Play( Music::ID_t theme )
{

}

void MusicPlayer::Stop()
{

}

void MusicPlayer::SetPaused( bool paused )
{

}

void MusicPlayer::SetVolume( float volume )
{

}

