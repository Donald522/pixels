#ifndef LEVEL_SELECT_STATE_H
#define LEVEL_SELECT_STATE_H

#include "states/State.h"
#include "gui/Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LevelSelectState : public State {
public:
	LevelSelectState( StateStack& stack, Context_t context);

	virtual void Draw();
	virtual bool Update( sf::Time dt );
	virtual bool HandleEvent( const sf::Event& event );

private:

	sf::Text m_tittleText;
	sf::Sprite m_backgroundSprite;
};


#endif // LEVEL_SELECT_STATE_H
