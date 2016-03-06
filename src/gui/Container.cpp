#include "gui/Container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace GUI
{

Container::Container()
: m_children()
, mSelectedChild(-1)
{
}

void Container::pack(Component::Ptr component)
{
	m_children.push_back(component);

	if (!hasSelection() && component->IsSelectable())
		select(m_children.size() - 1);
}

bool Container::IsSelectable() const
{
    return false;
}

void Container::HandleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
	if (hasSelection() && m_children[mSelectedChild]->isActive())
	{
		m_children[mSelectedChild]->HandleEvent(event);
	}
	else if (( event.type == sf::Event::KeyReleased ) || ( event.type == sf::Event::JoystickMoved ))
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				m_children[mSelectedChild]->activate();
		}


		if ( event.joystickMove.axis == sf::Joystick::Axis::Y )
		{
			//std::cout << event.joystickMove.position << '\n';
			if ( event.joystickMove.position < -99.99f )
				selectPrevious();
			else if ( event.joystickMove.position > 99.99f )
				selectNext();
		}
	}
	if ( event.type == sf::Event::JoystickButtonPressed )
	{

		 if ( event.joystickButton.button == 1 )
		{
			if ( hasSelection() )
				m_children[mSelectedChild]->activate();
		}
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for (const Component::Ptr& child : m_children)
		target.draw(*child, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(std::size_t index)
{
	if (m_children[index]->IsSelectable())
	{
		if (hasSelection())
			m_children[mSelectedChild]->deselect();

		m_children[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % m_children.size();
	while (!m_children[next]->IsSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + m_children.size() - 1) % m_children.size();
	while (!m_children[prev]->IsSelectable());

	// Select that component
	select(prev);
}

}
