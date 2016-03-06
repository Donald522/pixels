#ifndef COMMAND_H
#define COMMAND_H

#include "resource/Category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>


class SceneNode;

struct Command_t
{

	typedef std::function<void(SceneNode&, sf::Time)> Action_t;

								Command_t();

	Action_t					action;
	unsigned int				category;

};


template <typename GameObject, typename Function>
Command_t::Action_t DerivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif // COMMAND_H
