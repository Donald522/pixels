#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "states/State.h"
#include "gui/Container.h"
#include "effects/BloomEffect.h"
#include "effects/PixelateEffect.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
		
								MenuState(StateStack& stack, Context_t context);

		virtual void			Draw();
		virtual bool			Update(sf::Time dt);
		virtual bool			HandleEvent(const sf::Event& event);


	private:
		sf::Time				m_effectTime;

		sf::Text				m_gameName;
		sf::Sprite				m_backgroundSprite;
		GUI::Container			mGUIContainer;

		sf::RenderTexture		m_renderTexture;
		BloomEffect				m_bloomEffect;
		PixelateEffect			m_pixelateEffect;
};

#endif // MENUSTATE_H
