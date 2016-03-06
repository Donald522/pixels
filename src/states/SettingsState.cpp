#include "states/SettingsState.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context_t context)
: State(stack, context)
, m_GUIContainer()
{
	std::cout << "[STATE]: settings\n";

	// Build key binding buttons and labels
	AddButtonLabel(Player::MoveLeft,		300.f, "Move Left", context);
	AddButtonLabel(Player::MoveRight,		350.f, "Move Right", context);
	AddButtonLabel(Player::MoveUp,			400.f, "Move Up", context);
	AddButtonLabel(Player::MoveDown,		450.f, "Move Down", context);
	AddButtonLabel(Player::Fire,			500.f, "Fire", context);
	AddButtonLabel(Player::LaunchMissile,	550.f, "Missile", context);

	UpdateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(80.f, 620.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::RequestStackPop, this));

	m_GUIContainer.pack(backButton);
}

void SettingsState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	window.draw(m_backgroundSprite);
	window.draw(m_GUIContainer);
}

bool SettingsState::Update(sf::Time)
{
	return true;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (m_bindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				GetContext().player->AssignKey(static_cast<Player::PlayerAction_t>(action), event.key.code);
				m_bindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		UpdateLabels();
	else
		m_GUIContainer.HandleEvent(event);

	return false;
}

void SettingsState::UpdateLabels()
{
	Player& player = *GetContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.GetAssignedKey(static_cast<Player::PlayerAction_t>(i));
		m_bindingLabels[i]->SetText(ToString(key));
	}
}

void SettingsState::AddButtonLabel(Player::PlayerAction_t action, float y, const std::string& text, Context_t context)
{
	m_bindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	m_bindingButtons[action]->setPosition(80.f, y);
	m_bindingButtons[action]->setText(text);
	m_bindingButtons[action]->setToggle(true);

	m_bindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	m_bindingLabels[action]->setPosition(300.f, y + 15.f);

	m_GUIContainer.pack(m_bindingButtons[action]);
	m_GUIContainer.pack(m_bindingLabels[action]);
}
