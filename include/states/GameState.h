#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "states/State.h"
#include "world/World.h"
#include "player/Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
	public:

							GameState(StateStack& stack, Context_t context);

		virtual void		Draw();
		virtual bool		Update(sf::Time dt);
		virtual bool		HandleEvent(const sf::Event& event);

	private:

		World				m_world;
		Player&				m_player;
};

#endif // GAMESTATE_HPP
