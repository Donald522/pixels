#include "states/MenuState.h"
#include "gui/Button.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context_t context)
: State(stack, context)
, m_renderTexture()
, m_guiContainer()
, m_effectTime(sf::Time::Zero)
{
	std::cout << "[STATE]: menu\n";

	m_renderTexture.create( context.window->getSize( ).x, context.window->getSize( ).y );

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(100, 300);
    playButton->SetText("Play");
    playButton->SetCallback([this] ()
	{
		RequestStackPop();
		RequestStackPush(States::Game);
	});
	

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(100, 350);
    settingsButton->SetText("Settings");
    settingsButton->SetCallback([this] ()
	{
		RequestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 400);
    exitButton->SetText("Exit");
    exitButton->SetCallback([this] ()
	{
		RequestStackPop();
	});

    m_guiContainer.Pack(playButton);
    m_guiContainer.Pack(settingsButton);
    m_guiContainer.Pack(exitButton);


	m_gameName.setFont( context.fonts->Get( Fonts::Main ) );
	m_gameName.setString( "Pixels" );
	m_gameName.setCharacterSize( 100u );

	sf::Vector2f windowSize( context.window->getSize( ) );
	m_gameName.setPosition( 0.5f * windowSize.x, 0.2f * windowSize.y );

	CenterOrigin( m_gameName );


	m_backgroundSprite.setTexture( context.textures->Get(Textures::Menu ));
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	bool useEffect = true;
	if ( useEffect )
	{
		m_renderTexture.clear();
		m_renderTexture.setView( window.getDefaultView() );
		m_renderTexture.draw( m_backgroundSprite );
        m_renderTexture.draw( m_guiContainer );
		m_renderTexture.draw( m_gameName );
		m_renderTexture.display();

		m_pixelateEffect.Apply( m_renderTexture, window );
		//m_bloomEffect.Apply( m_renderTexture, window );
	}
	else
	{
		window.setView( window.getDefaultView( ) );
		window.draw( m_backgroundSprite );
        window.draw( m_guiContainer );
		window.draw( m_gameName );

	}

}

bool MenuState::Update(sf::Time dt)
{
	static bool dir = true;

	if ( dir )
	{
		if ( m_effectTime <= sf::seconds( 1.6f ) )
			m_effectTime += dt;
		else
			dir = !dir;
	}
	else
	{
		if ( m_effectTime >= sf::Time::Zero )
			m_effectTime -= dt;
		else
			dir = !dir;
	}
	m_pixelateEffect.SetPixelThreshold( m_effectTime.asMilliseconds( ) *  1.0f + 150.0f );
	
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
    m_guiContainer.HandleEvent(event);
	return false;
}
