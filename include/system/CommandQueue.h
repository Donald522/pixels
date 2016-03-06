#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include "Command.h"

#include <queue>


class CommandQueue
{
	public:
		void						Push(const Command_t& command);
		Command_t					Pop();
		bool						IsEmpty() const;

		
	private:
		std::queue<Command_t>			m_queue;
};

#endif // COMMANDQUEUE_H
