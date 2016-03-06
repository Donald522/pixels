#include "states/TitleState.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleState::TitleState(StateStack& stack, Context_t context)
: State(stack, context)
, m_text()
{
	std::cout << "[STATE]: tittle\n";
	m_backgroundSprite.setTexture( context.textures->Get( Textures::TitleScreen ) );

	m_text.setFont(context.fonts->Get(Fonts::Main));
	m_text.setString("Press any key to start");
	m_text.setCharacterSize( 40u );
	CenterOrigin(m_text);
	m_text.setPosition( sf::Vector2f( context.window->getSize( ) / 2u ) - sf::Vector2f(0.0f, context.window->getSize( ).y / 4.0f) );
}

void TitleState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.draw( m_backgroundSprite );
	window.draw(m_text);
}

bool TitleState::Update(sf::Time dt)
{
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if ((event.type == sf::Event::KeyReleased ) ||
	 ( event.type == sf::Event::JoystickButtonReleased ))
	{
		RequestStackPop();
		RequestStackPush(States::Menu);
	}

	return true;
}
