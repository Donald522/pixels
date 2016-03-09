#ifndef STATE_H
#define STATE_H

#include "states/StateIdentifiers.h"
#include "resource/ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;
class MusicPlayer;


class State
{
	public:

		typedef std::unique_ptr<State> Ptr_t;

		struct Context_t
		{
                                Context_t(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music);

			sf::RenderWindow*	window;
			TextureHolder*		textures;
			FontHolder*			fonts;
			Player*				player;
            MusicPlayer*        music;
		};


	public:

							State(StateStack& stack, Context_t context);
		virtual				~State();

		virtual void		Draw() = 0;
		virtual bool		Update(sf::Time dt) = 0;
		virtual bool		HandleEvent(const sf::Event& event) = 0;


	protected:

		void				RequestStackPush(States::ID_t stateID);
		void				RequestStackPop();
		void				RequestStateClear();

		Context_t			GetContext() const;

	private:

		StateStack*			m_stack;
		Context_t			m_context;
};


#endif // STATE_H
