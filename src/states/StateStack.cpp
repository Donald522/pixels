#include "states/StateStack.h"

#include <cassert>
#include "log/Log.h"



StateStack::StateStack(State::Context_t context)
: m_stack()
, m_pendingList()
, m_context(context)
, m_factories()
{
}

void StateStack::Update(sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->Update(dt))
			break;
	}

	ApplyPendingChanges();
}

void StateStack::Draw()
{
	// Draw all active states from bottom to top
	for ( State::Ptr_t& state : m_stack )
		state->Draw();
}

void StateStack::HandleEvent(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as HandleEvent() returns false
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
			break;
	}

	ApplyPendingChanges();
}

void StateStack::PushState(States::ID_t stateID)
{
	m_pendingList.push_back(PendingChange_t(Push, stateID));
}

void StateStack::PopState()
{
	m_pendingList.push_back(PendingChange_t(Pop));
}

void StateStack::ClearStates()
{
	m_pendingList.push_back(PendingChange_t(Clear));
}

bool StateStack::IsEmpty() const
{
	return m_stack.empty();
}

State::Ptr_t StateStack::CreateState(States::ID_t stateID)
{
	_LOG_INFO( "Create state id = " + std::to_string(stateID));
	auto found = m_factories.find(stateID);
	assert(found != m_factories.end());

	return found->second();
}

void StateStack::ApplyPendingChanges()
{
	for ( PendingChange_t& change : m_pendingList )
	{
		switch (change.action)
		{
			case Push:
				m_stack.push_back(CreateState(change.stateID));
				break;

			case Pop:
				m_stack.pop_back();
				break;

			case Clear:
				m_stack.clear();
				break;
		}
	}

	m_pendingList.clear();
}

StateStack::PendingChange_t::PendingChange_t(StateStackAction_t action, States::ID_t stateID)
: action(action)
, stateID(stateID)
{

}

