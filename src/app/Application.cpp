#include "app/Application.h"
#include "util/Utility.h"
#include "states/State.h"
#include "states/StateIdentifiers.h"
#include "states/TitleState.h"
#include "states/GameState.h"
#include "states/MenuState.h"
#include "states/PauseState.h"
#include "states/SettingsState.h"
#include "states/LevelSelectState.h"
#include "states/GameOverState.h"

#include "log/Log.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.0f/60.f);

#include <iostream>

Application::Application()
: m_window(sf::VideoMode(1400, 900), "Pixels", sf::Style::Close)
, m_textures()
, m_fonts()
, m_player()
, m_musicPlayer()
, m_soudPlayer()
, m_stateStack(State::Context_t(m_window, m_textures, m_fonts, m_player, m_musicPlayer, m_soudPlayer))
, m_statisticsText()
, m_statisticsUpdateTime()
, m_statisticsNumFrames(0)
{
	LogInfo("Window major version: "	+ std::to_string(m_window.getSettings().majorVersion));
	LogInfo("Window minor version: "	+ std::to_string(m_window.getSettings().minorVersion));
	LogInfo("Window depth: "			+ std::to_string(m_window.getSettings().depthBits));


	//State::Context_t(m_window, m_textures, m_fonts, m_player, m_musicPlayer, m_soudPlayer);
	m_window.setKeyRepeatEnabled(false);

	m_fonts.Load(Fonts::Main, 					"Data/Sansation.ttf");

	m_textures.Load(Textures::TitleScreen,		"Data/Textures/tittle.jpg" );
	m_textures.Load(Textures::Menu,				"Data/Textures/tittle.jpg" );
	m_textures.Load(Textures::LevelSelect,		"Data/Textures/tileable-classic-nebula-space-patterns-1.jpg" );
	m_textures.Load(Textures::Buttons,			"Data/Textures/Buttons.png");

	m_statisticsText.setFont(m_fonts.Get(Fonts::Main));
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(25u);

	RegisterStates();
	m_stateStack.PushState(States::Title);

	

	std::cout << "Joystick connected: "	<< sf::Joystick::isConnected(0)					<< std::endl;
	std::cout << "Joystick buttons: "	<< sf::Joystick::getButtonCount( 0 )			<< std::endl;
	std::cout << "Joystick has X: "		<< sf::Joystick::hasAxis( 0, sf::Joystick::X )	<< std::endl;
	std::cout << "Joystick has Y: "		<< sf::Joystick::hasAxis( 0, sf::Joystick::Y )	<< std::endl;
	std::cout.clear();
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Main cycle
	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while ( timeSinceLastUpdate > TimePerFrame )
		{
			timeSinceLastUpdate -= TimePerFrame;

			ProcessInput();

			Update( TimePerFrame );

			if (m_stateStack.IsEmpty())
				m_window.close();
		}
		UpdateStatistics(dt);
		Render();
	}
}

void Application::ProcessInput()
{
	sf::Event event;
	while ( m_window.pollEvent( event ) )
	{
		m_stateStack.HandleEvent(event);

		if ( event.type == sf::Event::Closed )
			m_window.close();
	}
}

void Application::Update(sf::Time dt)
{
	m_stateStack.Update( dt );
}

void Application::Render()
{
	m_window.clear();

	m_stateStack.Draw();

	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_statisticsText);

	m_window.display();
}

void Application::UpdateStatistics(sf::Time dt)
{
	m_statisticsUpdateTime += dt;
	++m_statisticsNumFrames;
	if (m_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		m_statisticsText.setString("FPS: " + ToString(m_statisticsNumFrames));
		
		m_statisticsUpdateTime -= sf::seconds(1.0f);
		m_statisticsNumFrames = 0;
	}
}

void Application::RegisterStates()
{
	m_stateStack.RegisterState<TitleState>(States::Title);
	m_stateStack.RegisterState<MenuState>(States::Menu);
	m_stateStack.RegisterState<GameState>(States::Game);
	m_stateStack.RegisterState<PauseState>(States::Pause);
	m_stateStack.RegisterState<SettingsState>(States::Settings);
	m_stateStack.RegisterState<LevelSelectState>( States::LevelSelect );
	m_stateStack.RegisterState<GameOverState>(States::GameOver);
}
