#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "states/State.h"
#include "player/Player.h"
#include "gui/Container.h"
#include "gui/Button.h"
#include "gui/Label.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context_t context);

		virtual void					Draw();
		virtual bool					Update(sf::Time dt);
		virtual bool					HandleEvent(const sf::Event& event);


	private:
		void							UpdateLabels();
		void							AddButtonLabel(Player::PlayerAction_t action, float y, const std::string& text, Context_t context);


	private:
		sf::Sprite											m_backgroundSprite;
		GUI::Container										m_GUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	m_bindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> 	m_bindingLabels;
};

#endif // SETTINGSSTATE_H
