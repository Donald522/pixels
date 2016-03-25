#include "states/State.h"
#include "states/StateStack.h"
#include "log/Log.h"



State::Context_t::Context_t(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
							Player& player, MusicPlayer& music, SoundPlayer& sound, Config_t cfg)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
, music(&music)
, sound(&sound)
, cfg(cfg)
{
}

State::State(StateStack& stack, Context_t context)
: m_stack(&stack)
, m_context(context)
{
}

State::~State()
{
}

void State::RequestStackPush(States::ID_t stateID)
{
	LogInfo( "Stack push id = " + std::to_string( stateID ) );
	m_stack->PushState(stateID);
}

void State::RequestStackPop()
{
	LogInfo( "Stack pop" );
	m_stack->PopState();
}

void State::RequestStateClear()
{
	LogInfo( "Stack clear" );
	m_stack->ClearStates();
}

State::Context_t State::GetContext() const
{
	return m_context;
}

