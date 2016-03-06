#ifndef PLAYER_H
#define PLAYER_H

#include "system/Command.h"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:

		enum PlayerAction_t
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Fire,
			LaunchMissile,
			ActionCount
		};

		enum MissionStatus_t
		{
			MissionRunning,
			MissionSuccess,
			MissionFailure
		};


	public:

								Player();

		void					HandleEvent(const sf::Event& event, CommandQueue& commands);
		void					HandleRealtimeInput(CommandQueue& commands);

		void					AssignKey(PlayerAction_t action, sf::Keyboard::Key key);
		sf::Keyboard::Key		GetAssignedKey(PlayerAction_t action) const;

		void 					SetMissionStatus(MissionStatus_t status);
		MissionStatus_t 		GetMissionStatus() const;

	private:

		void					InitializeActions();
		static bool				IsRealtimeAction(PlayerAction_t action);

	private:

		bool												m_useJoystick;

		std::map<sf::Keyboard::Key, PlayerAction_t>			m_keyBinding;
		std::map<size_t, PlayerAction_t>					m_joystickBindings;
		std::map<PlayerAction_t, Command_t>					m_actionBinding;
		MissionStatus_t 									m_currentMissionStatus;
};

#endif // PLAYER_H
