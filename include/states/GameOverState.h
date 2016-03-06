#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "states/State.h"
#include "gui/Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
	public:
							GameOverState(StateStack& stack, Context_t context);

		virtual void		Draw();
		virtual bool		Update(sf::Time dt);
		virtual bool		HandleEvent(const sf::Event& event);


	private:
		sf::Text			m_gameOverText;
		sf::Time			m_elapsedTime;
};

#endif // GAMEOVERSTATE_H
