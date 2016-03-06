#include "states/LevelSelectState.h"
#include "resource/ResourceHolder.h"
#include "util/Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

LevelSelectState::LevelSelectState( StateStack& stack, Context_t context )
: State( stack, context )
, m_tittleText()
{
	std::cout << "[STATE]: Level selection\n";
	sf::Font& font = context.fonts->Get( Fonts::Main );
	sf::Vector2f windowSize( context.window->getSize( ) );

	m_tittleText.setFont( font );
	m_tittleText.setString( "Level Selection" );

	m_tittleText.setCharacterSize( 80 );
	CenterOrigin( m_tittleText );
	m_tittleText.setPosition( 0.5f * windowSize.x, 0.4f * windowSize.y );

	GetContext().window->setTitle( "Level selection" );


	//m_backgroundSprite.setTexture( context.textures->Get( Textures::LevelSelect ) );
	sf::Texture& texture = context.textures->Get( Textures::LevelSelect );
	texture.setRepeated( true );
	m_backgroundSprite.setTexture( texture  );
}

void LevelSelectState::Draw()
{
	sf::RenderWindow& window = *GetContext( ).window;
	window.draw( m_backgroundSprite );
	window.draw( m_tittleText );
}

bool LevelSelectState::Update( sf::Time dt )
{
	return true;
}

bool LevelSelectState::HandleEvent( const sf::Event& event )
{
	// If any key is pressed, trigger the next screen
	if ( ( event.type == sf::Event::KeyPressed ) ||
		( event.type == sf::Event::JoystickButtonPressed ) )
	{
		RequestStackPop( );
		RequestStackPush( States::Menu );
	}

	return false;
}
