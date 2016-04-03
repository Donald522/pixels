#include "gui/Container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace GUI
{

Container::Container()
: m_children()
, m_selectedChild(-1)
{
}

void Container::Pack(Component::Ptr component)
{
	m_children.push_back(component);

	if (!HasSelection() && component->IsSelectable())
		Select(m_children.size() - 1);
}

bool Container::IsSelectable() const
{
    return false;
}

void Container::HandleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
    if (HasSelection() && m_children[m_selectedChild]->IsActive())
	{
		m_children[m_selectedChild]->HandleEvent(event);
	}
	else if (( event.type == sf::Event::KeyReleased ) || ( event.type == sf::Event::JoystickMoved ))
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			SelectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			SelectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (HasSelection())
                m_children[m_selectedChild]->Activate();
		}


		if ( event.joystickMove.axis == sf::Joystick::Axis::Y )
		{
			//std::cout << event.joystickMove.position << '\n';
			if ( event.joystickMove.position < -99.99f )
				SelectPrevious();
			else if ( event.joystickMove.position > 99.99f )
				SelectNext();
		}
	}
	if ( event.type == sf::Event::JoystickButtonPressed )
	{

		 if ( event.joystickButton.button == 1 )
		{
			if ( HasSelection() )
                m_children[m_selectedChild]->Activate();
		}
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for (const Component::Ptr& child : m_children)
		target.draw(*child, states);
}

bool Container::HasSelection() const
{
	return m_selectedChild >= 0;
}

void Container::Select(std::size_t index)
{
	if (m_children[index]->IsSelectable())
	{
		if (HasSelection())
            m_children[m_selectedChild]->Deselect();

        m_children[index]->Select();
		m_selectedChild = index;
	}
}

void Container::SelectNext()
{
	if (!HasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = m_selectedChild;
	do
		next = (next + 1) % m_children.size();
	while (!m_children[next]->IsSelectable());

	// Select that component
	Select(next);
}

void Container::SelectPrevious()
{
	if (!HasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = m_selectedChild;
	do
		prev = (prev + m_children.size() - 1) % m_children.size();
	while (!m_children[prev]->IsSelectable());

	// Select that component
	Select(prev);
}

}
