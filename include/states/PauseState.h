#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "states/State.h"
#include "gui/Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
	public:
							PauseState(StateStack& stack, Context_t context);

		virtual void		Draw();
		virtual bool		Update(sf::Time dt);
		virtual bool		HandleEvent(const sf::Event& event);


	private:
		sf::Sprite			m_backgroundSprite;
		sf::Text			m_pausedText;
		GUI::Container 		mGUIContainer;
};

#endif // PAUSESTATE_H
