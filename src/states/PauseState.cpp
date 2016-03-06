#include "states/PauseState.h"
#include "gui/Button.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context_t context)
: State(stack, context)
, m_backgroundSprite()
, m_pausedText()
, m_guiContainer()
{
	sf::Font& font = context.fonts->Get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	m_pausedText.setFont(font);
	m_pausedText.setString("Game Paused");	
	m_pausedText.setCharacterSize(70);
	CenterOrigin(m_pausedText);
	m_pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    returnButton->SetText("Return");
    returnButton->SetCallback([this] ()
	{
		RequestStackPop();
	});

	auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    backToMenuButton->SetText("Back to menu");
    backToMenuButton->SetCallback([this] ()
	{
		RequestStateClear();
		RequestStackPush(States::Menu);
	});

    m_guiContainer.Pack(returnButton);
    m_guiContainer.Pack(backToMenuButton);
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_pausedText);
    window.draw(m_guiContainer);
}

bool PauseState::Update(sf::Time)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
    m_guiContainer.HandleEvent(event);
	return false;
}
