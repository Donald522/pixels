#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
	public:
							TitleState(StateStack& stack, Context_t context);

		virtual void		Draw();
		virtual bool		Update(sf::Time dt);
		virtual bool		HandleEvent(const sf::Event& event);


	private:
		sf::Text			m_text;
		sf::Sprite			m_backgroundSprite;
};

#endif // TITLESTATE_H
