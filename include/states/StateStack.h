#ifndef STATESTACK_H
#define STATESTACK_H

#include "states/State.h"
#include "states/StateIdentifiers.h"
#include "resource/ResourceIdentifiers.h"
#include "log/Log.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>



namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
	public:

		enum StateStackAction_t
		{
			Push,
			Pop,
			Clear,
		};


	public:		

		explicit			StateStack(State::Context_t context);

		template <typename T>
		void				RegisterState(States::ID_t stateID);

		void				Update(sf::Time dt);
		void				Draw();
		void				HandleEvent(const sf::Event& event);

		void				PushState(States::ID_t stateID);
		void				PopState();
		void				ClearStates();

		bool				IsEmpty() const;


	private:

		State::Ptr_t		CreateState(States::ID_t stateID);
		void				ApplyPendingChanges();


	private:

		struct PendingChange_t
		{
			explicit						PendingChange_t(StateStackAction_t action, States::ID_t stateID = States::None);

			StateStackAction_t				action;
			States::ID_t					stateID;
		};


	private:
		std::vector<State::Ptr_t>								m_stack;
		std::vector<PendingChange_t>							m_pendingList;

		State::Context_t										m_context;
		std::map<States::ID_t, std::function<State::Ptr_t()>>	m_factories;
};


template <typename T>
void StateStack::RegisterState(States::ID_t stateID)
{
	_LOG_INFO( "RegisterState id = " + std::to_string( stateID ) );
	m_factories[stateID] = [this] ()
	{
		return State::Ptr_t(new T(*this, m_context));
	};
}

#endif // STATESTACK_H
