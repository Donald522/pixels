#include "player/Player.h"
#include "system/CommandQueue.h"
#include "entity/Creature.h"

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;


struct AircraftMover
{
	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Creature& Creature, sf::Time) const
	{
		Creature.Accelerate(velocity * Creature.GetSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player()
: m_useJoystick( false ) 
, m_currentMissionStatus(MissionRunning)
{
	if ( sf::Joystick::isConnected( 0 ) )
		m_useJoystick = true;
    //TODO: hard coded
    m_useJoystick = false;

	// Set initial key bindings
	if ( m_useJoystick )
	{
		m_joystickBindings[sf::Joystick::X] = MoveLeft;
		m_joystickBindings[sf::Joystick::X] = MoveRight;
		m_joystickBindings[sf::Keyboard::Up] = MoveUp;
		m_joystickBindings[sf::Keyboard::Down] = MoveDown;
		m_joystickBindings[sf::Keyboard::Space] = Fire;
		m_joystickBindings[sf::Keyboard::M] = LaunchMissile;
	}
	else
	{
		m_keyBinding[sf::Keyboard::Left]	= MoveLeft;
		m_keyBinding[sf::Keyboard::Right]	= MoveRight;
		m_keyBinding[sf::Keyboard::Up]		= MoveUp;
		m_keyBinding[sf::Keyboard::Down]	= MoveDown;
		m_keyBinding[sf::Keyboard::Space]	= Fire;
		m_keyBinding[sf::Keyboard::M]		= LaunchMissile;
	}
 
	// Set initial action bindings
	InitializeActions();	

	// Assign all categories to player's Creature
	for ( auto& pair : m_actionBinding )
		pair.second.category = Category::PlayerAircraft;
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{

	if ( m_useJoystick )
	{
		Command_t c;
		c.category = Category::PlayerAircraft;
		if ( event.type == sf::Event::JoystickButtonPressed )
		{
			if ( event.joystickButton.button == 2)
			//if ( sf::Joystick::isButtonPressed( 0, 2 ) )
			{
				// yes: shoot!
				c.action = DerivedAction<Creature>( []( Creature& a, sf::Time ){ a.LaunchMissile(); } );
				commands.Push( c );
			}
		}
	}
	else
	{
		if ( event.type == sf::Event::KeyPressed )
		{
			// Check if pressed key appears in key binding, trigger command if so
			auto found = m_keyBinding.find( event.key.code );
			if ( found != m_keyBinding.end() && !IsRealtimeAction( found->second ) )
				commands.Push( m_actionBinding[found->second] );
		}
	}
	
}

void Player::HandleRealtimeInput(CommandQueue& commands)
{
	if ( m_useJoystick )
	{

		float x = sf::Joystick::getAxisPosition( 0, sf::Joystick::X );
		float y = sf::Joystick::getAxisPosition( 0, sf::Joystick::Y );

		Command_t c;
		c.category = Category::PlayerAircraft;
		if ( x > 1.0f )
		{
			c.action = DerivedAction<Creature>( AircraftMover( +1.0, 0 ) );
			commands.Push( c );
		}
		else if ( x < -1.0f )
		{
			c.action = DerivedAction<Creature>( AircraftMover( -1.0, 0 ) );
			commands.Push( c );
		}

		if ( y > 1.0f )
		{
			c.action = DerivedAction<Creature>( AircraftMover( 0.0, +1.0 ) );
			commands.Push( c );
		}
		else if ( y < -1.0f )
		{
			c.action = DerivedAction<Creature>( AircraftMover( 0.0, -1.0 ) );
			commands.Push( c );
		}

		if ( sf::Joystick::isButtonPressed( 0, 1 ) )
		{
			// yes: shoot!
			c.action = DerivedAction<Creature>( []( Creature& a, sf::Time ){ a.Fire(); } );
			commands.Push( c );
		}

	}

	if ( !m_useJoystick )
	{
		// Traverse all assigned keys and check if they are pressed
		for ( auto pair : m_keyBinding )
		{
			// If key is pressed, lookup action and trigger corresponding command
			if ( sf::Keyboard::isKeyPressed( pair.first ) && IsRealtimeAction( pair.second ) )
				commands.Push( m_actionBinding[pair.second] );
		}
	}
}

void Player::AssignKey(PlayerAction_t action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = m_keyBinding.begin(); itr != m_keyBinding.end(); )
	{
		if (itr->second == action)
			m_keyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	m_keyBinding[key] = action;
}

sf::Keyboard::Key Player::GetAssignedKey(PlayerAction_t action) const
{
	for ( auto pair : m_keyBinding )
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::SetMissionStatus(MissionStatus_t status)
{
	m_currentMissionStatus = status;
}

Player::MissionStatus_t Player::GetMissionStatus() const
{
	return m_currentMissionStatus;
}

void Player::InitializeActions()
{
	m_actionBinding[MoveLeft].action      = DerivedAction<Creature>(AircraftMover(-1.0,  0));
	m_actionBinding[MoveRight].action     = DerivedAction<Creature>(AircraftMover(+1.0,  0));
	m_actionBinding[MoveUp].action        = DerivedAction<Creature>(AircraftMover( 0, -1.0));
	m_actionBinding[MoveDown].action      = DerivedAction<Creature>(AircraftMover( 0, +1.0));
	m_actionBinding[Fire].action          = DerivedAction<Creature>([] (Creature& a, sf::Time){ a.Fire(); });
	m_actionBinding[LaunchMissile].action = DerivedAction<Creature>([] (Creature& a, sf::Time){ a.LaunchMissile(); });
}

bool Player::IsRealtimeAction(PlayerAction_t action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
		case Fire:
			return true;

		default:
			return false;
	}
}
