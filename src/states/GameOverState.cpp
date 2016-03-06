#include "states/GameOverState.h"
#include "util/Utility.h"
#include "player/Player.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context_t context)
: State(stack, context)
, m_gameOverText()
, m_elapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->Get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	m_gameOverText.setFont(font);
	if (context.player->GetMissionStatus() == Player::MissionFailure)
		m_gameOverText.setString("You died!");	
	else
		m_gameOverText.setString("Successfull!");

	m_gameOverText.setCharacterSize(80);
	CenterOrigin(m_gameOverText);
	m_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_gameOverText);
}

bool GameOverState::Update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	m_elapsedTime += dt;
	if (m_elapsedTime > sf::seconds(3))
	{
		RequestStateClear();
		RequestStackPush(States::Menu);
	}
	return false;
}

bool GameOverState::HandleEvent(const sf::Event&)
{
	return false;
}
