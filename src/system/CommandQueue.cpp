#include "system/CommandQueue.h"
#include "nodes/SceneNode.h"


void CommandQueue::Push(const Command_t& command)
{
	m_queue.push(command);
}

Command_t CommandQueue::Pop()
{
	Command_t command = m_queue.front();
	m_queue.pop();
	return command;
}

bool CommandQueue::IsEmpty() const
{
	return m_queue.empty();
}
