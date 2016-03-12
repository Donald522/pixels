#include "states/GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "music/MusicPlayer.h"

GameState::GameState( StateStack& stack, Context_t context )
: State(stack, context)
, m_world( *context.window, *context.fonts, *context.sound )
, m_player(*context.player)
{
	m_player.SetMissionStatus(Player::MissionRunning);

	context.music->Play(Music::MissionTheme);
}

void GameState::Draw()
{
	m_world.Draw();
}

bool GameState::Update(sf::Time dt)
{
	m_world.Update(dt);

	if ( !m_world.HasAlivePlayer( ) )
	{
		m_player.SetMissionStatus(Player::MissionFailure);
		RequestStackPush(States::GameOver);
	}
	else if ( m_world.HasPlayerReachedEnd( ) )
	{
		m_player.SetMissionStatus(Player::MissionSuccess);
		RequestStackPush(States::GameOver);
	}

	//GetContext().window->setTitle( std::to_string( m_world.GetEntititisCount() ) );

	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleRealtimeInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if ( event.type == sf::Event::KeyPressed )
	{
		if ( event.key.code == sf::Keyboard::P )
			m_world.ScrollStop();

		if ( event.key.code == sf::Keyboard::O )
			m_world.ScrollResume( );

		if ( event.key.code == sf::Keyboard::Escape )
			RequestStackPush( States::Pause );
	}

	if ( event.type == sf::Event::JoystickButtonPressed )
	{

		if ( event.joystickButton.button == 4)
			RequestStackPush( States::Pause );
	}


	return true;
}
